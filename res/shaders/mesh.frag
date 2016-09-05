//==============================================================================
// Shader simpy map texture coordinate onto pixel.
// Intended to use with models loaded via assimpl library.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core

//==============================================================================
// In
//------------------------------------------------------------------------------
in vec2           v_texCoords;

//==============================================================================
// Out
//------------------------------------------------------------------------------
out vec4          color;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform sampler2D u_textureDiffuse1;
uniform sampler2D u_textureSpecular1;

void main()
{
    color = vec4(texture(u_textureDiffuse1, v_texCoords));
}