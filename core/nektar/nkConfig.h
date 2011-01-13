//------------------------------------------------------------------------------
// nkConfig.h
//  - global configuration file for nektar
//------------------------------------------------------------------------------

#ifndef _NKCONFIG_H_
#define _NKCONFIG_H_

//------------------------------------------------------------------------------
// builds
//------------------------------------------------------------------------------

#define BUILD_DEBUG   0   // full debug, no optimizations
#define BUILD_RELEASE 1   // partial debug, with optimizations
#define BUILD_FINAL   2   // no debug, full optimizations

#define BUILD BUILD_DEBUG

//------------------------------------------------------------------------------
// hardware
//------------------------------------------------------------------------------

#define NEKTAR_IPHONE_DEVICE    0
#define NEKTAR_IPHONE_SIMULATOR 1

// figure out hardware to build for
#if defined(TARGET_OS_IPHONE)
  #define NEKTAR_IPHONE
  #define NEKTAR_HARDWARE NEKTAR_IPHONE_DEVICE
#elif defined(TARGET_IPHONE_SIMULATOR)
  #define NEKTAR_IPHONE
  #define NEKTAR_HARDWARE NEKTAR_IPHONE_SIMULATOR
#endif

//------------------------------------------------------------------------------
// debug
//------------------------------------------------------------------------------

#define NEKTAR_DEBUG_MEMORY

#if (BUILD < BUILD_FINAL)
  #define NEKTAR_DEBUG_ASSERT
  #define NEKTAR_DEBUG_PRINT
#endif

//------------------------------------------------------------------------------
// math 
//------------------------------------------------------------------------------

// enable assembly math funtions for device
#if (BUILD > BUILD_DEBUG)
  #ifdef NEKTAR_IPHONE_DEVICE
    #define NEKTAR_MATH_ASSEMBLY
  #endif
#endif

// enable inlining of math functions
#if (BUILD == FINAL)
  #define NEKTAR_MATH_INLINE_ENABLE
#endif

//------------------------------------------------------------------------------
// texture
//------------------------------------------------------------------------------

#define MAX_TEXTURES 1028

//------------------------------------------------------------------------------

#endif // _NKCONFIG_H_
