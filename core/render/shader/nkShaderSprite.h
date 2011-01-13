//------------------------------------------------------------------------------
// nkShaderSprite.h
//------------------------------------------------------------------------------

#ifndef _NKSHADERSPRITE_H_
#define _NKSHADERSPRITE_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "render/shader/nkShaderBase.h"

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

class nkShaderSprite : public nkShaderBase
{

public:
  
  enum Attribute
  {
    ATTRIB_VERTEX,
    ATTRIB_UV,
    ATTRIB_TINT,
    ATTRIB_COUNT
  };

  enum Uniform
  {
    UNIFORM_CAMERA,
    UNIFORM_TEXTURE,
    UNIFORM_COUNT
  };

public:

  virtual ~nkShaderSprite();

public:

  GLuint* getUniforms();
  void    setViewport(GLfloat *camera_matrix);
  void    setTexture(GLint texture_id);
  void    setVertices(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr);
  void    setUVs(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr);
  void    setTint(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr);

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

inline GLuint* nkShaderSprite::getUniforms()
{
  return mUniforms;
}

//------------------------------------------------------------------------------

inline void nkShaderSprite::setViewport(GLfloat *camera_matrix)
{
  GLuint *uniforms = getUniforms();
  glUniformMatrix4fv(uniforms[UNIFORM_CAMERA], 1, GL_FALSE, camera_matrix);
}

//------------------------------------------------------------------------------

inline void nkShaderSprite::setTexture(GLint texture_id)
{
  GLuint *uniforms = getUniforms();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUniform1i(uniforms[UNIFORM_TEXTURE], 0);
}

//------------------------------------------------------------------------------

inline void nkShaderSprite::setVertices(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr)
{
  glVertexAttribPointer(ATTRIB_VERTEX, size, GL_FLOAT, normalized, stride, ptr);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
}

//------------------------------------------------------------------------------

inline void nkShaderSprite::setUVs(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr)
{
  glVertexAttribPointer(ATTRIB_UV, size, GL_FLOAT, normalized, stride, ptr);
  glEnableVertexAttribArray(ATTRIB_UV);
}

//------------------------------------------------------------------------------

inline void nkShaderSprite::setTint(GLint size, GLboolean normalized, GLsizei stride, const GLvoid *ptr)
{
  glVertexAttribPointer(ATTRIB_TINT, size, GL_UNSIGNED_BYTE, normalized, stride, ptr);
  glEnableVertexAttribArray(ATTRIB_TINT);
}

#endif // _NKSHADERSPRITE_H_

