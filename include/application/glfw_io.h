//==============================================================================
// Handles keyboard and mouse controls and updates camera properties.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef GLFW_IO_H
#define GLFW_IO_H

#include <glm/glm.hpp>
#include "ship_model.h"
#include <AntTweakBar.h>
#include <glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "custom_camera.h"


using namespace std;
using namespace glm;

class CGLFWInputOutput {
public:
    /**
     * Class requires GLFW window to work. The class will not free its
     * resources.
     */
    CGLFWInputOutput(GLFWwindow *window);

    /**
     * Set camera to be updated with changes in the programs input. The class
     * will not free its resources.
     */
    void setCamera(CCustomCamera *camera);
    void setForceMove(vec3 *forceMove);
    void setShip(CShipModel* ship);
    static void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods);

    static void cursor_position_callback(GLFWwindow *window, double xpos,
                                         double ypos);

    void updateTime(float deltaTime);

    static void mouse_button_callback(GLFWwindow *window, int button,
                                      int action, int mods);

    static void setIntersectionRequested(bool intersectionRequested);
    static void setStopAnimationRequested(bool stopAnimationRequested);
    static bool isIntersectionRequested();
    static bool isStopAnimationRequested();
    vec2 getIntersectionCoordinates();

private:
    GLFWwindow*    _window;
    CCustomCamera* _camera;
    CShipModel*    _ship;
    vec3*          _forceMove;
    static bool    _rightButtonPressed;
    static double  _mouseX;
    static double  _mouseY;
    static bool    _intersectionRequested;
    static bool    _stopAnimationRequested;
    static vec2    _intersectionCoordinates;

    /**
     * Updates the camera according to the mouse parameters.
     *
     * @param Difference in time between render calls.
     */
    void _handleMouse(double deltaTime);

    /**
     * Updates the camera according to the keyboard parameters.
     *
     * @param Difference in time between render calls.
     */
    void _handleKeyboard(double deltaTime);
};

#endif
