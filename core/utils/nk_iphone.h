//------------------------------------------------------------------------------
// nk_iphone.h
//------------------------------------------------------------------------------

#ifndef _NKIPHONEUTILS_H_
#define _NKIPHONEUTILS_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "nektar/nektar.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

namespace nkiPhone
{

  bool getFilePath(const char *name, const char *type, char *path, u32 size);
  bool readAsciiFile(const char *path, char *contents, u32 size);

};

//------------------------------------------------------------------------------

#endif // _NKIPHONEUTILS_H_
