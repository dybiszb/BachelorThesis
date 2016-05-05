//==============================================================================
// TODO
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include "error_handling.h"

using namespace utils;
using namespace std;

namespace rendering {

    class CTexture2D {
    public:
        /**
         * Creates black texture of given sizes.
         */
        CTexture2D(int width, int height);
        // Constructor that takes image data
        // Constructor that takes path to image (SOIL)
        ~CTexture2D();
        void bind();
        void unbind();
        GLuint getId();
    private:
        GLuint _id;

    };
}

#endif
