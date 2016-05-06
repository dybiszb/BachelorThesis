//==============================================================================
// The shader using Euler method calculates next step in shallow water
// equations.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core

#define NONE                 0
#define UP_NEIGHBOUR         1.0
#define DOWN_NEIGHBOUR      -1.0
#define LEFT_NEIGHBOUR       1.0
#define RIGHT_NEIGHBOUR     -1.0

struct MembraneEqProperties {
    float h;
    float c;
    float dt;
};

//==============================================================================
// In
//------------------------------------------------------------------------------
in vec2                      v_heightFieldTexCoords;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform sampler2D            u_heightFieldTexture;
uniform float                u_sideSize;
uniform int                  u_verticesPerSide;
uniform MembraneEqProperties u_membraneProperties;

/**
 * Calculates damping according to distance between the fragment and closest
 * shore. As a fragment's position, the procedure uses its UV coordinates on
 * heightfield texture.
 *
 * @param position Fragment's UV heightfield texture coordinates.
 */
float calculateDamping(vec2 position) {
    float distShoreX = min(position.x, 1.0 - position.x);
    float distShoreY = min(position.y, 1.0 - position.y);
    float distShore  = max(distShoreX, distShoreY);
    distShore = u_sideSize * distShore;
    return 0.95 * min(1, distShore/(0.2));
}

/**
 * Retrieves height of specified neighbour. All eight neighbors can be
 * access.
 *
 * @param uModifier Left (1.0) or right (-1.0) neighbor. 0 will represent none.
 * @param vModifier Up   (1.0) or down  (-1.0) neighbor. 0 will represent none.
 */
float getNeighbour(float uModifier, float vModifier) {
    float step = 1.0 / float(u_verticesPerSide);
    return texture
           (
           u_heightFieldTexture,
               vec2
               (
                    v_heightFieldTexCoords.x - uModifier * step,
                    v_heightFieldTexCoords.y - vModifier * step
               )
           ).r;
}
float dividedDifferencies(float up, float down, float left, float right,
                         float current, float old) {
    float A = (u_membraneProperties.c * u_membraneProperties.c *
               u_membraneProperties.dt * u_membraneProperties.dt) /
              (u_membraneProperties.h * u_membraneProperties.h);
    float B = 2. - 4. * A;
    return (A * (up + down + left + right)) + (B * current) - old;
}
void main()
{
    float up      = getNeighbour(NONE,            UP_NEIGHBOUR);
    float down    = getNeighbour(NONE,            DOWN_NEIGHBOUR);
    float left    = getNeighbour(LEFT_NEIGHBOUR,  NONE);
    float right   = getNeighbour(RIGHT_NEIGHBOUR, NONE);
    float current = getNeighbour(NONE,            NONE);
    float old     = texture2D(u_heightFieldTexture, v_heightFieldTexCoords).g;

    float d       = calculateDamping(v_heightFieldTexCoords);

    float height = d * dividedDifferencies(up, down, left, right, current, old);
    gl_FragColor = vec4(height, current, 0.0, 0.0);
}