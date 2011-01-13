//------------------------------------------------------------------------------
// nkShaderDebugFont.h
//------------------------------------------------------------------------------

#ifndef _NKSHADERDEBUGFONT_H_
#define _NKSHADERDEBUGFONT_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "render/shader/nkShaderBase.h"

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

class nkShaderDebugFont : public nkShaderBase
{

public:
  
  enum Attribute
  {
    ATTRIB_VERTEX,
    ATTRIB_UV,
    ATTRIB_COUNT
  };

  enum Uniform
  {
    UNIFORM_CAMERA,
    UNIFORM_WORLD,
    UNIFORM_TEXTURE,
    UNIFORM_TINT,
    UNIFORM_COUNT
  };

public:

  virtual ~nkShaderDebugFont();

public:

  GLuint* getUniforms();
  void    setViewport(GLfloat *camera_matrix);
  void    setWorld(GLfloat *world_matrix);
  void    setTint(GLfloat *tint);
  void    setTexture(GLint texture_id);
  void    setVertices(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr);
  void    setUVs(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr);

private:

  virtual bool onLoadProgram();
  virtual void onBindAttributeLocations(GLuint program);
  virtual void onSaveUniformLocations(GLuint program);

private:

  GLuint mUniforms[UNIFORM_COUNT];

};

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

inline GLuint* nkShaderDebugFont::getUniforms()
{
  return mUniforms;
}

//------------------------------------------------------------------------------

inline void nkShaderDebugFont::setViewport(GLfloat *camera_matrix)
{
  GLuint *uniforms = getUniforms();
  glUniformMatrix4fv(uniforms[UNIFORM_CAMERA], 1, GL_FALSE, camera_matrix);
}

//------------------------------------------------------------------------------

inline void nkShaderDebugFont::setWorld(GLfloat *world_matrix)
{
  GLuint *uniforms = getUniforms();
  glUniformMatrix4fv(uniforms[UNIFORM_WORLD], 1, GL_FALSE, world_matrix);
}

//------------------------------------------------------------------------------

inline void nkShaderDebugFont::setTint(GLfloat *tint)
{
  GLuint *uniforms = getUniforms();
  glUniform4fv(uniforms[UNIFORM_TINT], 1, tint);
}

//------------------------------------------------------------------------------

inline void nkShaderDebugFont::setTexture(GLint texture_id)
{
  GLuint *uniforms = getUniforms();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUniform1i(uniforms[UNIFORM_TEXTURE], 0);
}

//------------------------------------------------------------------------------

inline void nkShaderDebugFont::setVertices(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr)
{
  glVertexAttribPointer(ATTRIB_VERTEX, size, GL_FLOAT, normalized, stride, ptr);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
}

//------------------------------------------------------------------------------

inline void nkShaderDebugFont::setUVs(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr)
{
  glVertexAttribPointer(ATTRIB_UV, size, GL_FLOAT, normalized, stride, ptr);
  glEnableVertexAttribArray(ATTRIB_UV);
}

#endif // _NKSHADERDEBUGFONT_H_

