//==============================================================================
// Class in charge of creating square tile of water. Animation of surface
// follows shallow water equations. By assumption water must be bounded
// by skybox to properly perform its ray-casting operations.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef WATER_GRID_H
#define WATER_GRID_H

#include <iostream>
#include <string.h>
#include "renderable_object.h"
#include "grid.h"
#include "vertex.h"
#include "error_handling.h"
#include "textures/texture_2D.h"
#include "waves_deformer.h"
#include "camera.h"
#include "rays_functions.h"

using namespace rendering;
using namespace geometry;
using namespace utils;
using namespace glm;
using namespace std;

namespace entities {
    class CWaterGrid : public CRenderableObject,
                       public CGrid {
    public:
        class CWaterBuilder;

        CWaterGrid(int quadsPerSide, float sideSize,
                   vec2 bottomCorner,  GLuint cubemapId,
                   bool modernShaders, int viewportWidth,
                   int viewportHeight, bool animation, bool lightOn);

        ~CWaterGrid();

        virtual void render(const float *view,
                            const float *projection);

        void updateTime(float currentTime);

        /**
         * Updates current camera position for correct drawing of the water
         * grid.
         *
         * @param cameraPosition Current camera position.
         */
        void setCameraPosition(vec3 cameraPosition);
        void setLightDirections(vec3& lightDirection);
        void intersect(vec2& viewportCoordinates, CCustomCamera& camera,
                       float amount);
        void intersect(vec2& quadCoordinates, float amount);
        int getVerticesPerSide();
        void setAnimation(bool animation);
        bool getAnimation();
        bool getLightOn();
        void setLightOn(bool lightOn);
    private:
        CWavesDeformer _wavesDeformer;
        GLfloat        _currentTime;
        vec3           _cameraPosition;
        vec3           _lightDirection;
        float          _cameraAngle;
        GLuint         _cubemapId;
        GLfloat        _sideSize;
        GLuint         _verticesPerSide;
        int            _viewportWidth;
        int            _viewportHeight;
        vec3           _box[2];
        bool           _animation;
        bool           _lightOn;

        void _initShader(bool modernShaders);
    };

}

//#include "water_builder.h"

#endif
