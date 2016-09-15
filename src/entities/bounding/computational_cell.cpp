// author: dybisz

#include "computational_cell.h"


CComputationalCell::CComputationalCell(vec3 centerVertex, float size)
        : CCube(centerVertex, size),
          _isWireframe(false){
    _initShader();

    Vertex *vertices = CCube::generateVertices();
    GLuint *indices = CCube::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.setBuffer("vertices", GL_ARRAY_BUFFER);
    _vao.setBuffer("indices", GL_ELEMENT_ARRAY_BUFFER);
    _vao.bind();
    _vao.bindBuffers();
    _vao.getBuffer("vertices")->setDataStatic
            (CCube::getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["v_position"], 3, stride, 0);
    _vao.getBuffer("indices")->
            setDataStatic(CCube::getTotalIndices() * sizeof(GLuint),
                          &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

CComputationalCell::~CComputationalCell() {
    _shader.DeleteShaderProgram();
}


void CComputationalCell::render(const float *view, const float *projection) {
    _shader.Use();
    _vao.bind();

    if(_isWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUniform1f(_shader("u_immersion"), _immersion);
    glUniformMatrix4fv(_shader("u_modelMatrix"), 1, GL_FALSE, &_modelMatrix[0][0]);
    glUniformMatrix4fv(_shader("u_viewMatrix"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("u_projectionMatrix"), 1, GL_FALSE, projection);
    glDrawElements(GL_TRIANGLES, CCube::getTotalIndices(), GL_UNSIGNED_INT, 0);

    if(_isWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    _vao.unbind();
    _shader.UnUse();
}

void CComputationalCell::setModelMatrix(mat4 &modelMatrix) {
    _modelMatrix = modelMatrix;
}

bool CComputationalCell::isImmersed() {
    return (_immersion != 0.0);
}


void CComputationalCell::setImmersion(float waterHeight, float scaledCenterY) {
    float heightDifference = abs(scaledCenterY - waterHeight);
    float cellSize = 0.1f * CCube::_size;
    if(heightDifference <= (cellSize / 2.0) || (scaledCenterY < waterHeight)){
        _immersion = (heightDifference / cellSize) + 0.5f;
    } else {
        _immersion = 0.0;
    }
}

float CComputationalCell::getImmersion() {
    return _immersion;
}
vec3& CComputationalCell::getCenter() {
    return CCube::_center;
}

void CComputationalCell::_initShader() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/bounding_box.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/bounding_box.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("v_position");
    _shader.AddUniform("u_modelMatrix");
    _shader.AddUniform("u_viewMatrix");
    _shader.AddUniform("u_projectionMatrix");
    _shader.AddUniform("u_immersion");
    _shader.UnUse();
}