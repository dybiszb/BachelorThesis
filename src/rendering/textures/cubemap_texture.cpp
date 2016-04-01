// author: dybisz

#include "textures/cubemap_texture.h"

using namespace rendering;

CCubemapTexture::CCubemapTexture(vector<const GLchar *>* facesNames) {
    loadTexture(facesNames);
}

CCubemapTexture::~CCubemapTexture() {
    glDeleteTextures(1, &_id);
}

void CCubemapTexture::loadTexture(vector<const GLchar *> *facesNames) {
    _id = SOIL_load_OGL_cubemap
            (
                    (*facesNames)[0],
                    (*facesNames)[1],
                    (*facesNames)[2],
                    (*facesNames)[3],
                    (*facesNames)[4],
                    (*facesNames)[5],
                    SOIL_LOAD_RGB,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS
            );
    checkErrorOpenGL("CCubemapTexture::loadTexture");
    checkErrorSOIL(_id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    checkErrorOpenGL("CCubemapTexture::loadTexture");
}

void CCubemapTexture::bind(){
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    checkErrorOpenGL("CCubemapTexture::bind");
}

void CCubemapTexture::unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint CCubemapTexture::getId() {
    return _id;
}