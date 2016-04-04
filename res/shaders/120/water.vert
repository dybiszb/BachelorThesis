#version 120

attribute vec3 vVertex;
attribute vec2 texCoords;

varying vec2 vTexCoords;
varying vec3 vPosition;

uniform mat4 MVP;
uniform float waveTime;
uniform sampler2D heightFieldTex;

void main()
{
    vTexCoords = texCoords;

    vec3 vertex = vVertex;
    vertex.y = texture2D(heightFieldTex, texCoords).r;
//    vertex.y = sin(0.7 * vVertex.x + waveTime) * cos(0.7 * vVertex.z +
//              waveTime) * 0.5;
    gl_Position = MVP*vec4(vertex,1);

    vPosition = vVertex;
}