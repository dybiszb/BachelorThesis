//==============================================================================
// Following source file contains all auxiliary functions related to
// initializing various frameworks/libraries like e.g. GLEW or GLFW.
// It is additionally useful when it comes to performing unit tests.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <GL/glew.h>
#include <glfw3.h>

namespace utils {
    bool initGLFW();

    bool initGLEW();

    GLFWwindow *initGLFWWindow(int width, int height, const char *title,
                               GLFWmonitor* monitor = NULL);
}

#endif INITIALIZE_H
