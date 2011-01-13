//------------------------------------------------------------------------------
// nkShaderSprite.cpp
//------------------------------------------------------------------------------

#include "render/shader/nkShaderSprite.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

nkShaderSprite::~nkShaderSprite()
{
}

//------------------------------------------------------------------------------

bool nkShaderSprite::onLoadProgram()
{
  bool result = loadProgram("sprite");
  return result;
}

//------------------------------------------------------------------------------

void nkShaderSprite::onBindAttributeLocations(GLuint program)
{
  // bind attribute locations
  glBindAttribLocation(program, ATTRIB_VERTEX, "a_position");
  glBindAttribLocation(program, ATTRIB_UV,     "a_uv");
  glBindAttribLocation(program, ATTRIB_TINT,   "a_tint");
}

//------------------------------------------------------------------------------

void nkShaderSprite::onSaveUniformLocations(GLuint program)
{
  GLuint *uniforms = getUniforms();

  // get uniform locations
  uniforms[UNIFORM_CAMERA]  = glGetUniformLocation(program, "u_camera");
  uniforms[UNIFORM_TEXTURE] = glGetUniformLocation(program, "u_texture");
}

