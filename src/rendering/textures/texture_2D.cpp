// author: dybisz

#include "textures/texture_2D.h"
#include <iostream>

using namespace rendering;

CTexture2D::CTexture2D(int width, int height) {
    std::vector<GLfloat> data(4 * width * height, 0.0);

    glGenTextures(1, &_id);
    checkErrorOpenGL("CTexture2D::CTexture2D::glGenTextures");

    CTexture2D::bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA,
                 GL_FLOAT, &data[0]);
    checkErrorOpenGL("CTexture2D::CTexture2D::glTexSubImage2D");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    CTexture2D::unbind();
}

CTexture2D::~CTexture2D() {
    glDeleteTextures(1, &_id);
    checkErrorOpenGL("CTexture2D::~CTexture2D");
}

void CTexture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, _id);
    checkErrorOpenGL("CTexture2D::bind");
}

void CTexture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    checkErrorOpenGL("CTexture2D::unbind");
}

GLuint CTexture2D::getId() {
    return _id;
}