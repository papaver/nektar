//------------------------------------------------------------------------------
// nkPrint.h
//------------------------------------------------------------------------------

#ifndef _NKPRINT_H_
#define _NKPRINT_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "nektar/nkConfig.h"
#include "nektar/nkStd.h"
#include "math/nk_math.h"

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

#ifdef NEKTAR_DEBUG_PRINT
  #define nk_print(msg, ...) nkDebug::nk_print_handler(__FILE__, __LINE__, msg, ##__VA_ARGS__)
  #define nk_warn(msg, ...)  nkDebug::nk_warn_handler(__FILE__, __LINE__, msg, ##__VA_ARGS__)
  #define nk_error(msg, ...) nkDebug::nk_error_handler(__FILE__, __LINE__, msg, ##__VA_ARGS__)
#else
  #define nk_print(msg, ...) do { } while(0)
  #define nk_warn(msg, ...)  do { } while(0)
  #define nk_error(msg, ...) do { } while(0)
#endif

//------------------------------------------------------------------------------
// typedefs
//------------------------------------------------------------------------------

typedef void(*nkPrintHandler)(const char* file, u32 line, const char *msg, ...);
typedef void(*nkWarnHandler)(const char* file, u32 line, const char *msg, ...);
typedef void(*nkErrorHandler)(const char* file, u32 line, const char *msg, ...);

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

namespace nkDebug 
{
  NK_EXTERN nkPrintHandler nk_print_handler;
  NK_EXTERN nkWarnHandler  nk_warn_handler;
  NK_EXTERN nkErrorHandler nk_error_handler;
};

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

namespace nkDebug 
{

  void nkDefaultPrintHandler(const char* file, u32 line, const char *msg, ...);
  void nkDefaultWarnHandler(const char* file, u32 line, const char *msg, ...);
  void nkDefaultErrorHandler(const char* file, u32 line, const char *msg, ...);

};

//------------------------------------------------------------------------------

#endif // _NKPRINT_H_
