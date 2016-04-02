// author: dybisz

#include "custom_camera.h"

void CCustomCamera::updateViewingAngles(double mouseX, double mouseY,
                                        float deltaTime) {
    _horizontalAngle -= _mouseSpeed * deltaTime * mouseX;
    _verticalAngle -= _mouseSpeed * deltaTime * mouseY;
}

void CCustomCamera::moveForward(float deltaTime) {
    _position += getDirectionVector() * deltaTime * _speed;
}

void CCustomCamera::moveBackward(float deltaTime) {
    _position -= getDirectionVector() * deltaTime * _speed;
}

void CCustomCamera::moveLeft(float deltaTime) {
    _position -= getRightVector() * deltaTime * _speed;
}

void CCustomCamera::moveRight(float deltaTime) {
    _position += getRightVector() * deltaTime * _speed;
}

void CCustomCamera::moveUp(float deltaTime) {
    _position.y += deltaTime * _speed;
}

void CCustomCamera::moveDown(float deltaTime) {
    _position.y -= deltaTime * _speed;
}

mat4 CCustomCamera::getProjectionMatrix() {
    return perspective(_initialFoV, 4.0f / 3.0f, 0.1f, 1000.0f);
}

mat4 CCustomCamera::getViewMatrix() {
    return glm::lookAt(_position,
                       _position + getDirectionVector(),
                       getUpVector()
    );
}

vec3 CCustomCamera::getDirectionVector() {
    return vec3(cos(_verticalAngle) * sin(_horizontalAngle),
                sin(_verticalAngle),
                cos(_verticalAngle) * cos(_horizontalAngle));
}

vec3 CCustomCamera::getRightVector() {
    return vec3(sin(_horizontalAngle - 3.14f / 2.0f),
                0,
                cos(_horizontalAngle - 3.14f / 2.0f));
}

vec3 CCustomCamera::getUpVector() {
    return cross(getRightVector(), getDirectionVector());
}

vec3 CCustomCamera::getPosition() {
    return _position;
}