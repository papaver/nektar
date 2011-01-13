//------------------------------------------------------------------------------
// nkAssert.h
//
//  Macro Magic:
//
//   - Defaults
//      __LINE__ -> (int) current line number
//      __FILE__ -> (char*) path to current file 
//
//   - Concatenation
//      #define CONCAT(a,b) (a##b = 0) -> CONCAT(cat, 0) -> cat0 = 0
//
//   - String Convert
//      #define STR(e) (#e) -> STR(x < 0) -> "x < 0"
//
//   - Variable Arguments (## eats , if no args)
//      #define PRINT(m, ...) printf(m, ##__VA_ARGS__)
//
//   - Multiline (allows for correct ; before else)
//      #define MULTI(x) \
//        do { \ 
//          a(x); \
//          a(x); \
//        } while(0)
//         
//------------------------------------------------------------------------------

#ifndef _NKASSERT_H_
#define _NKASSERT_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "nektar/nkConfig.h"
#include "nektar/nkStd.h"
#include "math/nkType.h"  

//------------------------------------------------------------------------------
// typdefs
//------------------------------------------------------------------------------

typedef bool(*nkAssertHandler)(const char *condition, const char *message, const char *file, u32 line);

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

namespace nkDebug 
{
  NK_EXTERN nkAssertHandler nk_assert_handler;
};

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------

#ifdef NEKTAR_DEBUG_ASSERT
  #if (NEKTAR_HARDWRE == NEKTAR_IPHONE_DEVICE)
    #define NK_HALT() (__asm("trap"))
  #elif (NEKTAR_HARDWRE == NEKTAR_IPHONE_SIMULATOR)
    #define NK_HALT() (__asm("int3"))
  #else
    #define NK_HALT() ((void)0)
  #endif
#else
  #define NK_HALT() ((void)0)
#endif

#ifdef NEKTAR_DEBUG_ASSERT
  #define NK_STOP() (__builtin_trap())
#else
  #define NK_STOP() ((void)0)
#endif

#ifdef NEKTAR_DEBUG_ASSERT
  #define NK_ASSERT_MSG(cond, msg)                                             \
    do  {                                                                      \
      if (!(cond)) {                                                           \
        (*nkDebug::nk_assert_handler)(NK_STR(cond), msg, __FILE__, __LINE__);  \
      }                                                                        \
    } while(0) 
#else
  #define NK_ASSERT_MSG(cond, msg)  \
    do {                            \
    } while(0)
#endif
  
#define NK_ASSERT(cond) NK_ASSERT_MSG(cond, "")

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

namespace nkDebug 
{

  bool nkDefaultAssertHandler(const char *condition, const char *message, const char *file, u32 line);

};

//------------------------------------------------------------------------------

#endif // _NKASSERT_H_
