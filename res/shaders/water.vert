//==============================================================================
// Shader in charge of calculating normal for a given vertex based on supplied
// height map texture. The texture must contain current values for shallow
// water equations calculations. What is more, the vertex position is updated
// according to the heightmap. Both, position and normal are sent to the
// fragment shader for further processing.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core

//==============================================================================
// In
//------------------------------------------------------------------------------
in vec3           a_position;
in vec2           a_heightFieldTexCoords;

//==============================================================================
// Out
//------------------------------------------------------------------------------
out vec3          v_position;
out vec3          v_normal;
out vec2          v_textureCoords;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform sampler2D u_heightFieldTexture;
uniform mat4      u_modelMatrix;
uniform mat4      u_viewMatrix;
uniform mat4      u_projectionMatrix;
uniform vec3      u_cameraPosition;
uniform int       u_verticesPerSide;
uniform float     u_sideSize;

/**
 * For considered vertex procedure reads height of its neighbors. Based on them
 * two vectors are calculated: right to left and up to down. Their normalized
 *  cross product is interpreted as the normal.
 *
 * @return Normal to the current vertex.
 */
vec3 calculateNormal() {
  float step    = 1. / float(u_verticesPerSide);

  float current = texture
                  (
                      u_heightFieldTexture,
                      vec2
                      (
                          a_heightFieldTexCoords.x,
                          a_heightFieldTexCoords.y
                      )
                  ).r;

  float up      = texture
                  (
                      u_heightFieldTexture,
                      vec2
                      (
                          a_heightFieldTexCoords.x,
                          a_heightFieldTexCoords.y + step
                      )
                  ).r;

  float down    = texture
                  (
                      u_heightFieldTexture,
                      vec2
                      (
                          a_heightFieldTexCoords.x,
                          a_heightFieldTexCoords.y - step
                      )
                  ).r;

  float right   = texture
                  (
                      u_heightFieldTexture,
                      vec2
                      (
                          a_heightFieldTexCoords.x + step,
                          a_heightFieldTexCoords.y
                      )
                  ).r;

  float left    = texture
                  (
                      u_heightFieldTexture,
                      vec2
                      (
                          a_heightFieldTexCoords.x - step,
                          a_heightFieldTexCoords.y
                      )
                  ).r;

  vec3 d_x      = vec3(u_sideSize * 2.0 * step, right - left, 0.0);
  vec3 d_z      = vec3(0.0, up - down, u_sideSize *  2.0 * step);
  vec3 normal   = normalize(cross(d_z, d_x));

  return normal;
}

void main()
{
    // Read the vertex height
    vec3 position = a_position;
    position.y    = texture(u_heightFieldTexture, a_heightFieldTexCoords).r;

    // Update its position according to transformations
    gl_Position   = u_projectionMatrix *
                    u_viewMatrix       *
                    u_modelMatrix      *
                    vec4(position, 1.0);

    // Pass values to the next shader
    v_normal      = calculateNormal();
    v_position    = position;
    v_textureCoords = a_heightFieldTexCoords;
}