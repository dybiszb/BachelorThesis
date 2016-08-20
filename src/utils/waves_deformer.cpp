// author: dybisz

#include "waves_deformer.h"

// TODO wdth and height change to side length
CWavesDeformer::CWavesDeformer(int width, int height)
        : _width(width),
          _height(height) {

    _verticesPerSide = height;

    _fbo0 = new CFrameBuffer();
    _fbo1 = new CFrameBuffer();
    _fbo2 = new CFrameBuffer();

    _tex0 = new CTexture2D(width, height);
    _tex1 = new CTexture2D(width, height);
    _tex2 = new CTexture2D(width, height);

    _fbo0->bind();
    _fbo0->setColorAttachment(*_tex0);
    _fbo0->unbind();

    _fbo1->bind();
    _fbo1->setColorAttachment(*_tex1);
    _fbo1->unbind();

    _fbo2->bind();
    _fbo2->setColorAttachment(*_tex2);
    _fbo2->unbind();

    _initMembraneCoefficients();
    _initShaders();
    _initVao();
}

void CWavesDeformer::pointDisturbance(vec2 &quad, float amount) {
    _tex0->bind();

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

    _tex0->unbind();
}

void CWavesDeformer::areaDisturbance(vec2 &quad, float amount, int kernel,
                                     float flatness) {
    _tex0->bind();
    int quadXmin = (quad.x - kernel < 0) ? 0 : (quad.x - kernel);
    int quadXmax = (quad.x + kernel >= _width - 2) ? _width - 2 : (quad.x +
                                                                   kernel);
    int quadYmin = (quad.y - kernel < 0) ? 0 : (quad.y - kernel);
    int quadYmax = (quad.y + kernel >= _height - 2) ? _height - 2 : (quad.y +
                                                                     kernel);

    int data2Size = 4 * (quadXmax - quadXmin + 1) * (quadYmax - quadYmin + 1);

    GLfloat data2[data2Size];

    int offset = 0;
    for (int y = quadYmin; y <= quadYmax; y++) {
        for (int x = quadXmin; x <= quadXmax; x++) {
            float localX = x - quad.x;
            float localY = y - quad.y;
            data2[offset++] = amount + flatness * (-(localX * localX + localY *
                                                                       localY)
                                                   /
                                                   float(2 * (kernel + 1) * 2 *
                                                         (kernel + 1) +
                                                         2 * (kernel + 1) * 2 *
                                                         (kernel + 1)));
            data2[offset++] = 0.0;
            data2[offset++] = 0.0;
            data2[offset++] = 0.0;
        }
    }
    if (quadXmin + kernel * 2 + 1 < _width &&
        quadYmin + kernel * 2 + 1 < _height)
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        quadXmin,
                        quadYmin,
                        kernel * 2 + 1,
                        kernel * 2 + 1,
                        GL_RGBA,
                        GL_FLOAT,
                        data2);

    _tex0->unbind();
}

void CWavesDeformer::updateTime(float deltaTime) {
//    _dt = deltaTime;
    _dtOverall += deltaTime;
}

void CWavesDeformer::setWavesOn(bool wavesOn) {
    _wavesOn = wavesOn;
}

void CWavesDeformer::setWavesAmplitude(float wavesAmplitude) {
    _wavesAmplitude = wavesAmplitude;
}

void CWavesDeformer::setWavesFrequency(float wavesFrequency) {
    _wavesFrequency = wavesFrequency;
}

void CWavesDeformer::setWavesChoppiness(float wavesChoppiness) {
    _wavesChoppiness = wavesChoppiness;
}

void CWavesDeformer::setWavesResolutionX(float wavesResolutionX) {
    _wavesResolutionX = wavesResolutionX;
}

void CWavesDeformer::setWavesResolutionY(float wavesResolutionY) {
    _wavesResolutionY = wavesResolutionY;
}

CWavesDeformer::~CWavesDeformer() {
    delete _fbo0;
    delete _fbo1;
    delete _fbo2;
    delete _tex0;
    delete _tex1;
    delete _tex2;

    _shader.DeleteShaderProgram();
}

void CWavesDeformer::animationStep() {
    glViewport(0, 0, _width, _height);

    _shader.Use();
    _vao.bind();
    _vao.bindBuffers();
    glUniform1iARB(_shader("u_heightFieldTexture"), 0);
    glUniform1f(_shader("u_sideSize"), _width);
    glUniform1i(_shader("u_verticesPerSide"), _verticesPerSide);

    glUniform1f(_shader("u_membraneProperties.h"), _h);
    glUniform1f(_shader("u_membraneProperties.c"), _c);
    glUniform1f(_shader("u_membraneProperties.dt"), _dt);
    glUniform1f(_shader("u_membraneProperties.dtOverall"), _dtOverall);

    glUniform1f(_shader("u_wavesAmplitude"), _wavesAmplitude);
    glUniform1f(_shader("u_wavesFrequency"), _wavesFrequency);
    glUniform1f(_shader("u_wavesChoppiness"), _wavesChoppiness);
    glUniform1f(_shader("u_wavesResoulutionX"), _wavesResolutionX);
    glUniform1f(_shader("u_wavesResoulutionY"), _wavesResolutionY);


    // Water Disturbance Pass
    glUniform1i(_shader("u_isPerlinNoiseCalculations"), 0);
    _tex0->bind();
    _fbo1->bind();
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");

    _tex1->bind();
    _fbo0->bind();
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");
    _fbo0->unbind();

    // Perlin Noise Pass
    if(_wavesOn) {
        glUniform1i(_shader("u_isPerlinNoiseCalculations"), 1);
        _tex0->bind();
        _fbo2->bind();
        glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
        checkErrorOpenGL("CWavesDeformer::renderStep");
        _fbo2->unbind();
    }

    _vao.unbind();
    _shader.UnUse();
}


void CWavesDeformer::bindDisturbanceTexture() {
    _tex0->bind();
}

void CWavesDeformer::unbindDisturbanceTexture() {
    _tex0->unbind();
}

void CWavesDeformer::bindNoiseTexture() {
    if(_wavesOn) {
        _tex2->bind();
    } else {
        bindDisturbanceTexture();
    }
}

void CWavesDeformer::unbindNoiseTexture() {
    _tex2->unbind();
}

void CWavesDeformer::_initShaders() {
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
    _shader.AddUniform("u_membraneProperties.dtOverall");
    _shader.AddUniform("u_isPerlinNoiseCalculations");
    _shader.AddUniform("u_wavesAmplitude");
    _shader.AddUniform("u_wavesFrequency");
    _shader.AddUniform("u_wavesChoppiness");
    _shader.AddUniform("u_wavesResoulutionX");
    _shader.AddUniform("u_wavesResoulutionY");
    _shader.UnUse();
}

void CWavesDeformer::_initVao() {
    Vertex *vertices = _quad.generateVertices();
    GLuint *indices = _quad.generateIndices();
    GLsizei stride = sizeof(Vertex);


    _vao.setBuffer("vertices", GL_ARRAY_BUFFER);
    _vao.setBuffer("indices", GL_ELEMENT_ARRAY_BUFFER);
    _vao.bind();
    _vao.bindBuffers();
    _vao.getBuffer("vertices")->setDataStatic(
            _quad.getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["a_position"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["a_heightFieldTexCoords"], 2, stride,
                              (const GLvoid *) offsetof(Vertex, texCoord));
    _vao.getBuffer("indices")->
            setDataStatic(_quad.getTotalIndices() * sizeof(GLuint),
                          &indices[0]);
    _vao.unbind();

    delete[] vertices;
    delete[] indices;
}

void CWavesDeformer::_initMembraneCoefficients() {
    float N = (float) _verticesPerSide;
    _h = 2. / (N - 1.);
    _c = 0.3;
    _dt = (1. / (N));
    _dtOverall = 0;
}

GLfloat *CWavesDeformer::getCurrentTextureAsVector() {
    GLfloat *textureAsArray = new GLfloat[_width * _height * 8];
    _tex2->bind();
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, textureAsArray);
    _tex2->unbind();
    return textureAsArray;
}