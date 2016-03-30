// author: dybisz

#include "water_grid.h"

using namespace entities;

CWaterGrid::CWaterGrid(
        int quadsPerX,
        int quadsPerZ,
        float sideSize,
        glm::vec2 bottomCorner) :
        CGrid(quadsPerX, quadsPerZ, sideSize, sideSize,bottomCorner),
        _wavesDeformer(quadsPerX+1, quadsPerZ+1)
        {

    _initShader();

//    _textures[0] = new CTexture2D(quadsPerX+1, quadsPerZ+1);

    Vertex *vertices = CGrid::generateVertices();
    GLuint *indices =  CGrid::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(CGrid::getTotalVertices() * sizeof(Vertex), &vertices[0]);

    _vao.assignFloatAttribute(_shader["vVertex"], 3, stride, 0);

//    _vao.assignFloatAttribute(_shader["vColor"], 3, stride,
//                              (const GLvoid *) offsetof(Vertex, color));

    _vao.assignFloatAttribute(_shader["texCoords"], 2, stride,
                              (const GLvoid*) offsetof(Vertex, texCoord));
    _vao.setIndices(CGrid::getTotalIndices() * sizeof(GLuint), &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

CWaterGrid::~CWaterGrid() {
//    delete _textures[0];
}

void CWaterGrid::render(const float *MVP) {
    // bind deformer
    _wavesDeformer.renderStep();

    glViewport(0, 0, 800, 600);
    _shader.Use();
    _vao.bind();
//    _textures[0]->bind();

//    glUniform1iARB(_shader("myFloatTex"),0);
    glUniform1f(_shader("waveTime"),_currentTime);
    glUniformMatrix4fv(_shader("MVP"), 1, GL_FALSE, MVP);
    glDrawElements(GL_TRIANGLES, CGrid::getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWaterGrid::render");

//    _textures[0]->unbind();
    _vao.unbind();
    _shader.UnUse();
}

void CWaterGrid::updateTime(float currentTime) {
    _currentTime = (GLfloat) currentTime;
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
    _shader.AddUniform("myFloatTex");
    _shader.UnUse();
}
