//==============================================================================
// Builder pattern implementation. TODO finish
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef SKYBOX_BUILDER_H
#define SKYBOX_BUILDER_H

#include <glm/glm.hpp>
#include "skybox_cube.h"

using namespace glm;
using namespace std;

namespace entities {

    class CSkyboxBuilder {

    private:
        float _sideSize;
        vector<const GLchar *> *_faces;
        bool _modernShaders;

    public:
        static const float defaultSideSize;
        static vector<const GLchar *>* defaultFaces;
        static const bool defaultModernShaders;

        /**
         * Basically initializes all internal values with default quantities.
         */
        CSkyboxBuilder();

        /**
         * Releases dynamically allocated default values.
         */
        ~CSkyboxBuilder();

        /**
         * Produce the skybox using collected parameter's values.
         */
        CSkybox *build();

        /**
         * Sets new length of skybox's side.
         *
         * @param sideSize How long will be the edge of skybox-cube?
         */
        CSkyboxBuilder &setSideSize(const float sideSize);

        /**
         * Sets paths to textures that will be loaded as 6 faces of the cube.
         *
         * @param defaultFaces Pointer to the vector filled with 6 paths to
         *                     textures that will be mapped on the cube.
         */
        CSkyboxBuilder &setFaces(vector<const GLchar *> *defaultFaces);

        /**
         * Use modern shaders?
         *
         * @param modernShaders If true 330 core shaders will be used.
         *                      Otherwise version 120 will be loaded.
         */
        CSkyboxBuilder &setModernShaders(const bool modernShaders);
    };
}


#endif
