// author: dybisz

#include "buffers/buffer.h"

using namespace rendering;

CBuffer::CBuffer(GLenum type) : _type(type) {
    glGenBuffers(1, &_id);
}

void CBuffer::bind() {
    glBindBuffer (_type, _id);
}

void CBuffer::setData(GLsizeiptr size, const GLvoid * data) {
    glBufferData (_type, size, data, GL_STATIC_DRAW);
}

void CBuffer::deleteBuffer() {
    glDeleteBuffers(1, &_id);
}