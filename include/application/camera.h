//==============================================================================
// TODO
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef CUSTOM_CAMERA_H
#define CUSTOM_CAMERA_H
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "settings_struct.h"

using namespace glm;
using namespace utils;

class CCustomCamera {
public:
    CCustomCamera(Settings& settings);
    void updateViewingAngles(double mouseX, double mouseY, float deltaTime);

    void moveForward(float deltaTime);

    void moveBackward(float deltaTime);

    void moveLeft(float deltaTime);

    void moveRight(float deltaTime);

    void moveUp(float deltaTime);

    void moveDown(float deltaTime);

    mat4 getProjectionMatrix();

    mat4 getViewMatrix();

    vec3 getDirectionVector();

    vec3 getRightVector();

    vec3 getUpVector();

    vec3& getPosition();

    float getVerticalAngle();
public:
    vec3 _position;
    float _horizontalAngle;
    float _verticalAngle;
    float _fov;
    float _movementSpeed;
    float _angularSpeed;
private:
    Settings _settings;

};


#endif
