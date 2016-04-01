#version 330 core

in vec3 vVertex;
in vec2 texCoords;

out vec2 vTexCoords;
out vec3 vPosition;

uniform mat4 MVP;
uniform float waveTime;
uniform sampler2D heightFieldTex;

void main()
{
    vTexCoords = texCoords;

    vec3 vertex = vVertex;
    vertex.y = texture(heightFieldTex, texCoords).r;
    gl_Position = MVP*vec4(vertex,1);

    vPosition = vVertex;
}