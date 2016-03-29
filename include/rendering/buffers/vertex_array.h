//==============================================================================
// However in the current form Vertex Array Object consists of two buffers of
// types: GL_ELEMENT_ARRAY_BUFFER and GL_ARRAY_BUFFER, it can store additional
// information (like normals or colors) in the latter one. It can been
// achieved e.g via introducing Vertex structure, wchich consists of several
// vectors.
// In addition, class has all functionality needed to properly used it
// within OpenGL application. It provides bind/unbind methods, assigning
// float attributes (shader related) and obviously: filling up the buffers.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <buffers/buffer.h>
#include <GL/glew.h>
#include "error_handling.h"

using namespace util;

namespace rendering {

    class CVertexArray {
    public:
        /**
         * Initializes buffers and generates Vertex Array in OpenGL context.
         */
        CVertexArray();

        /**
         * Deletes Vertex Array object along with its buffers.
         */
        ~CVertexArray();

        /**
         * Binds VAO to the current OpenGL context via glBindVertexArray method.
         */
        void bind();

        /**
        * Unbinds VAO from current OpenGL context.
        */
        void unbind();

        /**
         * Fill up vertices buffer with data.
         */
        void setVertices(GLsizeiptr size, const GLvoid *data);

        /**
         * Fill up indices buffer with data.
         */
        void setIndices(GLsizeiptr size, const GLvoid *data);

        /**
         * By default method should be used with Vertex structure but it is
         * not obligatory. Basicly the procedure wraps process of asigning
         * shader's attribute to the VAO. The purpose of this is to inform
         * shader how to interpret data stored in buffers.
         */
        void assignFloatAttribute(GLuint index, GLint size, GLsizei stride,
                                  const GLvoid *pointer);

        /**
         * Returns id of VAO withing OpenGL context.
         */
        GLuint getId();

    private:
        GLuint _id;
        CBuffer _vertices;
        CBuffer _indices;
    };

}


#endif //BACHELOR_WATER_VERTEX_ARRAY_H
