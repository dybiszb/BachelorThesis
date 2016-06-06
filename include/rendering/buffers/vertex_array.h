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
#include <cstddef>
#include <GL/glew.h>
#include <map>
#include <string>
#include "bindable_object.h"
#include "error_handling.h"

using namespace utils;
using namespace std;

namespace rendering {

    class CVertexArray : public IBindableObject {
    public:
        CVertexArray();
        ~CVertexArray();

        /**
         * Bind the object to the active OpenGl context.
         */
        virtual void bind();

        /**
         * Unbind the object from the OpenGl active context.
         */
        virtual void unbind();

        /**
         * Binds all buffers assigned to the vertex array object.
         */
        void bindBuffers();

        /**
         * Unbinds all buffers assigned to the vertex array object.
         */
        void unbindBuffers();

        /**
         * Adds a buffer of a given type to the vertex array object.
         *
         * @param name Name of the buffer. It is the only way to directly
         *             access the proper buffer later on.
         * @param type Type of the buffer that one wants to create. Normally
         *             it is either GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER.
         */
        void setBuffer(string name, GLenum type);

        /**
         * Allows to acces some particular buffer by its name.
         *
         * @param name Name of a buffer one wants to access.
         *
         * @return When buffer of a given name exists procedure returns its
         *         pointer. Otherwise exception of type std::out_of_range is
         *         thrown.
         */
        CBuffer* getBuffer(string name);

        /**
         * By default method should be used with Vertex structure but it is
         * not obligatory. Basically the procedure wraps process of assigning
         * shader's attribute to the VAO. The purpose of this is to inform
         * shader how to interpret data stored in buffers.
         */
        void assignFloatAttribute(GLuint index, GLint size, GLsizei stride,
                                  const GLvoid *pointer);

    private:
        map<string, CBuffer *> _buffers;
    };

}


#endif //BACHELOR_WATER_VERTEX_ARRAY_H
