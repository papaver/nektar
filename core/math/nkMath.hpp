//------------------------------------------------------------------------------
// nkMath.hpp
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <math.h>

#include "math/nkMath.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Cosf(f32 a)
{
  f32 result = cos(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Sinf(f32 a)
{
  f32 result = sin(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Tanf(f32 a)
{
  f32 result = tan(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Acosf(f32 a)
{
  f32 result = acos(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Asinf(f32 a)
{
  f32 result = asin(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Atanf(f32 a)
{
  f32 result = atan(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Atan2f(f32 ay, f32 ax)
{
  f32 result = atan2(ay, ax);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Coshf(f32 a)
{
  f32 result = cosh(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Sinhf(f32 a)
{
  f32 result = sinh(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Tanhf(f32 a)
{
  f32 result = tanh(a);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Expf(f32 f)
{
  f32 result = exp(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Frexpf(f32 f, int *exp)
{
  f32 result = frexp(f, exp);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Ldexpf(f32 f, int exp)
{
  f32 result = ldexpf(f, exp);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Logf(f32 f)
{
  f32 result = log(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Log10f(f32 f)
{
  f32 result = log10(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Modf(f32 f, f32 *intpart)
{
  f32 result = modff(f, intpart);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Powf(f32 base, f32 exp)
{
  f32 result = pow(base, exp);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Sqrtf(f32 f)
{
  f32 result = sqrt(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Ceilf(f32 f)
{
  f32 result = ceil(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Absf(f32 f)
{
  f32 result = fabs(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Floorf(f32 f)
{
  f32 result = floor(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Fmodf(f32 num, f32 den)
{
  f32 result = fmod(num, den);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Roundf(f32 f)
{
  f32 result = round(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Truncf(f32 f)
{
  f32 result = trunc(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Remainderf(f32 num, f32 den)
{
  f32 result = remainderf(num, den);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Maxf(f32 x, f32 y)
{
#ifdef NK_MATH_ARM_ASSEMBLY
  // i stole this from the compiled release code but managed to 
  // write it myself after reading the tech manual, i missed the
  // sweet register trick though.  
  // the thing to remember is r0 always contains the first arg x
  // so that means since r0 is also the return register we only
  // need to check if y should be returned, nice eh?
  f32 result;
  __asm__ __volatile__ (
    "fmsr   s14,  %1  \n\t"  
    "fmsr   s15,  %2  \n\t"  
    "fcmps  s14, s15  \n\t"  // x > y
    "fmstat           \n\t"  // stall til compare bit is set
    "fmrsle  %0, s15  \n\t"  // ? x : y
    : "+r" (result)           
    : "r" (x), "r" (y)
    : "s14", "s15"
  );     
  return result;
#else

  // xcode compiles this without branches for iphone build
  f32 result = (x > y) ? x : y;
  return result;

#endif
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Minf(f32 x, f32 y)
{
#ifdef NK_MATH_ARM_ASSEMBLY
  f32 result;
  __asm__ __volatile__ (
    "fmsr   s14,  %1  \n\t"  
    "fmsr   s15,  %2  \n\t"  
    "fcmps  s14, s15  \n\t"  // x > y
    "fmstat           \n\t"  // stall til compare bit is set
    "fmrsge  %0, s15  \n\t"  // ? x : y
    : "+r" (result)           
    : "r" (x), "r" (y)
    : "s14", "s15"
  );     
  return result;
#else

  // xcode compiles this without branches for iphone build
  f32 result = (x < y) ? x : y;
  return result;

#endif
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool IsFinitef(f32 f)
{
  bool result = isfinite(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool IsInfintyf(f32 f)
{
  bool result = isinf(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool IsNaNf(f32 f)
{
  bool result = isnan(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool IsNormalf(f32 f)
{
  bool result = isnan(f);
  return result;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void Srand(u32 seed)
{
  srand(seed);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE i32 Rand()
{
  i32 r = rand();
  return r;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 Randf()
{
  f32 r = rand() / (static_cast<f32>(RAND_MAX) + 1.0f);
  return r;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE u32 SelectIfZero(u32 cond, u32 x, u32 y)
{
#ifdef NK_MATH_ARM_ASSEMBLY
  u32 result;
  __asm__ __volatile__ (
    "cmp   %1, #0  \n\t"  // cond == 0
    "moveq %0, %2  \n\t"  // ? x 
    "movne %0, %3"        // : y
    : "+r" (result) 
    : "r" (cond), "r" (x), "r" (y)
  );
  return result;
#else

  // xcode compiles this without branches for iphone build
  u32 result = cond == 0 ? x : y;
  return result;

#endif
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 SelectIfZerof(u32 cond, f32 x, f32 y)
{
#ifdef NK_MATH_ARM_ASSEMBLY
  f32 result;
  __asm__ __volatile__ (
    "cmp     %1,  #0  \n\t"  // cond == 0
    "fmsreq s15,  %2  \n\t"  // ? x 
    "fmsrne s15,  %3  \n\t"  // : y
    "fmrs    %0, s15"
    : "+r" (result) 
    : "r" (cond), "r" (x), "r" (y)
    : "s15"
  );
  return result;
#else

  // xcode compiles this without branches for iphone build
  f32 result = cond == 0 ? x : y;
  return result;

#endif
}

