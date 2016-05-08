//==============================================================================
// The shader just sends its texture coordinates to the fragment shaders.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core
precision highp float;

//==============================================================================
// In / Attributes
//------------------------------------------------------------------------------
in vec3        a_position;
in vec2        a_heightFieldTexCoords;

//==============================================================================
// Out / Varying
//------------------------------------------------------------------------------
out vec2       v_heightFieldTexCoords;

void main()
{
   v_heightFieldTexCoords = a_heightFieldTexCoords;
   gl_Position            = vec4(a_position, 1);
}