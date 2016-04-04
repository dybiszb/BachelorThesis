//==============================================================================
// TODO
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef CUSTOM_CAMERA_H
#define CUSTOM_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class CCustomCamera {
public:
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

    vec3 getPosition();

private:
    vec3 _position = glm::vec3(30,15, 0);
    float _horizontalAngle =  3.14f * 1.5 ;
    float _verticalAngle = -3.14f/ 8.0f;
    float _initialFoV = 45.0f;
    float _speed = 15.0f;
    float _mouseSpeed = 0.050f;
};


#endif
