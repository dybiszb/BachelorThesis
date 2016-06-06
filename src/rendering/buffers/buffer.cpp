// author: dybisz

#include "buffers/buffer.h"

using namespace rendering;

CBuffer::~CBuffer() {
    glDeleteBuffers(1, &_id);
}

CBuffer::CBuffer(GLenum type) : _type(type) {
    glGenBuffers(1, &_id);
    checkErrorOpenGL("CBuffer::CBuffer");
}

void CBuffer::bind() {
    glBindBuffer (_type, _id);
    checkErrorOpenGL("CBuffer::bind()");
}

void CBuffer::unbind() {
    glBindBuffer (_type, _id);
    checkErrorOpenGL("CBuffer::unbind()");
}

void CBuffer::setDataStatic(GLsizeiptr size, const GLvoid * data) {
    glBufferData (_type, size, data, GL_STATIC_DRAW);
    checkErrorOpenGL("CBuffer::setDataStatic");
}

void CBuffer::setDataStream(GLsizeiptr size, const GLvoid * data) {
    glBufferData (_type, size, data, GL_STREAM_DRAW);
    checkErrorOpenGL("CBuffer::setDataStream");
}

void CBuffer::setSubData(GLintptr offset, GLsizeiptr size, const GLvoid *data) {
    glBufferSubData(_type, offset, size, data);
    checkErrorOpenGL("CBuffer::setSubData");
}