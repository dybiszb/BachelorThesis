// author: dybisz

#include "bounding_box.h"


CBoundingBox::CBoundingBox(vector<vec3> boundingVertices)
        : CCuboid(boundingVertices),
          _modelBox(false){
    _initShader();

    Vertex *vertices = CCuboid::generateVertices();
    GLuint *indices = CCuboid::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.setBuffer("vertices", GL_ARRAY_BUFFER);
    _vao.setBuffer("indices", GL_ELEMENT_ARRAY_BUFFER);
    _vao.bind();
    _vao.bindBuffers();
    _vao.getBuffer("vertices")->setDataStatic
            (CCuboid::getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["v_position"], 3, stride, 0);
    _vao.getBuffer("indices")->
            setDataStatic(CCuboid::getTotalIndices() * sizeof(GLuint),
                          &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

CBoundingBox::~CBoundingBox() {
    _shader.DeleteShaderProgram();
}


void CBoundingBox::render(const float *view, const float *projection) {
    if(!_visible) return;

    _shader.Use();
    _vao.bind();

    if(!_modelBox) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUniformMatrix4fv(_shader("u_modelMatrix"), 1, GL_FALSE, &_modelMatrix[0][0]);
    glUniformMatrix4fv(_shader("u_viewMatrix"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("u_projectionMatrix"), 1, GL_FALSE, projection);
    glDrawElements(GL_TRIANGLES, CCuboid::getTotalIndices(), GL_UNSIGNED_INT, 0);

    if(!_modelBox) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    _vao.unbind();
    _shader.UnUse();
}

void CBoundingBox::setModelMatrix(mat4 &modelMatrix) {
    _modelMatrix = modelMatrix;
}

void CBoundingBox::setModelBox(bool modelBox) {
    _modelBox = modelBox;
}

bool CBoundingBox::isModelBox()  {
    return _modelBox;
}

void CBoundingBox::setVisible(bool visible) {
    _visible = visible;
}

void CBoundingBox::_initShader() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/bounding_box.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/bounding_box.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("v_position");
    _shader.AddUniform("u_modelMatrix");
    _shader.AddUniform("u_viewMatrix");
    _shader.AddUniform("u_projectionMatrix");
    _shader.UnUse();
}