//==============================================================================
// It happens that one wants to collect some set of objects and bind them all
// to the currently active OpenGL context. Following interface's purpose is -
// using polymorphism, allow the user to perform such an operation. Because
// different types of objects need to call different binding methods, crucial
// methods (i.e. bind(), unbind()) are declared virtual. Although
// definition of getId() method a little bit disturbs an interface pattern,
// there is no need declare it over and over again in each object, where its
// definition will look the same.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef BINDABLE_OBJECT_H
#define BINDABLE_OBJECT_H

#include <GL/glew.h>
#include <string>

using namespace std;

namespace rendering {

    class IBindableObject {
    public:
        /**
         * Bind object to the active OpenGl context.
         */
        virtual void bind() = 0;

        /**
         * Unbind object from the OpenGl active context.
         */
        virtual void unbind() = 0;

        /**
         * Accessing an object's id is often a vital part. E.g. attaching
         * textures to a frame buffer objects would be impossible without it.
         *
         * @return Id of an object in OpenGL context.
         */
        virtual GLuint getId() {
            return _id;
        };

    protected:
        GLuint _id;
    };

}

#endif
