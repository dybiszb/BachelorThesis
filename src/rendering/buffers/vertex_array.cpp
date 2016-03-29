// author: dybisz

#include "buffers/vertex_array.h"

using namespace rendering;

CVertexArray::CVertexArray() : _vertices(GL_ARRAY_BUFFER),
                               _indices(GL_ELEMENT_ARRAY_BUFFER) {

    glGenVertexArrays(1, &_id);
    checkErrorOpenGL("CVertexArray::CVertexArray");
}

CVertexArray::~ CVertexArray() {
    _vertices.deleteBuffer();
    _indices.deleteBuffer();
    glDeleteVertexArrays(1, &_id);
    checkErrorOpenGL("CVertexArray::~ CVertexArray");
}

void CVertexArray::bind() {
    glBindVertexArray(_id);
    checkErrorOpenGL("CVertexArray::bind");
    _vertices.bind();
    _indices.bind();
}

void CVertexArray::unbind() {
    glBindVertexArray(0);
    checkErrorOpenGL("CVertexArray::unbind");
}

void CVertexArray::setVertices(GLsizeiptr size, const GLvoid *data) {
    _vertices.setData(size, data);
}

void CVertexArray::setIndices(GLsizeiptr size, const GLvoid *data) {
    _indices.setData(size, data);
}

void CVertexArray::assignFloatAttribute(GLuint index, GLint size, GLsizei
stride, const GLvoid *pointer) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
    checkErrorOpenGL("CVertexArray::assignFloatAttribute");
}

GLuint CVertexArray::getId() {
    return _id;
}
