// author: dybisz

#include "buffers/frame_buffer.h"

using namespace rendering;

CFrameBuffer::CFrameBuffer() : _modernShaders(false){
    glGenFramebuffers(1, &_id);

    checkErrorFrameBuffer("CFrameBuffer::CFrameBuffer");
    checkErrorOpenGL("CFrameBuffer::CFrameBuffer");
}

void CFrameBuffer::setColorAttachement(CTexture2D &texture2D) {
    if(_modernShaders) {
        glFramebufferTexture(GL_FRAMEBUFFER,
                             GL_COLOR_ATTACHMENT0,
                             texture2D.getId(),
                             0);
    } else {
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                                  GL_TEXTURE_2D, texture2D.getId(), 0);
    }

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    checkErrorFrameBuffer("CFrameBuffer::setColorAttachement");
    checkErrorOpenGL("CFrameBuffer::setColorAttachement");
}

void CFrameBuffer::bind() {
    if(_modernShaders) {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
    }else {
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _id);
    }

    checkErrorOpenGL("CFrameBuffer::bind");
}

void CFrameBuffer::unbind() {

    if (_modernShaders) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    } else {
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

    checkErrorOpenGL("CFrameBuffer::unbind");
}