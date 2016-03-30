#version 330 core

in vec3 vVertex;
in vec2 texCoords;
out vec2 vTex;

uniform mat4 MVP;
uniform float waveTime;
uniform sampler2D myFloatTex;

void main()
{
   vTex = texCoords;
//   vSmoothColor = vec4(vColor,1);
   vec3 waveVec = vVertex;
//   waveVec.y = sin(0.7 * waveVec.x + waveTime) * cos(0.7 * waveVec.z +
//   waveTime) * 0.5;
   waveVec.y = texture(myFloatTex, texCoords).r;
   gl_Position = MVP*vec4(waveVec,1);
}