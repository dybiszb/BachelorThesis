// author: dybisz

#include "waves_deformer.h"

// TODO wdth and height change to side length
CWavesDeformer::CWavesDeformer(int width, int height)
        : _width(width),
          _height(height) {

    _verticesPerSide = height;

    _fbo0 = new CFrameBuffer();
    _fbo1 = new CFrameBuffer();
    _tex0 = new CTexture2D(width, height);
    _tex1 = new CTexture2D(width, height);

    _fbo0->bind();
    _fbo0->setColorAttachment(*_tex0);
    _fbo0->unbind();

    _fbo1->bind();
    _fbo1->setColorAttachment(*_tex1);
    _fbo1->unbind();

    _initMembraneCoefficients();
    _initShaders();
    _initVao();
}

void CWavesDeformer::disturbSurface(vec2 &quad, float amount) {
    _tex0->bind();

    GLfloat data[4] = {amount, 0, 0, 0};
//    glTexSubImage2D(GL_TEXTURE_2D,
//                    0,
//                    quad.x,
//                    quad.y,
//                    1,
//                    1,
//                    GL_RGBA,
//                    GL_FLOAT,
//                    data);

    ////////// TEMPORARY /////////////////////
    int kernel = 18;


    int quadXmin = (quad.x - kernel < 0 ) ? 0 : (quad.x - kernel);
    int quadXmax = (quad.x + kernel >= _width-2 ) ? _width-2 : (quad.x +
            kernel);
    int quadYmin = (quad.y - kernel < 0 ) ? 0 : (quad.y - kernel);
    int quadYmax = (quad.y + kernel >= _height -2) ? _height-2 : (quad.y +
            kernel);

    int data2Size = 4 * (quadXmax - quadXmin + 1) *(quadYmax - quadYmin + 1);

    GLfloat data2[data2Size];

    cout << "quad.x: " << quad.x << endl;
    cout << "quadXmin: " << quadXmin << endl;
    cout << "quadXmax: " << quadXmax << endl;

    int offset = 0;
    for(int y = quadYmin; y <=quadYmax; y++) {
        for(int x = quadXmin; x <= quadXmax; x++) {
            float localX = quadXmin + x;
            float localY = quadYmin + y;
            localX = x - quad.x;
            localY = y - quad.y;

            data2[offset++] = 2.0 + (-(localX * localX + localY * localY)/float
                    (100.0));
            data2[offset++] = 0.0;
            data2[offset++] = 0.0;
            data2[offset++] = 0.0;
        }
    }

    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    quadXmin,
                    quadYmin,
                    quadXmax - quadXmin,
                    quadYmax - quadYmin,
                    GL_RGBA,
                    GL_FLOAT,
                    data2);

    _tex0->unbind();
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
    _vao.bindBuffers();

    glUniform1iARB(_shader("u_heightFieldTexture"), 0);
    glUniform1f(_shader("u_sideSize"), _width);
    glUniform1i(_shader("u_verticesPerSide"), _verticesPerSide);

    glUniform1f(_shader("u_membraneProperties.h"), _h);
    glUniform1f(_shader("u_membraneProperties.c"), _c);
    glUniform1f(_shader("u_membraneProperties.dt"), _dt);

    _tex0->bind();
    _fbo1->bind();
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");

    _tex1->bind();
    _fbo0->bind();
    glDrawElements(GL_TRIANGLES, _quad.getTotalIndices(), GL_UNSIGNED_INT, 0);
    checkErrorOpenGL("CWavesDeformer::renderStep");
    _fbo0->unbind();

    _vao.unbind();
    _shader.UnUse();
}


void CWavesDeformer::bindTexture() {
    _tex0->bind();
}

void CWavesDeformer::unbindTexture() {
    _tex0->unbind();
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
    _vao.getBuffer("vertices")->setDataStatic(_quad.getTotalVertices() * sizeof(Vertex), &vertices[0]);
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
    _c = 1.;
    _dt = 1. / (N);
}