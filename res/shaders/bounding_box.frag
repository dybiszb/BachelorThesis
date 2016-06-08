//==============================================================================
// The shader simply assigns appropriate part of the texture to the fragment.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core
precision highp float;

void main()
{
    gl_FragColor = vec4(0.0, 0.0, 0.7, 0.3);
}