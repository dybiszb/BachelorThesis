//==============================================================================
// Skybox - big cube with inside faces textured! It helps maintaining an
// illusion of an open world. Normally skyboxes moves along with user's
// camera but for purpose of this project it will remain static.
// Class itself allows to specify sides lengths and paths to 6 images
// (for obvious purposes). No movement of the shape is allowed and it is
// always rendered with its center of gravity in the origin of world's
// coordinate space.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include "renderable_object.h"
#include "cube.h"
#include "textures/cubemap_texture.h"

using namespace rendering;
using namespace geometry;

namespace entities {
    class CSkybox : public CRenderableObject,
                    public CCube {
    public:
        /**
         * Enables to specify size of the skybox and path to each of its
         * texture.
         *
         * @param sideSize   How long should be cube's edge?
         * @param facesNames Pointer to vector with faces paths.
         */
        CSkybox(int sideSize, vector<const GLchar *> *facesNames);

        /**
         * Renders textured cube (skybox) in the center of world's space
         * coordinates.
         *
         * @param MVP Model-View-Projection matrix of the active camera.
         */
        virtual void render(const float *MVP);

    private:
        CCubemapTexture _texture;

        void _initShader();
    };
}


#endif
