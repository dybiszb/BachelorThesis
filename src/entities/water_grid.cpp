// author: dybisz

#include "water_grid.h"

using namespace entities;

CWaterGrid::CWaterGrid(
        int quadsPerX,
        int quadsPerZ,
        float sideSize,
        glm::vec2 bottomCorner, bool modernShaders) :
        CGrid(quadsPerX, quadsPerZ, sideSize, sideSize,bottomCorner),
        _wavesDeformer(quadsPerX+1, quadsPerZ+1, modernShaders),
        _cubemapId(-1),
        _sideSize(sideSize),
        _verticesPerSide(quadsPerX + 1)
        {

    _initShader(modernShaders);
    _wavesDeformer.setVerticesPerSide(_verticesPerSide);

    Vertex *vertices = CGrid::generateVertices();
    GLuint *indices =  CGrid::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(CGrid::getTotalVertices() * sizeof(Vertex), &vertices[0]);

    _vao.assignFloatAttribute(_shader["vVertex"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["texCoords"], 2, stride,
                              (const GLvoid*) offsetof(Vertex, texCoord));
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
    glViewport(0, 0, 800, 600);

    _shader.Use();
    _vao.bind();

    glUniform1iARB(_shader("heightFieldTex"),0);
    glUniform1iARB(_shader("skyBoxTex"),1);

    // Sampler of cubemap
    checkErrorCubemapId("CWaterGrid::render", _cubemapId);
    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapId);
    checkErrorOpenGL("CWaterGrid::render");

    glUniform1f(_shader("sideSize"),_sideSize);
    glUniform1i(_shader("verticesPerSide"),_verticesPerSide);
    glUniform3fv(_shader("cameraPos"), 1, &_cameraPosition[0]);
    glUniform3fv(_shader("lightPos"), 1, &_lightPosition[0]);
    glUniform1f(_shader("waveTime"),_currentTime);
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

void CWaterGrid::setCameraAngle(float angle) {
    _cameraAngle = angle;
}

void CWaterGrid::setLightPosition(vec3& lightPosition) {
    _lightPosition.x = lightPosition.x;
    _lightPosition.y = lightPosition.y;
    _lightPosition.z = lightPosition.z;
}

void CWaterGrid::setSkyboxCubemapId(GLuint cubemapId){
    _cubemapId = cubemapId;
}

void CWaterGrid::_initShader(bool modernShaders) {
    if(modernShaders) {
        _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/330/water.vert");
        _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/330/water.frag");
    }else {
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
    _shader.AddUniform("lightPos");
    _shader.AddUniform("verticesPerSide");
    _shader.UnUse();
}
