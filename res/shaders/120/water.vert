#version 120

attribute vec3 vVertex;
attribute vec2 texCoords;

varying vec2 vTexCoords;
varying vec3 vPosition;
varying vec4 vColor;
varying vec3 vLightDirection;
varying vec3 vNormal;
varying vec3 vVertexCameraspace;

uniform vec3 lightPos;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform float waveTime;
uniform sampler2D heightFieldTex;
uniform int verticesPerSide;
uniform vec3 cameraPos;

vec3 calculateNormal() {
  float current = texture2D(heightFieldTex, vec2(texCoords.x, texCoords.y)).r;
  if(current < 0.005) {
    return vec3(0.0,1.0,0.0);
  }
  float step    = 1. / float(verticesPerSide);
  float up      = texture2D(heightFieldTex, vec2(texCoords.x, texCoords.y +step)).r;
  float down    = texture2D(heightFieldTex, vec2(texCoords.x, texCoords.y -step)).r;
  float right   = texture2D(heightFieldTex, vec2(texCoords.x + step,texCoords.y)).r;
  float left    = texture2D(heightFieldTex, vec2(texCoords.x - step, texCoords.y)).r;

  vec3 d_x = vec3(32.0 * 2.0 * step, right - left, 0.0);
  vec3 d_z = vec3(0.0, up - down, 32.0 *  2.0 * step);
  vec3 normal = normalize(cross(d_z, d_x));
  return normal;
}

float phongShading(vec3 normal, vec3 lightPos, vec3 cameraPos) {
    vec3 L = normalize(lightPos - vPosition);
    return  clamp(max(dot(normal,L),0.0) ,0.0, 1.0);
}

void main()
{
    vTexCoords = texCoords;
    vec3 vertex = vVertex;
    vertex.y = texture2D(heightFieldTex, texCoords).r;
    vPosition = vertex;
    gl_Position = uProjection * uView * uModel * vec4(vertex,1.0);

    vLightDirection = lightPos - vertex;
    vNormal = calculateNormal();

    //earthworm jimm
}