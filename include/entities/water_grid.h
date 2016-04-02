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
#include "renderable_object.h"
#include "grid.h"
#include "vertex.h"
#include "error_handling.h"
#include "textures/texture2D.h"
#include "waves_deformer.h"

using namespace rendering;
using namespace geometry;
using namespace util;
using namespace glm;
using namespace std;

namespace entities {
    class CWaterGrid : public CRenderableObject,
                       public CGrid {
    public:
        CWaterGrid(int verticesOnWidth, int verticesOnHeight, float sideSize,
                   glm::vec2 bottomCorner, bool modernShaders);
        ~CWaterGrid();
        virtual void render(const float *MVP);

        void updateTime(float currentTime);

        /**
         * Updates current camera position for correct drawing of the water
         * grid.
         *
         * @param cameraPosition Current camera position.
         */
        void setCameraPosition(vec3 cameraPosition);

        void setSkyboxCubemapId(GLuint cubemapId);
    private:
        CWavesDeformer _wavesDeformer;
        GLfloat _currentTime;
        vec3 _cameraPosition;
        GLuint _cubemapId;
        GLfloat _sideSize;
        void _initShader(bool modernShaders);
    };
}

#endif
