//------------------------------------------------------------------------------
// nk_math.h
//------------------------------------------------------------------------------

#ifndef _API_NKMATH_H_
#define _API_NKMATH_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nkType.h"
#include "math/nkConstant.h"
#include "math/nkMath.h"
#include "math/nkVector2f.h"
#include "math/nkVector4f.h"
#include "math/nkMatrix4f.h"
#include "math/nkQuaternion.h"

//- inline includes ------------------------------------------------------------

#ifdef NEKTAR_MATH_INLINE
  #include "math/nkMath.cpp"
  #include "math/nkVector2f.cpp"
  #include "math/nkVector4f.cpp"
  #include "math/nkMatrix4f.cpp"
  #include "math/nkQuaternion.cpp"
#endif

//------------------------------------------------------------------------------

#endif // _API_NKMATH_H_
