#version 120

//precision mediump float;
varying vec4 vSmoothColor;  	//interpolated colour to fragment shader

void main()
{
	//set the interpolated colour as the shader output
  vec4 temp = vSmoothColor;
  gl_FragColor = temp;
}