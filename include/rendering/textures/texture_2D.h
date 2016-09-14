//==============================================================================
// The class encapsulates OpenGL methods related to managing two dimensional
// texture. One can either create empty (black) texture with specified with
// and height or load it directly from the image.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include <src/SOIL.h>
#include "bindable_object.h"
#include "error_handling.h"

using namespace utils;
using namespace std;

namespace rendering {

    class CTexture2D : public IBindableObject {
    public:
        ~CTexture2D();

        /**
         * Creates black texture of given sizes.
         *
         * @param width Texture's width
         * @param width Texture's height
         */
        CTexture2D(int width, int height);

        /**
         * Creates texture from image on provided path.
         *
         * @param Path to an image.
         */
        CTexture2D(string path);

        /**
         * Bind object to the active OpenGl context.
         */
        virtual void bind();

        /**
         * Unbind object from the OpenGl active context.
         */
        virtual void unbind();

    private:
        GLint _textureFromFile(string fullPath);
    };
}

#endif
