//
// Created by dybisz on 16.02.16.
//
// partially based on :
// http://www.tomdalling.com/blog/modern-opengl/04-cameras-vectors-and-input/
//

#ifndef BACHELOR_WATER_FPS_CAMERA_H
#define BACHELOR_WATER_FPS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* ----- Default settings for FPSCamera ----- */
#define POSITION          glm::vec3(0.0f, -20.0f, -45.0f)
#define HORIZONTAL_ANGLE  0.0f
#define VERTICAL_ANGLE    20.0f
#define FIELD_OF_VIEW     45.0f
#define VIEWPORT_RATIO    4.0f/3.0f
#define NEAR_PLANE        0.01f
#define FAR_PLANE         1000.0f
/* ------------------------------------------ */

class FPSCamera {
public:
    FPSCamera();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getViewProjectionMatrix();
    void changeAzimuth(float upAngle, float rightAngle);
    void moveForward(float amount);
    void moveBackward(float amount);
    void moveRight(float amount);
    void moveLeft(float amount);
    void moveUp(float amount);
    void moveDown(float amount);

private:
    glm::vec3 _position;
    float _horizontalAngle;
    float _verticalAngle;
    float _fov;
    float _viewportRatio;
    float _nearPlane;
    float _farPlane;

    glm::mat4 _getAzimuth();
    glm::vec3 _getForwardVector();
    glm::vec3 _getRightVector();
    void _normalizeAngles();
};


#endif //BACHELOR_WATER_FPS_CAMERA_H
