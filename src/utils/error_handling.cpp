// author: dybisz

#include "error_handling.h"

using namespace utils;

void utils::checkErrorSOIL(int errorId) {
    if (0 == errorId) {
        printf("SOIL error: '%s'\n", SOIL_last_result());
    }
}

void utils::checkErrorOpenGL(string errorSource) {
    GLenum err = GL_NO_ERROR;
    if ((err = glGetError()) != GL_NO_ERROR) {
        cout << errorSource << " || OpenGL error no: " << err << std::endl;
    }
}

void utils::checkErrorFrameBuffer(string errorSource) {
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        cout << errorSource << " || FrameBufferStatus != "
                                       "GL_FRAMEBUFFER_COMPLETE " <<
                std::endl;
    }
}

void utils::checkErrorCubemapId(string errorSource, int cubemapId) {
    if(cubemapId == -1) {
        cout << errorSource << " || Cubemap's id not set."<< std::endl;
    }
}