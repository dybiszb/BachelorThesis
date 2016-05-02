//==============================================================================
// Builder pattern implementation. TODO finish
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef WATER_BUILDER_H
#define WATER_BUILDER_H

#include <glm/glm.hpp>
#include "water_grid.h"

using namespace glm;

namespace entities {

    class CWaterBuilder {

    private:
    //==========================================================================
    //  Water Constructor Parameters
    //--------------------------------------------------------------------------
        int   _quadsPerSide;
        float _sideSize;
        vec2  _bottomCorner;
        int   _skyboxId;
        bool  _modernShaders;
        int   _viewportWidth;
        int   _viewportHeight;

    public:
    //==========================================================================
    //  Water Constructor Default Values
    //--------------------------------------------------------------------------
        static const int   defaultQuadsPerSide;
        static const float defaultSideSize;
        static const vec2  defaultBottomCorner;
        static const int   defaultSkyboxId;
        static const bool  defaultModernShaders;
        static const int   defaultViewportWidth;
        static const int   defaultViewportHeight;

        /**
         * Basically initializes all internal values with default quantities.
         */
        CWaterBuilder();

        /**
         * Produce the water grid using collected parameter's values.
         */
        CWaterGrid *build();

        /**
         * Sets new number of quads per side.
         *
         * @param How many quads per side sould be in newly created water grid?
         */
        CWaterBuilder& setQuadsPerSide(const int quadsPerSide);

        /**
         * Sets new length of water grid's side.
         *
         * @param How long will be side of the grid in world coordinates?
         */
        CWaterBuilder& setSideSize(const float sideSize);

        /**
         * Sets new bottom corner point of the water grid.
         *
         * @param bottomCorner From, which point on XZ-plane water grid should
         *                     start draw itself?
         */
        CWaterBuilder& setBottomCorner(const vec2 bottomCorner);

        /**
         * Connects water grid with pre-loaded skybox.
         *
         * @param From, which point on XZ-plane water grid should start draw
         *        itself?
         */
        CWaterBuilder& setSkyboxId(int skyboxId);

        /**
         * Use modern shaders?
         *
         * @param If true 330 core shaders will be used. Otherwise version
         *        120 will be loaded.
         */
        CWaterBuilder& setModernShaders(const bool modernShaders);

        /**
         * Set viewport resolution.
         *
         * @param viewportWidth
         * @param viewportHeight
         */
        CWaterBuilder& setViewport(const int viewportWidth,
                                   const int viewportHeight);
    };
}


#endif
