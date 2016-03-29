// author: dybisz

#include "error_handling.h"

using namespace util;

void util::checkErrorSOIL(int errorId) {
    if (0 == errorId) {
        printf("SOIL error: '%s'\n", SOIL_last_result());
    }
}

void util::checkErrorOpenGL(string errorSource) {
    GLenum err = GL_NO_ERROR;
    if ((err = glGetError()) != GL_NO_ERROR) {
        cout << errorSource << " || OpenGL error no: " << err << std::endl;
    }
}

void util::checkErrorFrameBuffer(string errorSource) {
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        cout << errorSource << " || FrameBufferStatus != "
                                       "GL_FRAMEBUFFER_COMPLETE " <<
                std::endl;
    }
}