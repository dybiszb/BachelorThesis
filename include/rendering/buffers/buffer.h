//==============================================================================
// Class constitutes straightforward encapsulation of OpenGL's buffer i.e.
// data structure, which enables sending a chunk of information into the
// pipeline.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include "bindable_object.h"
#include "error_handling.h"

using namespace utils;

namespace rendering {

    class CBuffer : public IBindableObject {
    public:
        ~CBuffer();

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
         * Bind object to the active OpenGl context.
         */
        virtual void bind();

        /**
         * Unbind object from the OpenGl active context.
         */
        virtual void unbind();

        /**
         * Put data into the data structure with GL_STATIC_DRAW flag.
         * Should be used for data that will be created and set once but used
         * a lot.
         *
         * @param size How many objects one wants to store (in bytes)
         * @param data Array of data to store
         */
        void setDataStatic(GLsizeiptr size, const GLvoid *data);

        /**
         * Put data into the data structure with GL_STREAM_DRAW flag.
         * Should be used for data that will be created, set and used once.
         * Great for orphaning.
         *
         * @param size How many objects one wants to store (in bytes)
         * @param data Array of data to store
         */
        void setDataStream(GLsizeiptr size, const GLvoid *data);

        /**
         * Updates a subset of the buffer object's data store.
         *
         * @param offset Specifies offset into the buffer object's data store
         *               where data replacement will begin, measured in bytes.
         * @param size   How many objects one wants to store (in bytes)
         * @param data   Array of data to store
         */
        void setSubData(GLintptr offset, GLsizeiptr size, const GLvoid *data);

    private:
        GLenum _type;
    };
}

#endif
