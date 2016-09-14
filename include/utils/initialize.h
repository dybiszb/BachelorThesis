//==============================================================================
// Following source file contains all auxiliary functions related to
// initializing various frameworks/libraries like e.g. GLEW or GLFW.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <GL/glew.h>
#include <glfw3.h>

namespace utils {
    /**
     * Initializes GLFW context.
     *
     * @return True if GLFW context has been initialized, false otherwise.
     */
    bool initGLFW();

    /**
     * Initializes GLEW context.
     *
     * @return True if GLEW context has been initialized, false otherwise.
     */
    bool initGLEW();

    /**
     * Initializes a window withing GLFW context.
     * Must be called after initGLFW procedure.
     * In case of any error, GLFW context will be terminated and appropriate
     * message will be displayed.
     *
     * @param width   Window width.
     * @param height  Window height.
     * @param title   Text in window title bar.
     * @param monitor The monitor to use for full screen mode, or `NULL` to use
     *                windowed mode.
     *
     * @return        Pointer to a window object.
     */
    GLFWwindow *initGLFWWindow(int width, int height, const char *title,
                               GLFWmonitor* monitor = NULL);
}

#endif INITIALIZE_H
