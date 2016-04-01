// author: dybisz

#include "skybox.h"

using namespace entities;

CSkybox::CSkybox(int sideSize, vector<const GLchar *> *facesNames) :
        CCube(sideSize),
        _texture(facesNames) {

    _initShader();

    Vertex *vertices = CCube::generateVertices();
    GLuint *indices = CCube::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(CCube::getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["vVertex"], 3, stride, 0);
    _vao.setIndices(CCube::getTotalIndices() * sizeof(GLuint), &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

void CSkybox::render(const float *MVP) {
    _shader.Use();
    _vao.bind();
    _texture.bind();

    glUniformMatrix4fv(_shader("MVP"), 1, GL_FALSE, MVP);
    glUniform1iARB(_shader("SkyBoxTexture"),0);
    glDrawElements(GL_TRIANGLES, CCube::getTotalIndices(), GL_UNSIGNED_INT, 0);

    _texture.unbind();
    _vao.unbind();
    _shader.UnUse();
}

// TODO check assignment operator for vec3

void CSkybox::setCameraPosition(vec3 cameraPosition) {
    _cameraPosition.x = cameraPosition.x;
    _cameraPosition.y = cameraPosition.y;
    _cameraPosition.z = cameraPosition.z;
}

GLuint CSkybox::getCubemapId() {
    return _texture.getId();
}


void CSkybox::_initShader() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/skybox.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/skybox.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("vVertex");
    _shader.AddUniform("MVP");
    _shader.AddUniform("SkyBoxTexture");
    _shader.UnUse();
}
