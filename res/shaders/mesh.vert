//==============================================================================
// Shader in charge of calculating per-pixel texture coordinates and
// calculating vertex position. It is intendet to use with models loadded via
// assimp library.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core

//==============================================================================
// In
//------------------------------------------------------------------------------
 layout (location = 0) in vec3 a_position;
 layout (location = 1) in vec3 a_normal;
 layout (location = 2) in vec2 a_texCoords;

//==============================================================================
// Out
//------------------------------------------------------------------------------
 out vec2                      v_texCoords;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
 uniform mat4                  u_modelMatrix;
 uniform mat4                  u_viewMatrix;
 uniform mat4                  u_projectionMatrix;

 void main()
 {
     gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix
                   * vec4(a_position, 1.0f);
     v_texCoords = a_texCoords;
 }