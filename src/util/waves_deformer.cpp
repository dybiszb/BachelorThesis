// author: dybisz

#include "waves_deformer.h"
// TODO wdth and height change to side length
CWavesDeformer::CWavesDeformer(int width, int height, bool modernShaders)
        : _width(width),
          _height(height) {
    cout << "deformer1\n";
    _fbo1 = new CFrameBuffer();
    cout << "deformer2\n";
    _fbo2 = new CFrameBuffer();
    cout << "deformer3\n";
    _tex1 = new CTexture2D(width, height);
    cout << "deformer4\n";
    _tex2 = new CTexture2D(width, height);
    cout << "deformer5\n";

    _fbo1->bind();
    cout << "deformer6\n";
    _fbo1->setColorAttachement(*_tex1);
    cout << "deformer7\n";
    _fbo1->unbind();
    cout << "deformer8\n";

    _fbo2->bind();
    cout << "deformer9\n";
    _fbo2->setColorAttachement(*_tex2);
    cout << "deformer10\n";
    _fbo2->unbind();

    _initShaders(modernShaders);
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