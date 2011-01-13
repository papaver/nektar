//------------------------------------------------------------------------------
// Shader.vsh
//------------------------------------------------------------------------------

attribute vec4 a_position;
attribute vec2 a_uv;
attribute vec4 a_tint;

varying   vec2 v_uv;
varying   vec4 v_tint;

uniform   mat4 u_camera;

//------------------------------------------------------------------------------

void main()
{
  // set vertex attributes
	gl_Position = u_camera * a_position;
  gl_Position.w = 1.0;
  
  // pass to fragment shader
  v_uv   = a_uv;
  v_tint = a_tint;
}
