//------------------------------------------------------------------------------
// nkAssert.cpp
//------------------------------------------------------------------------------

#include "debug/nkAssert.h"

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

nkAssertHandler nkDebug::nk_assert_handler(&nkDebug::nkDefaultAssertHandler);

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool nkDebug::nkDefaultAssertHandler(const char *condition, const char *message, const char *file, u32 line) 
{
  return true;
}

