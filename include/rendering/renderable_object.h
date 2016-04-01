//==============================================================================
// Class constitutes core of any object, which one wants to draw on the
// screen. It forces to implement rendering method and manages shader
// program and vertex array object. All cleaning methods of inner objects are
// cover by the destructor. Main aim of the class, besides obvious
// encapsulation, is providing polymorphism of all drawable objects on the
// scene.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include <glsl_shader.h>
#include <buffers/vertex_array.h>

namespace rendering {

    class CRenderableObject {
    public:

        /**
         * Must be implemented in order to specify how object should be
         * render. Normally one wants to inherit after the class and provide
         * OpenGL methods inside the function.
         */
        virtual void render(const float *MVP) = 0;

        /**
         * Manages deleting shader program from OpenGL context. In contrary,
         * Vertex Array Object takes care of himself.
         */
        virtual ~CRenderableObject();

    protected:
        GLSLShader _shader;
        CVertexArray _vao;
    };

}


#endif