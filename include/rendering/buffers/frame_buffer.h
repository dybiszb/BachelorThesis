//==============================================================================
// Frame buffers are mainly used to off screen rendering purposes. It is often
// useful to e.g. render some part of the scene to a texture for its further
// processing. The class encapsulates all features of glFrameBuffer and
// provides easy to use interface.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <GL/glew.h>
#include "textures/texture_2D.h"
#include "bindable_object.h"

using namespace utils;

namespace rendering {
    class CFrameBuffer : public IBindableObject {
    public:
        /**
         * Creates frame buffer object within OpenGL context and checks for
         * any errors that may occur.
         */
        CFrameBuffer();

        /**
         * Bind object to the active OpenGl context.
         */
        virtual void bind();

        /**
         * Unbind object from the OpenGl active context.
         */
        virtual void unbind();

        /**
         * Attach a texture to the frame buffer object. After a render pass
         * of the buffer, texture will be filled with rendered information.
         *
         * @param texture2D Texture to be filled with rendered information.
         */
        void setColorAttachment(CTexture2D& texture2D);
    };
}

#endif
