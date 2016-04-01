#version 330 core

//precision mediump float;
uniform sampler2D sampler;
uniform float sideSize;
in vec2 texUV;

void main()
{
  float step = 1.0 / sideSize;
  float up = texture2D(sampler, vec2(texUV.x, texUV.y + step)).r;

  gl_FragColor = vec4(up, 0,0,0);
}