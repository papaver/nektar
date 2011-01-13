//------------------------------------------------------------------------------
// nkMath.h
//------------------------------------------------------------------------------

#ifndef _NKMATH_H_
#define _NKMATH_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nkType.h"
#include "math/nkConstant.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#ifdef NEKTAR_MATH_INLINE
  #define _NEKTAR_MATH_INLINE_
  #define NK_MATH_INLINE __attribute__ ((__always_inline__))
#else
  #define NK_MATH_INLINE
#endif

#ifdef NEKTAR_MATH_ASSEMBLY
  #if (NEKTAR_HARDWARE == NEKTAR_IPHONE_DEVICE) 
    #define NK_MATH_ARM_ASSEMBLY
  #endif
#endif

//------------------------------------------------------------------------------
// interface definitions
//------------------------------------------------------------------------------

// Trigonometric functions //

f32 Cosf(f32 a);
f32 Sinf(f32 a);
f32 Tanf(f32 a); 
f32 Acosf(f32 a);
f32 Asinf(f32 a);
f32 Atanf(f32 a);
f32 Atan2f(f32 ay, f32 ax);

// Hyperbolic functions //

f32 Coshf(f32 a);
f32 Sinhf(f32 a);
f32 Tanhf(f32 a);

// Exponential and logarithmic functions //

f32 Expf(f32 f);
f32 Frexpf(f32 f, i32 *exp);
f32 Ldexpf(f32 f, i32 exp);
f32 Logf(f32 f);
f32 Log10f(f32 f);
f32 Modf(f32 f, f32 *intpart);

// Power functions //

f32 Powf(f32 base, f32 exp);
f32 Sqrtf(f32 f);

// Rounding, absolute value and remainder functions //

f32 Absf(f32 f);
i32 SignBitf(f32 f);
f32 Ceilf(f32 f);
f32 Floorf(f32 f);
f32 Roundf(f32 f); 
f32 Truncf(f32 f);
f32 Fmodf(f32 num, f32 den);
f32 Remainderf(f32 num, f32 den);
f32 Maxf(f32 x, f32 y);
f32 Minf(f32 x, f32 y);

// Validation //

bool IsFinitef(f32 f);
bool IsInfintyf(f32 f);
bool IsNaNf(f32 f);
bool IsNormalf(f32 f);

// Random //

void Srand(u32 seed);
i32  Rand();
f32  Randf();

// Selects //

u32 SelectIfZero(u32 cond, u32 x, u32 y);
f32 SelectIfZerof(u32 cond, f32 x, f32 y);

// Bits //

bool IsPowerOfTwo(u32 v);
u32  GetHighestPowerOfTwo(u32 v);
u32  GetHighestMultipleOfPowerOfTwo(u32 v, u32 p);

//------------------------------------------------------------------------------

#endif // _NKMATH_H_

