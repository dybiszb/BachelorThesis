// author: dybisz

#include "camera.h"

CCustomCamera::CCustomCamera(Settings& settings) : _settings(settings) {
    _position = vec3
            (
                    _settings.cameraStartPositionX,
                    _settings.cameraStartPositionY,
                    _settings.cameraStartPositionZ
            );
    _horizontalAngle = _settings.cameraHorizontalAngle;
    _verticalAngle   = _settings.cameraVerticalAngle;
    _fov = _settings.cameraFov;
    _movementSpeed = _settings.cameraMovementSpeed;
    _angularSpeed = _settings.cameraAngularSpeed;
}

void CCustomCamera::updateViewingAngles(double mouseX, double mouseY,
                                        float deltaTime) {
    _horizontalAngle += _angularSpeed * mouseX;
    _verticalAngle   += _angularSpeed * mouseY;
}

void CCustomCamera::moveForward(float deltaTime) {
    _position += getDirectionVector() * deltaTime * _movementSpeed;
}

void CCustomCamera::moveBackward(float deltaTime) {
    _position -= getDirectionVector() * deltaTime * _movementSpeed;
}

void CCustomCamera::moveLeft(float deltaTime) {
    _position -= getRightVector() * deltaTime * _movementSpeed;
}

void CCustomCamera::moveRight(float deltaTime) {
    _position += getRightVector() * deltaTime * _movementSpeed;
}

void CCustomCamera::moveUp(float deltaTime) {
    _position.y += deltaTime * _movementSpeed;
}

void CCustomCamera::moveDown(float deltaTime) {
    _position.y -= deltaTime * _movementSpeed;
}

mat4 CCustomCamera::getProjectionMatrix() {
    return perspective(_fov, 4.0f / 3.0f, 0.1f, 1000.0f);
}

mat4 CCustomCamera::getViewMatrix() {
    return glm::lookAt(_position,
                       _position + getDirectionVector(),
                       getUpVector()
    );
}

vec3 CCustomCamera::getDirectionVector() {
    float radiansHorizontal = (_horizontalAngle * M_PI) / 180.0f;
    float radiansVertical = (_verticalAngle * M_PI) / 180.0f;

    return vec3(cos(radiansVertical) * sin(radiansHorizontal),
                sin(radiansVertical),
                cos(radiansVertical) * cos(radiansHorizontal));
}

vec3 CCustomCamera::getRightVector() {
    float radiansHorizontal = (_horizontalAngle * M_PI) / 180.0f;

    return vec3(sin(radiansHorizontal - 3.14f / 2.0f),
                0,
                cos(radiansHorizontal - 3.14f / 2.0f));
}

vec3 CCustomCamera::getUpVector() {
    return cross(getRightVector(), getDirectionVector());
}

vec3& CCustomCamera::getPosition() {
    return _position;
}

float CCustomCamera::getVerticalAngle() {
    return _verticalAngle;
}