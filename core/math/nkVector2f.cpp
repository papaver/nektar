//------------------------------------------------------------------------------
// nkVector2f.cpp
//------------------------------------------------------------------------------

#include "math/nkVector2f.h"
#include "debug/nkAssert.h"

//- non-inline only ------------------------------------------------------------

#ifndef _NECKTAR_MATH_INLINE_

//------------------------------------------------------------------------------
// constructors
//------------------------------------------------------------------------------

NK_MATH_INLINE vec2f::vec2f() :
_x(),
_y()
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec2f::vec2f(f32 x) :
_x(x),
_y(0.0f)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec2f::vec2f(f32 x, f32 y) :
_x(x),
_y(y)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec2f::vec2f(vec2f_arg vec) :
_x(vec->_x),
_y(vec->_y)
{
}

//------------------------------------------------------------------------------
// getters
//------------------------------------------------------------------------------

NK_MATH_INLINE f32 vec2f::X() const
{
  return _x;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 vec2f::Y() const
{
  return _y;
}

//------------------------------------------------------------------------------
// setters
//------------------------------------------------------------------------------

NK_MATH_INLINE void vec2f::SetX(f32 x)
{
  _x = x;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec2f::SetY(f32 y)
{
  _y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec2f::SetXY(f32 x, f32 y)
{
  _x = x;
  _y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec2f::SetXY(vec4f_arg vec) 
{
  _x = vec->_x;
  _y = vec->_y;
}

//------------------------------------------------------------------------------
// operators
//------------------------------------------------------------------------------

NK_MATH_INLINE f32& vec2f::operator[](i32 i)
{
  return _v[i];
}

//------------------------------------------------------------------------------
// 2d vector operations
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd2(vec2f_ptr result, vec2f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x + rhs;
  f32 y = lhs->_y + rhs;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd2(vec2f_ptr result, vec2f_arg lhs, vec2f_arg rhs)
{
  f32 x = lhs->_x + rhs->_x;
  f32 y = lhs->_y + rhs->_y;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub2(vec2f_ptr result, vec2f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x - rhs;
  f32 y = lhs->_y - rhs;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub2(vec2f_ptr result, vec2f_arg lhs, vec2f_arg rhs)
{
  f32 x = lhs->_x - rhs->_x;
  f32 y = lhs->_y - rhs->_y;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecScale2(vec2f_ptr result, vec2f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x * rhs;
  f32 y = lhs->_y * rhs;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAbs2(vec2f_ptr result, vec2f_arg vec)
{
  f32 x = Absf(vec->_x);
  f32 y = Absf(vec->_y);
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNegate2(vec2f_ptr result, vec2f_arg vec)
{
  f32 x = -vec->_x;
  f32 y = -vec->_y;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLength2(vec2f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  
  f32 sum  = xx + yy;
  f32 root = Sqrtf(sum);
  return root;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLengthSqrd2(vec2f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  
  f32 sum = xx + yy;
  return sum;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNormalize2(vec2f_ptr result, vec2f_arg vec)
{
  f32 length  = VecLength2(vec);
  NK_ASSERT(length);
  f32 inverse = 1.0f / length;
  
  f32 x = vec->_x * inverse;
  f32 y = vec->_y * inverse;
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecLerp2(vec2f_ptr result, vec2f_arg lhs, vec2f_arg rhs, f32 t)
{
  f32 dx = rhs->_x - lhs->_x;
  f32 dy = rhs->_y - lhs->_y;
  
  f32 x = lhs->_x + (dx * t);
  f32 y = lhs->_y + (dy * t);
  
  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecZero2(vec2f_ptr vec)
{
  vec->_x = 0.0f;
  vec->_y = 0.0f;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecDot2(vec2f_arg lhs, vec2f_arg rhs)
{
  f32 x = lhs->_x * rhs->_x;
  f32 y = lhs->_y * rhs->_y;
  
  f32 sum = x + y;
  return sum;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecAngleBetween2(vec2f_ptr lhs, vec2f_arg rhs)
{
  f32 length_scale = VecLength2(lhs) * VecLength2(rhs);
  f32 acos_val     = VecDot2(lhs, rhs) / length_scale;
  
  return Acosf(acos_val);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool VecEqual2(vec2f_arg lhs, vec2f_arg rhs)
{
  bool x = lhs->_x == rhs->_x;
  bool y = lhs->_y == rhs->_y;
  
  bool is_equal = x && y;
  return is_equal;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecRand2(vec2f_ptr vec, f32 min, f32 max)
{
  NK_ASSERT(min <= max);
  
  f32 d = max - min;
  f32 x = min + (d * Randf());
  f32 y = min + (d * Randf());
  
  vec->_x = x;
  vec->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecRand2(vec2f_ptr vec, vec2f_arg min, vec2f_arg max)
{
  f32 dx = max->_x - min->_x;
  f32 dy = max->_y - min->_y;
  
  f32 x = min->_x + (dx * Randf());
  f32 y = min->_y + (dy * Randf());
  
  vec->_x = x;
  vec->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecPerp2(vec2f_ptr result, vec2f_arg vec)
{
  // pick negative y variant
  result->_x = vec->_y;
  result->_y = -vec->_x;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecProjVec2(vec2f_ptr result, vec2f_arg vec, vec2f_arg unit_vec)
{
  f32 dot = VecDot2(vec, unit_vec);
  VecScale2(result, vec, dot);
}

//------------------------------------------------------------------------------

#endif //  _NECKTAR_MATH_INLINE_
