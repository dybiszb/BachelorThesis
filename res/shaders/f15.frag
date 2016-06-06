#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse;
//uniform sampler2D texture_specular1;

void main()
{
    color = vec4(texture(texture_diffuse, TexCoords));
//    color = vec4(TexCoords, 1.0, 1.0);
}