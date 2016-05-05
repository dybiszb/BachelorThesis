//==============================================================================
// Set of functions, which perform operations related to ray intersection,
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
     * @return Three dimensional point in device coordinate space.
     */
    vec3 toNormalizedDeviceCoordinates(vec2 &viewportCoordinates,
                                       int windowWidth, int windowHeight);

    vec4 toCameraCoordinates(vec4& clipCoordinates, mat4& projectionMatrix);

    vec3 toWorldCoordinates(vec4& cameraCoordinates, mat4& viewMatrix);

    bool rayIntersectsPlane(vec3& worldCoordinates,  vec3& planeNormal,
                            vec3& cameraPosition, vec3& intersectionPoint);
}

#endif
