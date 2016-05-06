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
#include <glm/glm.hpp>
#include "renderable_object.h"
#include "cube.h"
#include "textures/cubemap_texture.h"

using namespace rendering;
using namespace geometry;
using namespace glm;

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
         * @param TODO
         */
        CSkybox(int sideSize, const char* facesNames[6],
                bool modernShaders);

        /**
         * Renders textured cube (skybox) in the center of world's space
         * coordinates.
         *
         * @param MVP Model-View-Projection matrix of the active camera.
         */
        virtual void render(const float *view,
                            const float *projection);

        /**
         * Updates current camera position for correct drawing of the skybox.
         *
         * @param cameraPosition Current camera position.
         */
        void setCameraPosition(vec3 cameraPosition);

        /**
         * @return Id of the cube map. Can be used to address it in e.g.
         * another shader.
         */
        GLuint getCubemapId();

    private:
        CCubemapTexture _texture;
        vec3 _cameraPosition;
        void _initShader(bool modernShaders);
    };
}


#endif
