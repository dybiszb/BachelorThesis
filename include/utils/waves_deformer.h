//==============================================================================
// Following class performs all off screen calculations related to the water.
// By default it encapsulates two shader passes: manual disturbance and
// random waves (results of the two are added and saved in one texture). The
// latter can be disabled via calling setWavesOn(false). One can call
// animationStep procedure to update inner textures, which can be later on
// binded and used to render the water grid.
//
// NOTE: Private methods, as an internal part of the class rather than public
//       interface, are not commented. Private variables are separated into
//       classes via header comments, in order to preserve clarity.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef WAVES_DEFORMER_H
#define WAVES_DEFORMER_H

#include <GL/glew.h>
#include <iostream>
#include <math.h>
#include "buffers/frame_buffer.h"
#include "textures/texture_2D.h"
#include "glsl_shader.h"
#include "vertex_array.h"
#include "vertex.h"
#include "quad.h"
#include "error_handling.h"

using namespace rendering;
using namespace geometry;
using namespace glm;
using namespace utils;
using namespace std;

class CWavesDeformer{
public:
    ~CWavesDeformer();

    /**
     * @param width  Width of the computational textures. It can be also
     *               understood as a number of vertices in a grid's row.
     * @param height Height of the computational textures. It can be also
     *                understood as a number of vertices in a grid's columns.
     */
    CWavesDeformer(int width, int height);

    /**
     * Calculates next step of the water simulation. If _wavesOn field is true,
     * random waves will be calculated.
     *
     * NOTE: Appropriate texture unit must be binded before calling this
     *       procedure. In addition one must either call
     *       bindDisturbanceTexture or bindNoiseTexture (depending on needs)
     *       after the call.
     */
    void animationStep();

    /**
     * Binds texture with manual disturbance calculations.
     */
    void bindDisturbanceTexture();

    /**
     * Unbinds texture with manual disturbance calculations.
     */
    void unbindDisturbanceTexture();

    /**
     * Binds texture with noise calculations.
     */
    void bindNoiseTexture();

    /**
     * Unbinds texture with noise calculations.
     */
    void unbindNoiseTexture();

    /**
     * Disturbs texture at a specified point. Appropriate pixel will get
     * specified value.
     *
     * @param quad     (u,v) coordinates of the texture that will be disturbed.
     * @param amount Value that will be saved in the specified pixel.
     */
    void pointDisturbance(vec2& quad, float amount);

    /**
     * Disturbs texture over specified area with -a*(x*x + y*y) function.
     *
     * @param quad     (u,v) coordinates of the texture that will be treated
     *                 as a center of disturbance area.
     * @param amount   How much one wants to disturb the area (height of the
     *                 disturbance function.)
     * @param kernel   Area size. E.g. kernel = 4 will mean that 9x9 area
     *                 will be disturbed (4 to the left of the center and 4
     *                 to the right, and center itself gives 9)
     * @param flatness Parameter 'a' in the formula. Determines steepnes of a
     *                 particular disturbance.
     */
    void areaDisturbance(vec2& quad, float amount, int kernel, float flatness);

    /**
     * @param deltaT Set time between rendering last two frames.
     */
    void updateTime(float deltaT);

    /**
     * @param wavesOn If true, both manual disturbance and random waves will
     *                be calculated. Otherwise only the former.
     */
    void setWavesOn(bool wavesOn);

    /**
     * @param wavesAmplitude Amplitude of generated waves.
     */
    void setWavesAmplitude(float wavesAmplitude);

    /**
     * @param wavesFrequency How frequent should be generated waves.
     */
    void setWavesFrequency(float wavesFrequency);

    /**
     * @param wavesChoppiness How steep should be generated waves.
     */
    void setWavesChoppiness(float wavesChoppiness);

    /**
     * @param wavesResolutionY Scope of random function's X axis.
     */
    void setWavesResolutionX(float wavesResolutionX);

    /**
     * @param wavesResolutionY Scope of random function's Y axis.
     */
    void setWavesResolutionY(float wavesResolutionY);

    /**
     * Acquires the resulting texture in form of an array.
     *
     * NOTE: Returned object must be deleted by the caller.
     *
     * @return Array with texture values ordered as RGBARGBA... sequence, where
     *         R, G, B, A are channels values of a particular pixel.
     */
    GLfloat* getCurrentTextureAsVector();

private:
//==============================================================================
// Deformer Settings
//------------------------------------------------------------------------------
    GLsizei       _width;
    GLsizei       _height;
    GLuint        _verticesPerSide;

//==============================================================================
// Off Screen Rendering
//------------------------------------------------------------------------------
    CFrameBuffer* _fbo0;
    CFrameBuffer* _fbo1;
    CFrameBuffer* _fbo2;
    CFrameBuffer* _fbo3;
    CTexture2D*   _tex0;
    CTexture2D*   _tex1;
    CTexture2D*   _tex2;
    CTexture2D*   _tex3;

//==============================================================================
// OpenGl Objects
//------------------------------------------------------------------------------
    GLSLShader    _shader;
    CVertexArray  _vao;
    CQuad         _quad;

//==============================================================================
// Shader Settings
//------------------------------------------------------------------------------
    GLfloat       _h;
    GLfloat       _c;
    GLfloat       _dt;
    GLfloat       _dtOverall;
    GLfloat       _wavesOn;
    GLfloat       _wavesAmplitude;
    GLfloat       _wavesFrequency;
    GLfloat       _wavesChoppiness;
    GLfloat       _wavesResolutionX;
    GLfloat       _wavesResolutionY;

    void _initShaders();
    void _initVao();
    void _initMembraneCoefficients();

};


#endif
