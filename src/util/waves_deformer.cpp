// author: dybisz

#include "waves_deformer.h"
// TODO wdth and height change to side length
CWavesDeformer::CWavesDeformer(int width, int height) : _width(width),
                                                        _height(height) {
    _fbo1 = new CFrameBuffer();
    _fbo2 = new CFrameBuffer();
    _tex1 = new CTexture2D(width, height);
    _tex2 = new CTexture2D(width, height);

    _fbo1->bind();
    _fbo1->setColorAttachement(*_tex1);
    _fbo1->unbind();

    _fbo2->bind();
    _fbo2->setColorAttachement(*_tex2);
    _fbo2->unbind();

    _initShaders();
    _initVao();
}

CWavesDeformer::~CWavesDeformer() {
    delete _fbo1;
    delete _fbo2;
    delete _tex1;
    delete _tex2;

    _shader.DeleteShaderProgram();
}

void CWavesDeformer::bindTextureOfNextAnimationStep() {
    glViewport(0, 0, _width, _height);

    _shader.Use();
    _vao.bind();

    _tex1->bind();
    _fbo2->bind();
    glUniform1f(_shader("sideSize"),_width);
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");

    _tex2->bind();
    _fbo1->bind();
    glUniform1f(_shader("sideSize"),_width);
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");

    _fbo1->unbind();
    _vao.unbind();
    _shader.UnUse();
}

void CWavesDeformer::_initShaders() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/waves_deformer.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/waves_deformer.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("vVertex");
    _shader.AddAttribute("texCoords");
    _shader.AddUniform("sampler");
    _shader.AddUniform("sideSize");
    _shader.UnUse();
}

void CWavesDeformer::_initVao() {
    Vertex *vertices = _quad.generateVertices();
    GLuint *indices = _quad.generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(_quad.getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["vVertex"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["texCoords"], 2, stride,
                              (const GLvoid *) offsetof(Vertex, texCoord));
    _vao.setIndices(_quad.getTotalIndices() * sizeof(GLuint), &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}