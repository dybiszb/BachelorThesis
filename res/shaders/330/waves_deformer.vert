#version 330 core
in vec3 vVertex;
in vec2 texCoords;
out vec2 texUV;

uniform sampler2D sampler;

void main()
{
   texUV = texCoords;
   gl_Position = vec4(vVertex,1);
}