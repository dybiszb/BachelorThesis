//==============================================================================
// Class encapsulates all methods related to cubemap object within OpenGL
// context. One can specify paths to 6 images (for each side of the cube) and
// it will automatically load them to the pipeline and create texture's id.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef CUBEMAP_TEXTURE_H
#define CUBEMAP_TEXTURE_H

#include <src/SOIL.h>
#include <GL/glew.h>
#include "error_handling.h"
#include <vector>

using namespace utils;
using namespace std;

namespace rendering {

    class CCubemapTexture {
    public:
        /**
         * Automatically calls loadTexture method with faces names provided
         * as an argument.
         *
         * @param facesNames Six paths to textures defining a cube.
         */
        CCubemapTexture(const char* facesNames[6]);

        /**
         * Releases textures from OpenGL context.
         */
        ~CCubemapTexture();

        /**
         * Loads textures of provided paths into OpenGL context. Reference
         * used to prevent needless copying.
         *
         * @param facesNames Six paths to textures defining a cube.
         */
        void loadTexture(const char* facesNames[6]);

        /**
         * Binds textures to current GL_TEXTURE_CUBE_MAP object.
         */
        void bind();

        /**
         * Releases textures from GL_TEXTURE_CUBE_MAP object.
         */
        void unbind();

        /**
         * Returns id of the texture withing OpenGL context.
         */
        GLuint getId();

    private:
        GLuint _id;
    };
}

#endif
