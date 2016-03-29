//==============================================================================
// Class constitutes straightforward encapsulation of OpenGl's buffer i.e.
// data structure, which enables sending a chunk of information into the
// pipeline.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

namespace rendering {

    class CBuffer {
    public:
        /**
         * Two existing types of buffers (at least in this project) can be
         * manage via this class: GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
         * Both of them are indispensable part of Vertex Array object.
         *
         * @param type Specify OpenGL's enum appropriate for desired type of
         *             buffer.
         */
        CBuffer(GLenum type);

        /**
         * Bind buffer to the OpenGl's context.
         */
        void bind();

        /**
         * Put data into the data structure.
         *
         * @param size How many objects one wants to store
         * @param data Array of data to store
         */
        void setData(GLsizeiptr size, const GLvoid *data);

        /**
         * Release OpenGL from this buffer.
         */
        void deleteBuffer();

    private:
        GLuint _id;
        GLenum _type;
    };
}

#endif
