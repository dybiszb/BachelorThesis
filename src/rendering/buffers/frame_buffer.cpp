// author: dybisz

#include "buffers/frame_buffer.h"

using namespace rendering;

CFrameBuffer::CFrameBuffer() {
    glGenFramebuffers(1, &_id);

    checkErrorFrameBuffer("CFrameBuffer::CFrameBuffer");
    checkErrorOpenGL("CFrameBuffer::CFrameBuffer");
}

void CFrameBuffer::setColorAttachment(CTexture2D &texture2D) {
    glFramebufferTexture(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0,
                         texture2D.getId(),
                         0);


    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    checkErrorFrameBuffer("CFrameBuffer::setColorAttachement");
    checkErrorOpenGL("CFrameBuffer::setColorAttachement");
}

void CFrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, IBindableObject::_id);
    checkErrorOpenGL("CFrameBuffer::bind");
}

void CFrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkErrorOpenGL("CFrameBuffer::unbind");
}