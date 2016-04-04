// author: dybisz

#include "waves_deformer.h"
// TODO wdth and height change to side length
CWavesDeformer::CWavesDeformer(int width, int height, bool modernShaders)
        : _width(width),
          _height(height),
          _oddPassage(false) {

    _fbo1 = new CFrameBuffer();
    _fbo2 = new CFrameBuffer();
    _tex1 = new CTexture2D(width, height);
    _tex2 = new CTexture2D(width, height);
    _tex3 = new CTexture2D(width, height);

    _fbo1->bind();
    _fbo1->setColorAttachement(*_tex1);
    _fbo1->unbind();

    _fbo2->bind();
    _fbo2->setColorAttachement(*_tex2);
    _fbo2->unbind();

    _initShaders(modernShaders);
    _initVao();
}

CWavesDeformer::~CWavesDeformer() {
    delete _fbo1;
    delete _fbo2;
    delete _tex1;
    delete _tex2;
    delete _tex3;

    _shader.DeleteShaderProgram();
}

void CWavesDeformer::bindTextureOfNextAnimationStep() {
    glViewport(0, 0, _width, _height);

    _shader.Use();
    _vao.bind();
    glUniform1iARB(_shader("oldvalues"),0);
    glUniform1f(_shader("sideSize"),_width);

    _tex1->bind();
    _fbo2->bind();
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");

    _tex2->bind();
    _fbo1->bind();
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");
    _fbo1->unbind();

    _vao.unbind();
    _shader.UnUse();
}

void CWavesDeformer::_initShaders(bool modernShaders) {
    if(modernShaders) {
        _shader.LoadFromFile
                (GL_VERTEX_SHADER, "res/shaders/330/waves_deformer.vert");
        _shader.LoadFromFile
                (GL_FRAGMENT_SHADER, "res/shaders/330/waves_deformer.frag");
    } else {
        _shader.LoadFromFile
                (GL_VERTEX_SHADER, "res/shaders/120/waves_deformer.vert");
        _shader.LoadFromFile
                (GL_FRAGMENT_SHADER, "res/shaders/120/waves_deformer.frag");

    }
    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("vVertex");
    _shader.AddAttribute("texCoords");
    _shader.AddUniform("oldvalues");
    _shader.AddUniform("newvalues");
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