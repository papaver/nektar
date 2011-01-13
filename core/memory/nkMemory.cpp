//------------------------------------------------------------------------------
// nkMemory.cpp
//------------------------------------------------------------------------------

#include <stdlib.h>
#include "memory/nkMemory.h"
#include "debug/nk_debug.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#undef nk_malloc
#undef nk_free
#undef new
#undef new[]
#undef delete
#undef delete[]

#ifndef NEKTAR_DEBUG_MEMORY
  #ifdef nk_print
    #undef nk_print
  #endif
  #define nk_print(...) 
#endif

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

void* nk_malloc(size_t size) 
{
  NK_ASSERT_MSG(size, "mallocing nothing");
  void *p = malloc(size);
  NK_ASSERT_MSG(p, "out of memory");
  //nk_print("nk_malloc -> %x, size -> %d\n", p, size);
  return p;
}

//------------------------------------------------------------------------------

void nk_free(void *p)
{
  NK_ASSERT_MSG(p, "freeing nothing");
  //nk_print("nk_free -> %x\n", p);
  free(p);
}

//------------------------------------------------------------------------------

void* operator new(size_t size)
{
  NK_ASSERT_MSG(size, "newing nothing");
  void *p = nk_malloc(size);
  NK_ASSERT_MSG(p, "out of memory");
  //nk_print("new -> %x, size -> %d\n", p, size);
  return p;
}

//------------------------------------------------------------------------------

void* operator new[](size_t size)
{
  NK_ASSERT_MSG(size, "newing[] nothing");
  void *p = nk_malloc(size);
  NK_ASSERT_MSG(p, "out of memory");
  //nk_print("new[] -> %x, size -> %d\n", p, size);
  return p;
}

//------------------------------------------------------------------------------

void operator delete(void *p)
{
  NK_ASSERT_MSG(p, "deleting null!");
  //nk_print("delete -> %x\n", p);
  nk_free(p);
}

//------------------------------------------------------------------------------

void operator delete[](void *p)
{
  NK_ASSERT_MSG(p, "deleting[] null!");
  //nk_print("delete[] -> %x\n", p);
  nk_free(p);
}