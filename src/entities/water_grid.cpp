// author: dybisz

#include "water_grid.h"

using namespace entities;

CWaterGrid::CWaterGrid(int quadsPerSide, float sideSize, glm::vec2
bottomCorner, GLuint cubemapId, bool modernShaders, int viewportWidth,
                       int viewportHeight)
        : CGrid(quadsPerSide, quadsPerSide, sideSize, sideSize, bottomCorner),
          _wavesDeformer(quadsPerSide + 1, quadsPerSide + 1, modernShaders),
          _cubemapId(cubemapId), _sideSize(sideSize),
          _verticesPerSide(quadsPerSide + 1), _viewportWidth(viewportWidth),
          _viewportHeight(viewportHeight) {

    _initShader(modernShaders);
    _wavesDeformer.setVerticesPerSide(_verticesPerSide);

    Vertex *vertices = CGrid::generateVertices();
    GLuint *indices = CGrid::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(CGrid::getTotalVertices() * sizeof(Vertex), &vertices[0]);

    _vao.assignFloatAttribute(_shader["vVertex"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["texCoords"], 2, stride,
                              (const GLvoid *) offsetof(Vertex, texCoord));
    _vao.setIndices(CGrid::getTotalIndices() * sizeof(GLuint), &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

CWaterGrid::~CWaterGrid() {

}

void CWaterGrid::render(const float *view,
                        const float *projection) {
    // Old hardware does not allow to bind two types of textures (two
    // samplers) to one texture unit. Hence one needs to swap it between
    // animation texture and cubemap texture
    glActiveTexture(GL_TEXTURE0);
    _wavesDeformer.bindTextureOfNextAnimationStep();
    glViewport(0, 0, _viewportWidth, _viewportHeight);

    _shader.Use();
    _vao.bind();

    glUniform1iARB(_shader("heightFieldTex"), 0);
    glUniform1iARB(_shader("skyBoxTex"), 1);

    // Sampler of cubemap
    checkErrorCubemapId("CWaterGrid::render", _cubemapId);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapId);
    checkErrorOpenGL("CWaterGrid::render");

    glUniform1f(_shader("sideSize"), _sideSize);
    glUniform1i(_shader("verticesPerSide"), _verticesPerSide);
    glUniform3fv(_shader("cameraPos"), 1, &_cameraPosition[0]);
    glUniform1f(_shader("waveTime"), _currentTime);
    glUniformMatrix4fv(_shader("uModel"), 1, GL_FALSE, &mat4(1.0)[0][0]);
    glUniformMatrix4fv(_shader("uView"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("uProjection"), 1, GL_FALSE, projection);
    glDrawElements(GL_TRIANGLES, CGrid::getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWaterGrid::render");

    _vao.unbind();
    _shader.UnUse();
}

void CWaterGrid::updateTime(float currentTime) {
    _currentTime = (GLfloat) currentTime;
}

void CWaterGrid::setCameraPosition(vec3 cameraPosition) {
    _cameraPosition.x = cameraPosition.x;
    _cameraPosition.y = cameraPosition.y;
    _cameraPosition.z = cameraPosition.z;
}

void CWaterGrid::intersect(vec2 &viewportCoordinates, CCustomCamera &camera) {

    /* ----- Clip Coordinates ----- */
    vec3 rayNormalizedDeviceSpace = toNormalizedDeviceCoordinates(
            viewportCoordinates, _viewportWidth, _viewportHeight);
    vec4 rayClipSpace = vec4(rayNormalizedDeviceSpace.x,
                             rayNormalizedDeviceSpace.y, -1.0, 1.0);

    /* ----- Camera Coordinates ----- */
    mat4 projectionMatrix = camera.getProjectionMatrix();
    vec4 rayCameraSpace = toCameraCoordinates(rayClipSpace, projectionMatrix);

    /* ----- World Coordinates ----- */
    mat4 viewMatrix = camera.getViewMatrix();
    vec3 rayWorldSpace = toWorldCoordinates(rayCameraSpace, viewMatrix);


    /* -----Intersection Point ----- */
    vec3 planeNormal = vec3(0.0, 1.0, 0.0);
    vec3 cameraPosition = camera.getPosition();
    vec3 intersectionPoint = vec3(-1.0, -1.0, -1.0);

    if (rayIntersectsPlane(rayWorldSpace, planeNormal, cameraPosition,
                           intersectionPoint)) {

        vec2 quad = vec2(intersectionPoint.x, intersectionPoint.z);
        quad = quad - _bottomCorner;

        /* ----- Inside Water Surface ----- */
        if (quad.x > 0 && quad.x <= _gridSizeOnX &&
            quad.y > 0 && quad.y <= _gridSizeOnZ) {

            /* ----- Which Quad ----- */
            float spaceBetweenQuads = _gridSizeOnX / (float)_quadsOnX;
            quad.x = (int)(quad.x / spaceBetweenQuads);
            quad.y = (int)(quad.y / spaceBetweenQuads);
            _wavesDeformer.disturbSurface(quad, 1.0f);
            cout << quad.x << " " << quad.y << endl;
        }


    } else {
        cout << "miss!" << endl;
    }

}

void CWaterGrid::_initShader(bool modernShaders) {
    if (modernShaders) {
        _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/330/water.vert");
        _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/330/water.frag");
    } else {
        _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/120/water.vert");
        _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/120/water.frag");
    }
    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("vVertex");
    _shader.AddAttribute("vColor");
    _shader.AddAttribute("texCoords");
    _shader.AddUniform("uModel");
    _shader.AddUniform("uView");
    _shader.AddUniform("uProjection");
    _shader.AddUniform("waveTime");
    _shader.AddUniform("heightFieldTex");
    _shader.AddUniform("skyBoxTex");
    _shader.AddUniform("cameraPos");
    _shader.AddUniform("sideSize");
    _shader.AddUniform("verticesPerSide");
    _shader.UnUse();
}
