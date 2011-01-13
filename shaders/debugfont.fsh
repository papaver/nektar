//------------------------------------------------------------------------------
// debugfont.fsh
//------------------------------------------------------------------------------

precision mediump float;

varying vec2      v_uv;

uniform sampler2D u_texture;
uniform vec4      u_tint;

//------------------------------------------------------------------------------

void main()
{
  // set fragment attributes
  gl_FragColor = texture2D(u_texture, v_uv);
}

