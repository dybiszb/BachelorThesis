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
//precision highp float;
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
out vec3          v_noiseNormal;
out vec2          v_textureCoords;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform sampler2D u_heightFieldTexture;
uniform sampler2D u_noiseTexture;
uniform mat4      u_modelMatrix;
uniform mat4      u_viewMatrix;
uniform mat4      u_projectionMatrix;
uniform vec3      u_cameraPosition;
uniform int       u_verticesPerSide;
uniform float     u_sideSize;
uniform float     u_time;

/**
 * TODO
 */
float hash( vec2 p ) {
    float h = dot(p,vec2(127.1,311.7));
    return fract(sin(h)*43758.5453123);
}

/**
 * TODO
 */
float noise( in vec2 p ) {
    vec2 i = floor( p );
    vec2 f = fract( p );
    vec2 u = f*f*(3.0-2.0*f);
    return -1.0+2.0*mix(
                mix( hash( i + vec2(0.0,0.0) ),
                     hash( i + vec2(1.0,0.0) ),
                        u.x),
                mix( hash( i + vec2(0.0,1.0) ),
                     hash( i + vec2(1.0,1.0) ),
                        u.x),
                u.y);
}

/**
 * For considered vertex procedure reads height of its neighbors. Based on them
 * two vectors are calculated: right to left and up to down. Their normalized
 *  cross product is interpreted as the normal.
 *
 * @return Normal to the current vertex.
 */
vec3 calculateNormal(sampler2D textureSampler, vec2 coordinates) {
  float step    = 1. / float(u_verticesPerSide);

  float current = texture
                  (
                      textureSampler,
                      vec2
                      (
                          coordinates.x,
                          coordinates.y
                      )
                  ).r;

  float up      = texture
                  (
                      textureSampler,
                      vec2
                      (
                          coordinates.x,
                          coordinates.y + step
                      )
                  ).r;

  float down    = texture
                  (
                      textureSampler,
                      vec2
                      (
                          coordinates.x,
                          coordinates.y - step
                      )
                  ).r;

  float right   = texture
                  (
                      textureSampler,
                      vec2
                      (
                          coordinates.x + step,
                          coordinates.y
                      )
                  ).r;

  float left    = texture
                  (
                      textureSampler,
                      vec2
                      (
                          coordinates.x - step,
                          coordinates.y
                      )
                  ).r;

  vec3 d_x      = vec3(u_sideSize * 2.0 * step, right - left, 0.0);
  vec3 d_z      = vec3(0.0, up - down, u_sideSize *  2.0 * step);
  vec3 normal   = normalize(cross(d_z, d_x));

  return normal;
}

void main()
{

    float c = noise(250.0 * a_heightFieldTexCoords+u_time);
    float noiseHeight = texture(u_noiseTexture, a_heightFieldTexCoords).r;
    float disturbHeight = texture(u_heightFieldTexture, a_heightFieldTexCoords).r * 0.6;

    // Read the vertex height
    vec3 position = a_position;
//    if(abs(disturbHeight) > abs(noiseHeight)) {
            position.y = disturbHeight;
            v_normal = calculateNormal(u_heightFieldTexture, a_heightFieldTexCoords);
//
//    } else {
//        position.y =  noiseHeight + disturbHeight;
//        v_normal = calculateNormal(u_noiseTexture, a_heightFieldTexCoords);
//    }
//    if(disturbHeight < noiseHeight && disturbHeight < 0 && disturbHeight < 0) {
//        position.y =  disturbHeight;
//        v_normal = calculateNormal(u_noiseTexture, a_heightFieldTexCoords);
//    } else if(disturbHeight > noiseHeight && disturbHeight > 0 && disturbHeight > 0){
//        position.y = disturbHeight + noiseHeight;
//        v_normal = calculateNormal(u_heightFieldTexture, a_heightFieldTexCoords);
//    }
//    position.y =  disturbHeight + noiseHeight;
//    v_normal = calculateNormal(u_noiseTexture, a_heightFieldTexCoords) + calculateNormal(u_heightFieldTexture, a_heightFieldTexCoords);
    // Update its position according to transformations
    gl_Position   = u_projectionMatrix *
                    u_viewMatrix       *
                    u_modelMatrix      *
                    vec4(position, 1.0);

    // Pass values to the next shader
    v_position    = position;
    v_textureCoords = a_heightFieldTexCoords;
}