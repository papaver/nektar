//------------------------------------------------------------------------------
// nkShaderBase.h
//------------------------------------------------------------------------------

#ifndef _NKSHADERBASE_H_
#define _NKSHADERBASE_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include <OpenGLES/ES2/gl.h>
#include "nektar/nkConfig.h"

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

class nkShaderBase
{

  public:

    inline nkShaderBase();
    virtual ~nkShaderBase();

  public:

    inline GLuint getProgram();
    inline void   setProgram(GLuint program);

  public:

    inline bool loadProgram();
    bool validateProgram();

  protected:

    virtual bool onLoadProgram() = 0;
    virtual void onBindAttributeLocations(GLuint program) = 0;
    virtual void onSaveUniformLocations(GLuint program) = 0;

    bool loadProgram(const GLchar *name);
    bool compileShader(GLuint *shader, GLuint type, const GLchar *source);
    bool linkProgram(GLuint program);

  #if (BUILD < BUILD_FINAL)
    void logProgramInfo(GLuint program);
    void logShaderInfo(GLuint shader);
  #else
    void logProgramInfo(GLuint program) {}
    void logShaderInfo(GLuint shader) {}
  #endif

  private:

    GLuint mProgram;

};

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

inline nkShaderBase::nkShaderBase()
{
}

//------------------------------------------------------------------------------

inline GLuint nkShaderBase::getProgram()
{
  return mProgram;
}

//------------------------------------------------------------------------------

inline void nkShaderBase::setProgram(GLuint program)
{
  mProgram = program;
}

//------------------------------------------------------------------------------

inline bool nkShaderBase::loadProgram()
{
  bool result = onLoadProgram();
  return result;
}

#endif // _NKSHADERBASE_H_

