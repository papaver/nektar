//------------------------------------------------------------------------------
// nkPrint.cpp
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdarg.h>
#include "debug/nkPrint.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

// terminal colors, colored text on black

#define NK_COLOR_BLACK   ("\033[30m")
#define NK_COLOR_RED     ("\033[31m")
#define NK_COLOR_GREEN   ("\033[32m")
#define NK_COLOR_YELLOW  ("\033[33m")
#define NK_COLOR_BLUE    ("\033[34m")
#define NK_COLOR_MAGENTA ("\033[35m")
#define NK_COLOR_CYAN    ("\033[36m")
#define NK_COLOR_WHITE   ("\033[37m")
#define NK_COLOR_RESET   ("\033[0m")

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

nkPrintHandler nkDebug::nk_print_handler(nkDebug::nkDefaultPrintHandler);
nkWarnHandler  nkDebug::nk_warn_handler(nkDebug::nkDefaultWarnHandler);
nkErrorHandler nkDebug::nk_error_handler(nkDebug::nkDefaultErrorHandler);

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

void nkDebug::nkDefaultPrintHandler(const char* file, u32 line, const char *msg, ...)
{
  fprintf(stderr, "%s::%d::", file, line);
  va_list args;
  va_start(args, msg);
  vfprintf(stdout, msg, args);
  va_end(args);
}

//------------------------------------------------------------------------------

void nkDebug::nkDefaultWarnHandler(const char* file, u32 line, const char *msg, ...)
{
  fprintf(stderr, "WARNING::%s::%d::", file, line);
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  va_end(args);
}

//------------------------------------------------------------------------------

void nkDebug::nkDefaultErrorHandler(const char* file, u32 line, const char *msg, ...)
{ 
  fprintf(stderr, "ERROR::%s::%d::", file, line);
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  va_end(args);
}

