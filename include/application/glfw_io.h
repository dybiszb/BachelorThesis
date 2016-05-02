//==============================================================================
// Handles keyboard and mouse controls and updates camera properties.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef GLFW_IO_H
#define GLFW_IO_H

#include <AntTweakBar.h>
#include <glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "camera.h"

using namespace std;

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

    static void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods);

    static void cursor_position_callback(GLFWwindow *window, double xpos,
                                         double ypos);

    void updateCamera(float deltaTime);

    static void mouse_button_callback(GLFWwindow *window, int button,
                                      int action, int mods);

    static void setIntersectionRequested(bool intersectionRequested);
    static bool isIntersectionRequested();
    vec2 getIntersectionCoordinates();

private:
    GLFWwindow*    _window;
    CCustomCamera* _camera;
    static bool    _rightButtonPressed;
    static double  _mouseX;
    static double  _mouseY;
    static bool    _intersectionRequested;
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
