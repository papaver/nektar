//------------------------------------------------------------------------------
// Shader.fsh
//------------------------------------------------------------------------------

precision mediump float;

varying vec2      v_uv;
varying vec4      v_tint;

uniform sampler2D u_texture;

//------------------------------------------------------------------------------

void main()
{
  // set fragment attributes
  gl_FragColor = texture2D(u_texture, v_uv) * v_tint;
  gl_FragColor = texture2D(u_texture, v_uv);
}

