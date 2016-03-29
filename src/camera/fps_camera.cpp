//
// Created by dybisz on 16.02.16.
//

#include "fps_camera.h"

FPSCamera::FPSCamera() : _position(POSITION),
                         _horizontalAngle(HORIZONTAL_ANGLE),
                         _verticalAngle(VERTICAL_ANGLE),
                         _fov(FIELD_OF_VIEW),
                         _viewportRatio(VIEWPORT_RATIO),
                         _nearPlane(NEAR_PLANE),
                         _farPlane(FAR_PLANE) {
}

/* -------------------- */
/* ----- Matrices ----- */
/* -------------------- */

glm::mat4 FPSCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(_fov), _viewportRatio, _nearPlane,
                            _farPlane);
}

glm::mat4 FPSCamera::getViewMatrix() {
    return _getAzimuth() * glm::translate(glm::mat4(), _position);
}

glm::mat4 FPSCamera::getViewProjectionMatrix() {
    return getProjectionMatrix() * getViewMatrix();
}

/* -------------------- */
/* ----- Movement ----- */
/* -------------------- */

void FPSCamera::changeAzimuth(float upAngle, float rightAngle) {
    _horizontalAngle += rightAngle;
    _verticalAngle += upAngle;
    _normalizeAngles();
}

void FPSCamera::moveForward(float amount) {
    _position += amount * _getForwardVector();
}

void FPSCamera::moveBackward(float amount) {
    _position -= amount * _getForwardVector();
}

void FPSCamera::moveRight(float amount) {
    _position += amount * _getRightVector();
}

void FPSCamera::moveLeft(float amount) {
    _position -= amount * _getRightVector();
}

void FPSCamera::moveUp(float amount) {
    _position -= amount * glm::vec3(0,1,0);
}

void FPSCamera::moveDown(float amount) {
    _position += amount * glm::vec3(0,1,0);
}

glm::mat4 FPSCamera::_getAzimuth() {
    glm::mat4 azimuth;
    azimuth = glm::rotate(azimuth, glm::radians(_verticalAngle),
                          glm::vec3(1, 0, 0));
    azimuth = glm::rotate(azimuth, glm::radians(_horizontalAngle),
                          glm::vec3(0, 1, 0));
    return azimuth;
}

glm::vec3 FPSCamera::_getForwardVector() {
    glm::vec4 forward = glm::inverse(_getAzimuth()) * glm::vec4(0,0,1,1);
    return glm::vec3(forward);
}

glm::vec3 FPSCamera::_getRightVector() {
    glm::vec4 right = glm::inverse(_getAzimuth()) * glm::vec4(-1,0,0,1);
    return glm::vec3(right);
}

void FPSCamera::_normalizeAngles() {
    _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
    if(_horizontalAngle < 0.0f)
        _horizontalAngle += 360.0f;

    if(_verticalAngle > 85.0f)
        _verticalAngle = 85.0f;
    else if(_verticalAngle < -85.0f)
        _verticalAngle = -85.0f;
}

