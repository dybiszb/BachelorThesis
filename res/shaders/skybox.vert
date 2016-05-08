//==============================================================================
// The shader calculates appropriate texture coordinates (further needed by
// cubemap sampler) and transforms vertex to fit in the scene.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core

//==============================================================================
// In
//------------------------------------------------------------------------------
in vec3 v_position;

//==============================================================================
// Out
//------------------------------------------------------------------------------
out vec3   v_skyboxTexCoords;
precision highp float;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform mat4   u_modelMatrix;
uniform mat4   u_viewMatrix;
uniform mat4   u_projectionMatrix;

void main()
{
   // Cubemap sampler needs normalized vector from the center of the cube to
   // the part that one wants to sample. It happens that after normalizing each
   // vertex position one can interpret it as a vector and supply to the
   // sampler. Via interpolation process each fragment will acquire
   // appropriate vector. Such operation is possible because cubemap's center
   // is the scene origin.
   v_skyboxTexCoords = normalize(v_position);

   gl_Position       = u_projectionMatrix *
                       u_viewMatrix       *
                       u_modelMatrix      *
                       vec4(v_position, 1.0);
}