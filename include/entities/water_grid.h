//==============================================================================
// Class in charge of creating square tile of water. Animation of surface
// follows shallow water equations. By assumption water must be bounded
// by skybox to properly perform its ray-casting operations.
//
// NOTE: Private methods, as an internal part of the class rather than public
//       interface, are not commented.
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
#include "custom_camera.h"
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
        /**
         * Following class is the preferred way of instantiating CWaterGrid
         * object.
         */
        class CWaterBuilder;

        ~CWaterGrid();

        /**
         * @param quadsPerSide   Number of generated quads (per side).
         * @param sideSize       Length of the grid side.
         * @param bottomCorner   Bottom left corner of the grid.
         * @param cubemapId      Id of skybox cubemap texture.
         * @param modernShaders  A legacy parameter. Now deprecated.
         * @param viewportWidth  Scene resolution width.
         * @param viewportHeight Scene resolution height.
         * @param animation      Should the grid be animated (can be changed
         *                       during runtime)?
         * @param lightOn        Should the grid be shaded (can be changed
         *                       during runtime)?
         */
        CWaterGrid(int quadsPerSide, float sideSize,
                   vec2 bottomCorner,  GLuint cubemapId,
                   bool modernShaders, int viewportWidth,
                   int viewportHeight, bool animation, bool lightOn);

        /**
         * Water grid is rendered with usage of shipped matrices.
         *
         * @param view       View matrix of the scene.
         * @param projection Projection matrix of the scene.
         */
        void render(const float *view,
                            const float *projection);

        /**
         * Internally vertices of the grid are represented as a texture.
         * Following method gathers them and put into one array. For further
         * information please refer to CWavesDeformer's
         * getCurrentTextureAsVector method.
         */
        GLfloat* getHeightfieldAsArray();

        /**
         * Update time and allow grid to perform the animation.
         *
         * @param Current time.
         */
        void updateTime(float currentTime);

        /**
         * Updates current camera position for correct drawing of the water
         * grid.
         *
         * @param cameraPosition Current camera position.
         */
        void setCameraPosition(vec3 cameraPosition);

        /**
         * Updates current light direction. If lights are on, the grid will
         * be shaded using the direction.
         *
         * @param lightDirection Three dimensional vector with light direction.
         */
        void setLightDirections(vec3& lightDirection);

        /**
         * Disturbs particular water area based on provided point in the scene.
         *
         * @param intersectionPoint Coordinates of intersection point.
         * @param amount            How much one wants to disturb the area
         *                          (height of the disturbance function.)
         * @param kernel            Area size. E.g. kernel = 4 will mean that
         *                          9x9 area will be disturbed (4 to the left
         *                          of the center and 4 to the right, and
         *                          center itself gives 9)
         * @param flatness          Parameter 'a' in the formula. Determines
         *                          steepness of a particular disturbance.
         */
        void strictWaterGridDisturbance(vec2& intersectionPoint,
                                                    float amount, int kernel,
                                                    float flatness);

        /**
         * Disturbs particular water area based on provided point on the
         * screen.
         *
         * @param viewportCoordinates (x,y) coordinates of the screen.
         * @param camera              Scene's active camera.
         * @param amount              How much one wants to disturb the area
         *                            (height of the disturbance function.)
         * @param kernel              Area size. E.g. kernel = 4 will mean that
         *                            9x9 area will be disturbed (4 to the left
         *                            of the center and 4 to the right, and
         *                            center itself gives 9)
         * @param flatness            Parameter 'a' in the formula. Determines
         *                            steepness of a particular disturbance.
         */
        void areaIntersect(vec2& viewportCoordinates, CCustomCamera& camera,
                       float amount, int kernel, float flatness);

        /**
         * Disturbs texture at a specified point. Appropriate pixel will get
         * specified value.
         *
         * @param quad   (u,v) coordinates of the texture that will be disturbed.
         * @param amount Value that will be saved in the specified pixel.
         */
        void pointIntersect(vec2& quadCoordinates, float amount);

        /**
         * Disturbs texture at a specified point. Appropriate pixel will get
         * specified value.
         *
         * @param quad    (u,v) coordinates of the texture that will be
         *                 disturbed.
         * @param amount   Value that will be saved in the specified pixel.
         * @param kernel   Area size. E.g. kernel = 4 will mean that
         *                 9x9 area will be disturbed (4 to the left
         *                 of the center and 4 to the right, and
         *                 center itself gives 9)
         * @param flatness Parameter 'a' in the formula. Determines
         *                 steepness of a particular disturbance.
         */
        void pointIntersect(vec2& quadCoordinates, float amount, int kernel, float flatness);

        /**
         * @return Number of quads per side.
         */
        int getVerticesPerSide();

        /**
         * @param If true water will be animated, otherwise animation will
         *        stop immediately.
         */
        void setAnimation(bool animation);

        /**
         * @return True if animation is running, false otherwise.
         */
        bool getAnimation();

        /**
         * @return True if lights are on, false otherwise.
         */
        bool getLightOn();

        /**
         * @param lightOn If true water will be shaded with directional
         *                light, otherwise not.
         */
        void setLightOn(bool lightOn);

        /**
         * @param wavesOn If true waves animation will be displayed,
         *                otherwise not.
         */
        void setWavesOn(bool wavesOn);

        /**
         * @param wavesAmplitude Set amplitude of waves function.
         */
        void setWavesAmplitude(float wavesAmplitude);

        /**
         * @param wavesFrequency Set frequency of waves function.
         */
        void setWavesFrequency(float wavesFrequency);

        /**
         * @param wavesChoppiness Set choppiness of waves function.
         */
        void setWavesChoppiness(float wavesChoppiness);

        /**
         * @param wavesResolutionY Scope of random function's X axis.
         */
        void setWavesResolutionX(float wavesResolution);

        /**
         * @param wavesResolutionY Scope of random function's Y axis.
         */
        void setWavesResolutionY(float wavesResolution);

    private:
        CWavesDeformer _wavesDeformer;
        GLfloat        _currentTime;
        GLfloat        _totalTime;
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
