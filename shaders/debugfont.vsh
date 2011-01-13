//------------------------------------------------------------------------------
// debugfont.vsh
//------------------------------------------------------------------------------

attribute vec4 a_position;
attribute vec2 a_uv;

varying   vec2 v_uv;

uniform   mat4 u_camera;
uniform   mat4 u_world;

//------------------------------------------------------------------------------

void main()
{
  // set vertex attributes
  gl_Position = u_camera * a_position;

  // pass to fragment shader
  v_uv = a_uv;
}
