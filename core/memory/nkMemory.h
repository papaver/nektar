//------------------------------------------------------------------------------
// nkMemory.h
//------------------------------------------------------------------------------

#ifndef _NKMEMORY_H_
#define _NKMEMORY_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include <stddef.h>
#include "nektar/nkConfig.h"
#include "math/nk_math.h"
#include "debug/nk_debug.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

void* nk_malloc(size_t size);
void  nk_free(void *p); 

/* [moiz] this may be dangerous... need to verify
void* operator new(size_t size);
void* operator new[](size_t size);
void  operator delete(void *p);
void  operator delete[](void *p);
*/

//------------------------------------------------------------------------------

void* nk_malloc(size_t size, const char *file, u32 line);
void  nk_free(void *p, const char* file, u32 line); 

void* operator new(size_t size, const char *file, u32 line);
void* operator new[](size_t size, const char *file, u32 line);
void  operator delete(void *p, const char *file, u32 line);
void  operator delete[](void *p, const char *file, u32 line);

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

inline void* nk_malloc(size_t size, const char *file, u32 line)
{
  nkDebug::nk_print_handler(file, line, "nk_malloc request:\n");
  return nk_malloc(size);
}

inline void nk_free(void *p, const char* file, u32 line)
{
  nkDebug::nk_print_handler(file, line, "nk_free request:\n");
  nk_free(p);
}

inline void* operator new(size_t size, const char *file, u32 line)
{
  nkDebug::nk_print_handler(file, line, "new request:\n");
  return operator new(size);
}

inline void* operator new[](size_t size, const char *file, u32 line)
{
  nkDebug::nk_print_handler(file, line, "new[] request:\n");
  return operator new[](size);
}

inline void operator delete(void *p, const char *file, u32 line)
{
  nkDebug::nk_print_handler(file, line, "delete request:\n");
  operator delete(p);
}

inline void operator delete[](void *p, const char *file, u32 line)
{
  nkDebug::nk_print_handler(file, line, "delete[] request:\n");
  operator delete[](p);
}

//------------------------------------------------------------------------------
// debug macros (end of fine to prevent modifing header)
//------------------------------------------------------------------------------

#ifdef NEKTAR_DEBUG_MEMORY
  #define nk_malloc(size) nk_malloc(size, __FILE__, __LINE__)
  #define nk_free(p)      nk_free(p, __FILE__, __LINE__)

/* [moiz] this may be dangerous need to verify
  #define new[](size)     new[](size, __FILE__, __LINE__)
  #define new(size)       new(size, __FILE__, __LINE__)
  #define delete[](p)     delete[](p, __FILE__, __LINE__)
  #define delete(p)       delete(p, __FILE__, __LINE__)
*/
#endif

//------------------------------------------------------------------------------

#endif // _API_NKMEMORY_H_
