// author: dybisz

#include "buffers/vertex_array.h"

using namespace rendering;

CVertexArray::CVertexArray(){
    glGenVertexArrays(1, &_id);
    checkErrorOpenGL("CVertexArray::CVertexArray");
}

CVertexArray::~ CVertexArray() {
    for (auto &pair : _buffers) delete pair.second;
    glDeleteVertexArrays(1, &_id);
//    checkErrorOpenGL(_callerName + ": CVertexArray::~ CVertexArray");
}

void CVertexArray::setCaller(string callerName) {
    _callerName = callerName;
}

void CVertexArray::bind() {
    glBindVertexArray(_id);
    checkErrorOpenGL("CVertexArray::bind");
}

void CVertexArray::unbind() {
    glBindVertexArray(0);
    checkErrorOpenGL("CVertexArray::unbind");
}

void CVertexArray::bindBuffers() {
    for(auto &pair : _buffers) pair.second->bind();
    checkErrorOpenGL("CVertexArray::bindBuffers");
}

void CVertexArray::unbindBuffers() {
    for(auto &pair : _buffers) pair.second->unbind();
    checkErrorOpenGL("CVertexArray::unbindBuffers");
}

void CVertexArray::setBuffer(string name, GLenum type) {
    _buffers[name] = new CBuffer(type);
}

CBuffer* CVertexArray::getBuffer(string name) {
    return _buffers.at(name);
}

void CVertexArray::assignFloatAttribute(GLuint index, GLint size,
                                        GLsizei stride, const GLvoid *pointer) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
    checkErrorOpenGL("CVertexArray::assignFloatAttribute");
}
