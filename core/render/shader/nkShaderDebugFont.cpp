//------------------------------------------------------------------------------
// nkShaderDebugFont.cpp
//------------------------------------------------------------------------------

#include "render/shader/nkShaderDebugFont.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

nkShaderDebugFont::~nkShaderDebugFont()
{
}

//------------------------------------------------------------------------------

bool nkShaderDebugFont::onLoadProgram()
{
  bool result = loadProgram("debugfont");
  return result;
}

//------------------------------------------------------------------------------

void nkShaderDebugFont::onBindAttributeLocations(GLuint program)
{
  // bind attribute locations
  glBindAttribLocation(program, ATTRIB_VERTEX, "a_position");
  glBindAttribLocation(program, ATTRIB_UV,     "a_uv");
}

//------------------------------------------------------------------------------

void nkShaderDebugFont::onSaveUniformLocations(GLuint program)
{
  GLuint *uniforms = getUniforms();

  // get uniform locations
  uniforms[UNIFORM_CAMERA]  = glGetUniformLocation(program, "u_camera");
  uniforms[UNIFORM_WORLD]   = glGetUniformLocation(program, "u_world");
  uniforms[UNIFORM_TINT]    = glGetUniformLocation(program, "u_tint");
  uniforms[UNIFORM_TEXTURE] = glGetUniformLocation(program, "u_texture");
}

