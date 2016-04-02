#version 120
attribute vec3 vVertex;
attribute vec2 texCoords;
varying vec2 texUV;

uniform sampler2D sampler;

void main()
{
   texUV = texCoords;
   gl_Position = vec4(vVertex,1);
}