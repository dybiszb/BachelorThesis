//==============================================================================
// Initializes GLFW, GLEW and AntTweakBar contexts.
// Class has been created in a straight forward manner on purpose. Its aim is
// just to wrap up basic application's window. In addition, it controls i/o
// from keyboard/mouse and oversees bridge-variables between rendered objects
// and GUI.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef GLFW_RENDERER_H
#define GLFW_RENDERER_H

#include <GL/glew.h>
#include <glfw3.h>
#include <AntTweakBar.h>
#include "glfw_io.h"
#include "glfw_timer.h"
#include "skybox_cube.h"
#include "water_grid.h"
#include "water_builder.h"
#include "skybox_builder.h"
#include "rand_functions.h"
#include "atw_gui.h"


using namespace entities;
using namespace utils;

class CGLFWRenderer {
public:
    /**
     * Basically calls all _init* methods in correct order.
     *
     * @param windowWidth   How wide should be the window?
     * @param windowHeight  How high should be the window?
     * @param fullscreen    Fullscreen on or off?
     */
    CGLFWRenderer(int windowWidth, int windowHeight, bool fullscreen);

    /**
     * Besides ordinary dispose calls, both GLFW and AntTweakBar must be
     * terminated by calling appropriate methods.
     */
    ~CGLFWRenderer();

    /**
     * Core of the application. All render calls along with appropriate
     * updates are handled here.
     */
    void runMainLoop();

private:
    int _windowWidth;
    int _windowHeight;
    bool _fullscreen;
    CGLFWInputOutput *_inputOutput;
    CTimer _timer;
    CAtwGui _gui;
    GLFWwindow *_window;
    CCustomCamera _camera;
    CSkybox *_skybox;
    CWaterGrid *_water;

    /**
     * Initializes GLFW context.
     */
    void _initGLFW();

    /**
     * Initializes GLFW window;
     */
    void _initWindow();

    /**
     * Initializes input output object. _window must contain pointer to GLFW
     * window. _camera must be initialized.
     */
    void _initInputOutput();

    /**
    * Initializes GLEW. By default experimental version is created (i.e.
     * glewExperimental is set to 'true').
    */
    void _initGLEW();

    /**
     * Initializes AntTweakBar-based GUI. One should definitely adapt
     * definition to his/hers purposes.
     */
    void _initATWBar();

    /**
     * Initially GLFW events must be redirected to ATWBar GUI. This is the
     * place where one can plug in his/hers functions into GUI functionality.
     */
    void _initCallbacks();

    /**
     * All objects to render, which are in form of pointers are born here.
     */
    void _initRenderableObjects();

    /**
     * Auxiliary method in charge of OpenGL settings which are usually set
     * before main render loop e.g. glClearColor or all glEnable calls;
     */
    void _initGLGlobalSettings();
};

#endif
