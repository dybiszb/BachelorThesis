// author: dybisz

#include "glfw_timer.h"

CTimer::CTimer() : _lastTime(0) {};

float CTimer::tick() {
    double currentTime = glfwGetTime();
    float deltaTime = (float) (currentTime - _lastTime);
    _lastTime = currentTime;
    return deltaTime;
}