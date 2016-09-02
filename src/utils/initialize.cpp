#include <cstdio>
#include "initialize.h"

using namespace utils;

bool utils::initGLFW() {
    return (bool) glfwInit();
}

bool utils::initGLEW() {
    glewExperimental = (GLboolean) true;
    return glewInit() == GLEW_OK;
}

GLFWwindow *utils::initGLFWWindow(int width, int height, const char *title, GLFWmonitor* monitor) {
    GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    return window;
}
