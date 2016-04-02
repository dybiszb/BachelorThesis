#version 120
attribute vec3 vVertex;
varying vec3 textUV;
uniform mat4 MVP;

void main()
{
   textUV = normalize(vVertex);
   gl_Position = MVP*vec4(vVertex,1);
}