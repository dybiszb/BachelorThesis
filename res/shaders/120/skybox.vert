#version 120
attribute vec3 vVertex;
varying vec3 textUV;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
   textUV = normalize(vVertex);
   gl_Position = uProjection * uView * uModel *vec4(vVertex,1);
}