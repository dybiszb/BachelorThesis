// author: dybisz

#include "water_grid.h"

using namespace entities;

CWaterGrid::CWaterGrid(
        int quadsPerSide, float sideSize, glm::vec2 bottomCorner,
        GLuint cubemapId, bool modernShaders, int viewportWidth,
        int viewportHeight, bool animation, bool lightOn)
        : CGrid(quadsPerSide, quadsPerSide, sideSize, sideSize, bottomCorner),
          _wavesDeformer(quadsPerSide + 1, quadsPerSide + 1),
          _cubemapId(cubemapId), _sideSize(sideSize),
          _verticesPerSide(quadsPerSide + 1), _viewportWidth(viewportWidth),
          _viewportHeight(viewportHeight), _animation(animation),
          _lightOn(lightOn) {

    _initShader(modernShaders);

    Vertex *vertices = CGrid::generateVertices();
    GLuint *indices = CGrid::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _animation = true;
    // Bounding box
    float halfSide = _sideSize / 2.0f;
    _box[0] = vec3(-halfSide, -halfSide, -halfSide);
    _box[1] = vec3(halfSide, halfSide, halfSide);
    _vao.setCaller("CWaterGrid");

    _vao.bind();
    _vao.setBuffer("vertices", GL_ARRAY_BUFFER);
    _vao.setBuffer("indices", GL_ELEMENT_ARRAY_BUFFER);
    _vao.bindBuffers();
    _vao.getBuffer("vertices")->setDataStatic
            (CGrid::getTotalVertices() * sizeof(Vertex), &vertices[0]);

    _vao.assignFloatAttribute(_shader["a_position"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["a_heightFieldTexCoords"], 2, stride,
                              (const GLvoid *) offsetof(Vertex, texCoord));
    _vao.getBuffer("indices")->
            setDataStatic(CGrid::getTotalIndices() * sizeof(GLuint),
                          &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

CWaterGrid::~CWaterGrid() {

}

void CWaterGrid::render(const float *view,
                        const float *projection) {

    if (_animation) {
        _wavesDeformer.animationStep();
    }
    glActiveTexture(GL_TEXTURE0);
    _wavesDeformer.bindNoiseTexture();
    glViewport(0, 0, _viewportWidth, _viewportHeight);

    _shader.Use();
    _vao.bind();
    _vao.bindBuffers();

    glUniform1iARB(_shader("u_heightFieldTexture"), 0);
    glUniform1iARB(_shader("u_skyboxTexture"), 1);
    glUniform1iARB(_shader("u_noiseTexture"), 2);

    // Sampler of cubemap
    checkErrorCubemapId("CWaterGrid::render", _cubemapId);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapId);
    checkErrorOpenGL("CWaterGrid::render");

    glActiveTexture(GL_TEXTURE0 + 2);
    _wavesDeformer.bindNoiseTexture();

    glUniform1f(_shader("u_sideSize"), _sideSize);
    glUniform1f(_shader("u_time"), this->_totalTime);
    glUniform1i(_shader("u_verticesPerSide"), _verticesPerSide);
    glUniform3fv(_shader("u_cameraPosition"), 1, &_cameraPosition[0]);
    glUniform3fv(_shader("u_lightDirection"), 1, &_lightDirection[0]);
    glUniform1i(_shader("u_lightOn"), _lightOn);

    // Box
    glUniform3fv(_shader("u_box.boxMin"), 1, &_box[0][0]);
    glUniform3fv(_shader("u_box.boxMax"), 1, &_box[1][0]);

    glUniformMatrix4fv(_shader("u_modelMatrix"), 1, GL_FALSE, &mat4(1.0)[0][0]);
    glUniformMatrix4fv(_shader("u_viewMatrix"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("u_projectionMatrix"), 1, GL_FALSE, projection);
    glDrawElements(GL_TRIANGLES, CGrid::getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWaterGrid::render");

    _wavesDeformer.unbindDisturbanceTexture();
    _vao.unbind();
    _shader.UnUse();
}

GLfloat* CWaterGrid::getHeightfieldAsArray() {
    return _wavesDeformer.getCurrentTextureAsVector();
}

void CWaterGrid::updateTime(float deltaTime) {
    _currentTime = (GLfloat) deltaTime;
    _totalTime += _currentTime;
    _wavesDeformer.updateTime(deltaTime);
}

void CWaterGrid::setCameraPosition(vec3 cameraPosition) {
    _cameraPosition.x = cameraPosition.x;
    _cameraPosition.y = cameraPosition.y;
    _cameraPosition.z = cameraPosition.z;
}

void CWaterGrid::setLightDirections(vec3 &lightDirection) {
    _lightDirection.x = lightDirection.x;
    _lightDirection.y = lightDirection.y;
    _lightDirection.z = lightDirection.z;
}

void CWaterGrid::areaIntersect(vec2 &viewportCoordinates, CCustomCamera &camera,
                           float amount, int kernel, float flatness) {

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
            float spaceBetweenQuads = _gridSizeOnX / (float) _quadsOnX;
            quad.x = (int) (quad.x / spaceBetweenQuads);
            quad.y = (int) (quad.y / spaceBetweenQuads);
            _wavesDeformer.areaDisturbance(quad, amount, kernel, flatness);
        }


    }
}

void CWaterGrid::pointIntersect(vec2 &quadCoordinates, float amount) {
    _wavesDeformer.pointDisturbance(quadCoordinates, amount);
}

void CWaterGrid::pointIntersect(vec2& quadCoordinates, float amount, int
        kernel, float flatness) {
    _wavesDeformer.areaDisturbance(quadCoordinates, amount, kernel, flatness);
}

int CWaterGrid::getVerticesPerSide() {
    return _verticesPerSide;
}

void CWaterGrid::setAnimation(bool animation) {
    _animation = animation;
}

bool CWaterGrid::getAnimation() {
    return _animation;
}

void CWaterGrid::setLightOn(bool lightOn) {
    _lightOn = lightOn;
}

bool CWaterGrid::getLightOn() {
    return _lightOn;
}

void CWaterGrid::_initShader(bool modernShaders) {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/water.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/water.frag");
    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("a_position");
    _shader.AddAttribute("a_heightFieldTexCoords");
    _shader.AddUniform("u_modelMatrix");
    _shader.AddUniform("u_viewMatrix");
    _shader.AddUniform("u_projectionMatrix");
    _shader.AddUniform("u_heightFieldTexture");
    _shader.AddUniform("u_skyboxTexture");
    _shader.AddUniform("u_noiseTexture");
    _shader.AddUniform("u_cameraPosition");
    _shader.AddUniform("u_sideSize");
    _shader.AddUniform("u_verticesPerSide");
    _shader.AddUniform("u_box.boxMin");
    _shader.AddUniform("u_box.boxMax");
    _shader.AddUniform("u_lightDirection");
    _shader.AddUniform("u_lightOn");
    _shader.AddUniform("u_time");
    _shader.UnUse();
}
