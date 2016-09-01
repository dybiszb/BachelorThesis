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

CTexture2D::CTexture2D(string path) {
    _id = SOIL_load_OGL_texture
            (
                    path.c_str(),
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                    SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
//    _id = _textureFromFile(path);
    checkErrorSOIL(_id);
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

// from OpenGL Cookbook
GLint CTexture2D::_textureFromFile(string fullPath)
{
    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    int texture_width = 0, texture_height = 0, channels=0;

    std::string full_filename = fullPath;

    GLubyte* pData = SOIL_load_image(full_filename.c_str(), &texture_width, &texture_height, &channels, SOIL_LOAD_AUTO);
    if(pData == NULL) {
        cerr<<"Cannot load image: "<<full_filename.c_str()<<endl;
        exit(EXIT_FAILURE);
    }

    //Flip the image on Y axis
    int i,j;
    for( j = 0; j*2 < texture_height; ++j )
    {
        int index1 = j * texture_width * channels;
        int index2 = (texture_height - 1 - j) * texture_width * channels;
        for( i = texture_width * channels; i > 0; --i )
        {
            GLubyte temp = pData[index1];
            pData[index1] = pData[index2];
            pData[index2] = temp;
            ++index1;
            ++index2;
        }
    }

    GLenum format = GL_RGBA;
    switch(channels) {
        case 1: format = GL_LUMINANCE_ALPHA; break;
        case 2:	format = GL_RG32UI; break;
        case 3: format = GL_RGB;	break;
        case 4: format = GL_RGBA;	break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, texture_width, texture_height, 0, format, GL_UNSIGNED_BYTE, pData);
    SOIL_free_image_data(pData);
    return id;
}