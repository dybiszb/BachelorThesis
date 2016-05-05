// author: dybisz

#include "rays_functions.h"

vec3 utils::toNormalizedDeviceCoordinates(vec2 &viewportCoordinates,
                                         int windowWidth, int windowHeight) {
    float x = (2.0f * viewportCoordinates.x) / (float) windowWidth - 1.0f;
    float y = 1.0f - (2.0f * viewportCoordinates.y) / windowHeight;
    float z = 1.0f;

    return vec3(x, y, z);
}

vec4 utils::toCameraCoordinates(vec4 &clipCoordinates, mat4 &projectionMatrix) {
    vec4 rayCameraSpace = inverse(projectionMatrix) * clipCoordinates;
    rayCameraSpace.z = -1.0;
    rayCameraSpace.w = 0.0;
    return rayCameraSpace;
}

vec3 utils::toWorldCoordinates(vec4 &cameraCoordinates, mat4 &viewMatrix) {
    vec4 rayWorldSpace4 = (inverse(viewMatrix) * cameraCoordinates);
    vec3 rayWorldSpace3 = vec3(rayWorldSpace4.x, rayWorldSpace4.y,
                               rayWorldSpace4.z);
    rayWorldSpace3 = normalize(rayWorldSpace3);
    return rayWorldSpace3;
}

bool utils::rayIntersectsPlane(vec3 &worldCoordinates, vec3 &planeNormal,
                              vec3 &cameraPosition, vec3 &intersectionPoint) {
    float denominator = dot(worldCoordinates, planeNormal);
    float t = -1.0;

    // Check if the ray goes perpendicular to the plane
    if (denominator != 0) {
        t = -(dot(cameraPosition, planeNormal));
        t /= denominator;
    }
    if (t < 0) {
        return false;
    } else {
        intersectionPoint = cameraPosition + (worldCoordinates * t);
        return true;
    }
}