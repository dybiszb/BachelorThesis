//==============================================================================
// TODO
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <GL/glew.h>
#include "textures/texture2D.h"

using namespace util;

namespace rendering {
    class CFrameBuffer {
    public:
        CFrameBuffer();
        /**
         * One must bind the frame buffer in order to proceed with the method.
         * Reference is not saved withinf the class body.
         */
        void setColorAttachement(CTexture2D& texture2D);
        void bind();
        void unbind();
    private:
        bool _modernShaders;
        GLuint _id;
    };
}

#endif
