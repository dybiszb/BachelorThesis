// author: dybisz

#include "skybox_cube.h"

using namespace entities;

CSkybox::CSkybox(int sideSize,
                 const char* facesNames[6],
                 bool modernShaders) :
        CCube(sideSize),
        _texture(facesNames) {

    _initShader(modernShaders);

    Vertex *vertices = CCube::generateVertices();
    GLuint *indices = CCube::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(CCube::getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["v_position"], 3, stride, 0);
    _vao.setIndices(CCube::getTotalIndices() * sizeof(GLuint), &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

void CSkybox::render(const float *view,
                     const float *projection) {
    _shader.Use();
    _vao.bind();
    glActiveTexture(GL_TEXTURE0);
    _texture.bind();

    glUniformMatrix4fv(_shader("u_modelMatrix"), 1, GL_FALSE, &mat4(1.0)[0][0]);
    glUniformMatrix4fv(_shader("u_viewMatrix"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("u_projectionMatrix"), 1, GL_FALSE, projection);
    glUniform1iARB(_shader("u_skyboxTexture"),0);
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


void CSkybox::_initShader(bool modernShaders) {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/skybox.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/skybox.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("v_position");
    _shader.AddUniform("MVP");
    _shader.AddUniform("u_skyboxTexture");
    _shader.AddUniform("u_modelMatrix");
    _shader.AddUniform("u_viewMatrix");
    _shader.AddUniform("u_projectionMatrix");
    _shader.UnUse();
}
