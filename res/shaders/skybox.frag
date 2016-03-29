#version 120
//precision highp float;

//1. declare a uniform sampler2d that contains the texture data
uniform samplerCube SkyBoxTexture;

//2. declare varying type which will transfer the texture coordinates from the vertex shader
varying vec3 textUV;

void main()
{

//3. set the final color to the output of the fragment shader
gl_FragColor = textureCube(SkyBoxTexture,textUV);

}