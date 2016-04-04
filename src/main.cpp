#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glsl_shader.h>
#include "custom_camera.h"
#include <vector>
#include <skybox.h>
#include "water_grid.h"

#define OPENGL_MAJOR        2
#define OPENGL_MINOR        1
#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       600
#define WINDOW_TITLE        "Ocean"
#define SUCCESS             1
#define ERROR               -1

bool gModernShaders = false;

int initGLFW(int openGLMajor, int openGLMinor);

int openWindow(int windowWidth, int windowHeight, const char *windowTitle);

int initGLEW();

int setupScene();

int runSimulationLoop();

void updateScene(float timeElapsed);

void centerTheWindow();

GLFWwindow *window;
CCustomCamera camera;

using namespace glm;
using namespace entities;
using namespace std;

int main(void) {
    assert (initGLFW(OPENGL_MAJOR, OPENGL_MINOR) == SUCCESS);
    assert (openWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) == SUCCESS);
    assert (initGLEW() == SUCCESS);
    assert (setupScene() == SUCCESS);
    runSimulationLoop();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

int initGLFW(int openGLMajor, int openGLMinor) {

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return ERROR;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLMinor);

    return SUCCESS;
}

// Open a window and create its OpenGL context
int openWindow(int windowWidth, int windowHeight, const char *windowTitle) {

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL,
                              NULL);

    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return ERROR;
    }

    glfwMakeContextCurrent(window);

    return SUCCESS;
}

int initGLEW() {
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return ERROR;
    }

    if(GLEW_VERSION_3_3) {
        gModernShaders = true;
        cout << "Loading modern shaders: version 330 core.\n";
    }
    else {
        cout << "Loading old shaders: version 120.\n";
    }

    if(!GL_ARB_depth_texture)
    {
        cout << "GL_ARB_depth_texture not supported!\n";
    }

    if(!GL_FRAMEBUFFER_EXT)
    {
        cout <<"GL_EXT_framebuffer_object not supported!\r\n";
    }

    return SUCCESS;
}

int setupScene() {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, 0, 0);
    centerTheWindow();
    return SUCCESS;
}

int runSimulationLoop() {
    int sceneSize = 256;

    std::vector<const GLchar *> facesNames({
                                                   "./res/textures"
                                                           "/skybox/sor_sea/front.jpg",
                                                   "./res/textures"
                                                           "/skybox/sor_sea/back.jpg",
                                                   "./res/textures"
                                                           "/skybox/sor_sea/top.jpg",
                                                   "./res/textures"
                                                           "/skybox/sor_sea/bottom.jpg",
                                                   "./res/textures"
                                                           "/skybox/sor_sea/right.jpg",
                                                   "./res/textures"
                                                           "/skybox/sor_sea/left.jpg"});

    CSkybox skybox(32, &facesNames, gModernShaders);
    CWaterGrid water(sceneSize, sceneSize, 32, glm::vec2
            (-32 / 2, -32 / 2), gModernShaders);
    water.setSkyboxCubemapId(skybox.getCubemapId());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    double lastTime = glfwGetTime();

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update scene
        double thisTime = glfwGetTime();
        double timeLapsed = (float) (thisTime - lastTime);

        updateScene(timeLapsed);
        water.updateTime(thisTime);
        lastTime = thisTime;

        // Draw scene
        mat4 projection = camera.getProjectionMatrix();
        mat4 view = camera.getViewMatrix();
        mat4 vp = projection * view;

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        skybox.setCameraPosition(camera.getPosition());
        skybox.render(&vp[0][0]);

//        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        water.setCameraPosition(camera.getPosition());;
        water.render(&vp[0][0]);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    return SUCCESS;
}

void updateScene(float timeElapsed) {

    // Mouse
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    camera.updateViewingAngles(mouseX, mouseY, timeElapsed);
    glfwSetCursorPos(window, 0, 0);

    if (glfwGetKey(window, 'W')) {
        camera.moveForward(timeElapsed);
    } else if (glfwGetKey(window, 'S')) {
        camera.moveBackward(timeElapsed);
    }

    if (glfwGetKey(window, 'A')) {
        camera.moveLeft(timeElapsed);
    } else if (glfwGetKey(window, 'D')) {
        camera.moveRight(timeElapsed);
    }

    if (glfwGetKey(window, 'Z')) {
        camera.moveUp(timeElapsed);
    } else if (glfwGetKey(window, 'X')) {
        camera.moveDown(timeElapsed);
    }
}

void centerTheWindow() {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(window, (mode->width - WINDOW_WIDTH) / 2, (mode->height -
                                                                WINDOW_HEIGHT) /
                                                               2);
}
