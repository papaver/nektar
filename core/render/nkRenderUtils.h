//------------------------------------------------------------------------------
// nkRenderUtils.h
//------------------------------------------------------------------------------

#ifndef _NKRENDERUTILS_H_
#define _NKRENDERUTILS_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include <OpenGLES/ES2/gl.h>

//------------------------------------------------------------------------------
// forward declarations 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

GLuint loadDefaultTexture();
GLuint loadTargaTexture(const char *path);
GLuint loadBitmapTexture(const char *path);

#endif // _NKRENDERUTILS_H_