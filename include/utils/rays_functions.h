//==============================================================================
// Set of functions, which perform operations related to ray intersection.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef RAYS_FUNCTIONS_H
#define RAYS_FUNCTIONS_H

#include <glm/glm.hpp>

using namespace glm;

namespace utils {

    /**
     * Transforms raw point from the screen to [­1:1, ­1:1, ­1:1] range.
     *
     * @param viewportCoordinates Two dimensional point on the screen. Can be
     *                            e.g. recently mouse-clicked place.
     * @param windowWidth         Width of the viewport.
     * @param windowHeight        Height of the viewport.
     *
     * @return                    Three dimensional point in device coordinate
     *                            space.
     */
    vec3 toNormalizedDeviceCoordinates(vec2 &viewportCoordinates,
                                       int windowWidth, int windowHeight);

    /**
     * Transforms a point in clip coordinates to camera coordinates.
     *
     * @param clipCoordinates  A four dimensional vector with homogeneous
     *                         coordinates.
     * @param projectionMatrix Projection matrix of a scene.
     *
     * @return                 Homogeneous, camera coordinates.
     */
    vec4 toCameraCoordinates(vec4& clipCoordinates, mat4& projectionMatrix);

    /**
     * Transforms a point in camera coordinates to world coordinates.
     *
     * @param cameraCoordinates  A four dimensional vector with homogeneous
     *                           coordinates.
     * @param viewMatrix         View matrix of a scene.
     *
     * @return                   Homogeneous, world coordinates.
     */
    vec3 toWorldCoordinates(vec4& cameraCoordinates, mat4& viewMatrix);

    /**
     * Determines whether specified ray intersects provided plane.
     * Ray will be constructed based on a point in world coordinates and
     * camera position. Plane is assumed to be infinite and not translated,
     * hence only its normal is needed.
     *
     * @param worldCoordinates  A point in world coordinates.
     * @param planeNormal       A plane normal.
     * @param cameraPosition    Scene's camera position.
     * @param intersectionPoint In case of an intersection following
     *                          reference will be updated with point of
     *                          intersection. Otherwise it will remains the
     *                          same.
     *
     * @return                  True if a ray intersects a plane, false
     *                          otherwise.
     */
    bool rayIntersectsPlane(vec3& worldCoordinates,  vec3& planeNormal,
                            vec3& cameraPosition, vec3& intersectionPoint);
}

#endif
