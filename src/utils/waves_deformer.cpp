// author: dybisz

#include "waves_deformer.h"

// TODO wdth and height change to side length
CWavesDeformer::CWavesDeformer(int width, int height, bool modernShaders)
        : _width(width),
          _height(height) {

    _fbo0 = new CFrameBuffer();
    _fbo1 = new CFrameBuffer();
    _tex0 = new CTexture2D(width, height);
    _tex1 = new CTexture2D(width, height);

    _fbo0->bind();
    _fbo0->setColorAttachement(*_tex0);
    _fbo0->unbind();

    _fbo1->bind();
    _fbo1->setColorAttachement(*_tex1);
    _fbo1->unbind();

    _initMembraneCoefficients();
    _initShaders(modernShaders);
    _initVao();
}

void CWavesDeformer::setVerticesPerSide(int verticesPerSide) {
    _verticesPerSide = verticesPerSide;
}

void CWavesDeformer::disturbSurface(vec2 &quad, float amount) {

//    cout << "quad: " << quad.x << " " << quad.y << endl;

    if (_counter % 2 == 0) {
        _tex0->bind();
    } else {
        _tex1->bind();
    }


    GLfloat data[4] = {amount, 0, 0, 0};
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    quad.x,
                    quad.y,
                    1,
                    1,
                    GL_RGBA,
                    GL_FLOAT,
                    data);

    if (_counter % 2 == 0) {
        _tex0->unbind();
    } else {
        _tex1->unbind();
    }
}

void CWavesDeformer::updateTime(float deltaTime) {
    _dt = deltaTime;
}

CWavesDeformer::~CWavesDeformer() {
    delete _fbo0;
    delete _fbo1;
    delete _tex0;
    delete _tex1;

    _shader.DeleteShaderProgram();
}

void CWavesDeformer::animationStep() {
    glViewport(0, 0, _width, _height);

    _shader.Use();
    _vao.bind();
    glUniform1iARB(_shader("u_heightFieldTexture"), 0);
    glUniform1f(_shader("u_sideSize"), _width);
    glUniform1i(_shader("u_verticesPerSide"), _verticesPerSide);

    glUniform1f(_shader("u_membraneProperties.h"), _h);
    glUniform1f(_shader("u_membraneProperties.c"), _c);
    glUniform1f(_shader("u_membraneProperties.dt"), _dt);

    if (_counter % 2 == 0) {
        _tex0->bind();
        _fbo1->bind();
        glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT,
                       0);
        checkErrorOpenGL("CWavesDeformer::renderStep");
        _fbo1->unbind();
        _tex0->unbind();
        _tex1->bind();
    } else {
        _tex1->bind();
        _fbo0->bind();
        glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT,
                       0);
        checkErrorOpenGL("CWavesDeformer::renderStep");
        _fbo0->unbind();
        _tex1->unbind();
        _tex0->bind();
    }

//    _tex0->bind();
//    _fbo1->bind();
//    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
//    checkErrorOpenGL("CWavesDeformer::renderStep");
//
//    _tex1->bind();
//    _fbo0->bind();
//    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
//    checkErrorOpenGL("CWavesDeformer::renderStep");
//    _fbo0->unbind();

    _vao.unbind();
    _shader.UnUse();
}

void CWavesDeformer::bindAndSwapTextures() {
    _shader.Use();
    _vao.bind();
    if (_counter % 2 == 0) {
        _tex1->bind();
    } else {
        _tex0->bind();
    }
    _counter++;
    _vao.unbind();
    _shader.UnUse();
}

void CWavesDeformer::bindTexture() {
    _shader.Use();
    _vao.bind();
    if (_counter % 2 == 0) {
        _tex1->bind();
    } else {
        _tex0->bind();
    }
    _vao.unbind();
    _shader.UnUse();
}

void CWavesDeformer::_initShaders(bool modernShaders) {
    _shader.LoadFromFile
            (GL_VERTEX_SHADER, "res/shaders/waves_deformer.vert");
    _shader.LoadFromFile
            (GL_FRAGMENT_SHADER, "res/shaders/waves_deformer.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("a_position");
    _shader.AddAttribute("a_heightFieldTexCoords");
    _shader.AddUniform("u_heightFieldTexture");
    _shader.AddUniform("u_sideSize");
    _shader.AddUniform("u_verticesPerSide");
    _shader.AddUniform("u_membraneProperties.h");
    _shader.AddUniform("u_membraneProperties.c");
    _shader.AddUniform("u_membraneProperties.dt");
    _shader.UnUse();
}

void CWavesDeformer::_initVao() {
    Vertex *vertices = _quad.generateVertices();
    GLuint *indices = _quad.generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(_quad.getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["a_position"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["a_heightFieldTexCoords"], 2, stride,
                              (const GLvoid *) offsetof(Vertex, texCoord));
    _vao.setIndices(_quad.getTotalIndices() * sizeof(GLuint), &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

void CWavesDeformer::_initMembraneCoefficients() {
    float N = (float) _verticesPerSide;
    _h = 2. / (N - 1.);
    _c = 1.;
    _dt = 1. / (N);
}