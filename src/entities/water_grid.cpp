// author: dybisz

#include "water_grid.h"

using namespace entities;

CWaterGrid::CWaterGrid(
        int quadsPerX,
        int quadsPerZ,
        float sideSize,
        glm::vec2 bottomCorner) :
        CGrid(quadsPerX, quadsPerZ, sideSize, sideSize,bottomCorner),
        _wavesDeformer(quadsPerX+1, quadsPerZ+1),
        _cubemapId(-1)
        {

    _initShader();

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

void CWaterGrid::render(const float *MVP) {
    _wavesDeformer.bindTextureOfNextAnimationStep();
    glViewport(0, 0, 800, 600);

    _shader.Use();
    _vao.bind();

    glUniform1iARB(_shader("heightFieldTex"),0);
    glUniform1iARB(_shader("skyBoxTex"),0);

    // Sampler of cubemap
    checkErrorCubemapId("CWaterGrid::render", _cubemapId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapId);
    checkErrorOpenGL("CWaterGrid::render");

    glUniform3fv(_shader("cameraPos"), 1, &_cameraPosition[0]);
    glUniform1f(_shader("waveTime"),_currentTime);
    glUniformMatrix4fv(_shader("MVP"), 1, GL_FALSE, MVP);
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

void CWaterGrid::setSkyboxCubemapId(GLuint cubemapId){
    _cubemapId = cubemapId;
}

void CWaterGrid::_initShader() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/water.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/water.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("vVertex");
    _shader.AddAttribute("vColor");
    _shader.AddAttribute("texCoords");
    _shader.AddUniform("MVP");
    _shader.AddUniform("waveTime");
    _shader.AddUniform("heightFieldTex");
    _shader.AddUniform("skyBoxTex");
    _shader.AddUniform("cameraPos");
    _shader.UnUse();
}
