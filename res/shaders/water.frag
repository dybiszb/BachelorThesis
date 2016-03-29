#version 330 core

//precision mediump float;
//in vec4 vSmoothColor;  	//interpolated colour to fragment shader
uniform sampler2D myFloatTex;
out vec2 vTex;

void main()
{
  //set the interpolated colour as the shader output
//  vec4 temp = vSmoothColor;
  gl_FragColor = texture(myFloatTex,vTex);
}