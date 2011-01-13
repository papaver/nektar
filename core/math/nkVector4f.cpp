//------------------------------------------------------------------------------
// nkVector4f.cpp
//------------------------------------------------------------------------------

#include "math/nkVector4f.h"
#include "debug/nkAssert.h"

//- non-inline only ------------------------------------------------------------

#ifndef _NECKTAR_MATH_INLINE_

//------------------------------------------------------------------------------
// constructors
//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f::vec4f() :
_x(),
_y(),
_z(),
_w()
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f::vec4f(f32 x) :
_x(x),
_y(0.0f),
_z(0.0f),
_w(0.0f)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f::vec4f(f32 x, f32 y) :
_x(x),
_y(y),
_z(0.0f),
_w(0.0f)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f::vec4f(f32 x, f32 y, f32 z) :
_x(x),
_y(y),
_z(z),
_w(0.0f)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f::vec4f(f32 x, f32 y, f32 z, f32 w) :
_x(x),
_y(y),
_z(z),
_w(w)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f::vec4f(vec4f_arg vec) :
_x(vec->_x),
_y(vec->_y),
_z(vec->_z),
_w(vec->_w)
{
}

//------------------------------------------------------------------------------
// getters
//------------------------------------------------------------------------------

NK_MATH_INLINE f32 vec4f::X() const
{
  return _x;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 vec4f::Y() const
{
  return _y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 vec4f::Z() const
{
  return _z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 vec4f::W() const
{
  return _w;
}

//------------------------------------------------------------------------------
// setters
//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetX(f32 x)
{
  _x = x;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetY(f32 y)
{
  _y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetZ(f32 z)
{
  _z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetW(f32 w)
{
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXY(f32 x, f32 y)
{
  _x = x;
  _y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXY(vec4f_arg vec)
{
  _x = vec->_x;
  _y = vec->_y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXZ(f32 x, f32 z)
{
  _x = x;
  _z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXW(f32 x, f32 w)
{
  _x = x;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetYZ(f32 y, f32 z)
{
  _y = y;
  _z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetYW(f32 y, f32 w)
{
  _y = y;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetZW(f32 z, f32 w)
{
  _z = z;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXYZ(f32 x, f32 y, f32 z)
{
  _x = x;
  _y = y;
  _z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXYZ(vec4f_arg vec)
{
  _x = vec->_x;
  _y = vec->_y;
  _z = vec->_z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXYW(f32 x, f32 y, f32 w)
{
  _x = x;
  _y = y;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXZW(f32 x, f32 z, f32 w)
{
  _x = x;
  _z = z;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetYZW(f32 y, f32 z, f32 w)
{
  _y = y;
  _z = z;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXYZW(f32 x, f32 y, f32 z, f32 w)
{
  _x = x;
  _y = y;
  _z = z;
  _w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetXAxis()
{
  SetXYZW(1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetYAxis()
{
  SetXYZW(0.0f, 1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetZAxis()
{
  SetXYZW(0.0f, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetUp()
{
  SetYAxis();
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetDown()
{
  SetXYZW(0.0f, -1.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetForward()
{
  SetZAxis();
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetBackward()
{
  SetXYZW(0.0f, 0.0f, -1.0f, 0.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetLeft()
{
  SetXAxis();
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void vec4f::SetRight()
{
  SetXYZW(-1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
// 2d vector operations
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd2(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x + rhs;
  f32 y = lhs->_y + rhs;

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd2(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x + rhs->_x;
  f32 y = lhs->_y + rhs->_y;

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub2(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x - rhs;
  f32 y = lhs->_y - rhs;

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub2(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x - rhs->_x;
  f32 y = lhs->_y - rhs->_y;

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecScale2(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x * rhs;
  f32 y = lhs->_y * rhs;

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAbs2(vec4f_ptr result, vec4f_arg vec)
{
  f32 x = Absf(vec->_x);
  f32 y = Absf(vec->_y);

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNegate2(vec4f_ptr result, vec4f_arg vec)
{
  f32 x = -vec->_x;
  f32 y = -vec->_y;

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLength2(vec4f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  
  f32 sum  = xx + yy;
  f32 root = Sqrtf(sum);
  return root;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLengthSqrd2(vec4f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  
  f32 sum = xx + yy;
  return sum;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNormalize2(vec4f_ptr result, vec4f_arg vec)
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

NK_MATH_INLINE void VecLerp2(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs, f32 t)
{
  f32 dx = rhs->_x - lhs->_x;
  f32 dy = rhs->_y - lhs->_y;
  
  f32 x = lhs->_x + (dx * t);
  f32 y = lhs->_y + (dy * t);

  result->_x = x;
  result->_y = y;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecZero2(vec4f_ptr vec)
{
  vec->_x = 0.0f;
  vec->_y = 0.0f;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecDot2(vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x * rhs->_x;
  f32 y = lhs->_y * rhs->_y;

  f32 sum = x + y;
  return sum;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecAngleBetween2(vec4f_ptr lhs, vec4f_arg rhs)
{
  // undefined...
  NK_ASSERT(0);
  return 0.0f;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool VecEqual2(vec4f_arg lhs, vec4f_arg rhs)
{
  bool x = lhs->_x == rhs->_x;
  bool y = lhs->_y == rhs->_y;

  bool is_equal = x & y;
  return is_equal;
}

//------------------------------------------------------------------------------

void VecRand2(vec4f_ptr vec, f32 min, f32 max)
{
  NK_ASSERT(min <= max);

  f32 d = max - min;
  f32 x = min + (d * Randf());
  f32 y = min + (d * Randf());
 
  vec->_x = x;
  vec->_y = y;
}

//------------------------------------------------------------------------------

void VecRand2(vec4f_ptr vec, vec4f_arg min, vec4f_arg max)
{
  f32 dx = max->_x - min->_x;
  f32 dy = max->_y - min->_y;

  f32 x = min->_x + (dx * Randf());
  f32 y = min->_y + (dy * Randf());
 
  vec->_x = x;
  vec->_y = y;
}

//------------------------------------------------------------------------------
// 3d vector operations
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd3(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x + rhs;
  f32 y = lhs->_y + rhs;
  f32 z = lhs->_z + rhs;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x + rhs->_x;
  f32 y = lhs->_y + rhs->_y;
  f32 z = lhs->_z + rhs->_z;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub3(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x - rhs;
  f32 y = lhs->_y - rhs;
  f32 z = lhs->_z - rhs;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x - rhs->_x;
  f32 y = lhs->_y - rhs->_y;
  f32 z = lhs->_z - rhs->_z;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecScale3(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x * rhs;
  f32 y = lhs->_y * rhs;
  f32 z = lhs->_z * rhs;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAbs3(vec4f_ptr result, vec4f_arg vec)
{
  f32 x = Absf(vec->_x);
  f32 y = Absf(vec->_y);
  f32 z = Absf(vec->_z);

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNegate3(vec4f_ptr result, vec4f_arg vec)
{
  f32 x = -vec->_x;
  f32 y = -vec->_y;
  f32 z = -vec->_z;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------
//          _______________________
// ||a|| = √((x*x) + (y*y) + (z*z)) 
//
//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLength3(vec4f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  f32 zz = vec->_z * vec->_z;
  
  f32 sum  = xx + yy + zz;
  f32 root = Sqrtf(sum);
  return root;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLengthSqrd3(vec4f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  f32 zz = vec->_z * vec->_z;

  f32 sum = xx + yy + zz;
  return sum;
}

//------------------------------------------------------------------------------
//
//       v       x         y         z
// â = ----- = ----- i + ----- j + ----- k
//     ||v||   ||v||     ||v||     ||v||   
//
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNormalize3(vec4f_ptr result, vec4f_arg vec)
{
  f32 length  = VecLength3(vec);
  NK_ASSERT(length);
  f32 inverse = 1.0f / length;

  f32 x = vec->_x * inverse;
  f32 y = vec->_y * inverse;
  f32 z = vec->_z * inverse;
  
  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecLerp3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs, f32 t)
{
  f32 dx = rhs->_x - lhs->_x;
  f32 dy = rhs->_y - lhs->_y;
  f32 dz = rhs->_z - lhs->_z;
  
  f32 x = lhs->_x + (dx * t);
  f32 y = lhs->_y + (dy * t);
  f32 z = lhs->_z + (dz * t);

  result->_x = x;
  result->_y = y;
  result->_z = z;
}
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecZero3(vec4f_ptr vec)
{
  vec->_x = 0.0f;
  vec->_y = 0.0f;
  vec->_z = 0.0f;
}

//------------------------------------------------------------------------------
//
// a . b = ||a|| ||b|| cos(θ)
// a . b = (a.x * b.x) + (a.y * by) + (a.z * bz)
//
//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecDot3(vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x * rhs->_x;
  f32 y = lhs->_y * rhs->_y;
  f32 z = lhs->_z * lhs->_z;

  f32 sum = x + y + z;
  return sum;
}

//------------------------------------------------------------------------------
//
// a x b = ||a|| ||b|| sin(θ)n
// a x b = ((a.y * b.z) - (a.z * b.y))i + 
//         ((a.z * b.x) - (a.x * b.z))j + 
//         ((a.x * b.y) - (a.y * b.x))k    (3d)
//
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecCross3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 yz = lhs->_y * rhs->_z;
  f32 zy = lhs->_z * rhs->_y;
  f32 zx = lhs->_z * rhs->_x;
  f32 xz = lhs->_x * rhs->_z;
  f32 xy = lhs->_x * rhs->_y;
  f32 yx = lhs->_y * rhs->_x;
  
  f32 x = yz - zy;
  f32 y = zx - xz;
  f32 z = xy - yx;

  result->_x = x;
  result->_y = y;
  result->_z = z;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecRotateAboutXAxis3(vec4f_ptr vec, f32 phi)
{
  f32 cos = Cosf(phi);
  f32 sin = Sinf(phi);

  f32 y = vec->_y;
  f32 z = vec->_z;

  f32 ry = (cos * y) - (sin * z);
  f32 rz = (sin * y) + (cos * z);

  vec->_y = ry;
  vec->_z = rz;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecRotateAboutYAxis3(vec4f_ptr vec, f32 theta)
{
  f32 cos = Cosf(theta);
  f32 sin = Sinf(theta);

  f32 x = vec->_x;
  f32 z = vec->_z;

  f32 rx =  (cos * x) + (sin * z);
  f32 rz = -(sin * x) + (cos * z);

  vec->_x = rx;
  vec->_z = rz;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecRotateAboutZAxis3(vec4f_ptr vec, f32 psi)
{
  f32 cos = Cosf(psi);
  f32 sin = Sinf(psi);

  f32 x = vec->_x;
  f32 y = vec->_y;

  f32 rx = (cos * x) - (sin * y);
  f32 ry = (sin * x) + (cos * y);

  vec->_x = rx;
  vec->_y = ry;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecAngleBetween3(vec4f_arg lhs, vec4f_arg rhs)
{
  // undefined...
  NK_ASSERT(0);
  return 0.0f;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool VecEqual3(vec4f_arg lhs, vec4f_arg rhs)
{
  bool x = lhs->_x == rhs->_x;
  bool y = lhs->_y == rhs->_y;
  bool z = lhs->_z == rhs->_z;

  bool is_equal = x & y & z;
  return is_equal;
}

//------------------------------------------------------------------------------

void VecRand3(vec4f_ptr vec, f32 min, f32 max)
{
  NK_ASSERT(min <= max);

  f32 d = max - min;
  f32 x = min + (d * Randf());
  f32 y = min + (d * Randf());
  f32 z = min + (d * Randf());
 
  vec->_x = x;
  vec->_y = y;
  vec->_z = z;
}

//------------------------------------------------------------------------------

void VecRand3(vec4f_ptr vec, vec4f_arg min, vec4f_arg max)
{
  f32 dx = max->_x - min->_x;
  f32 dy = max->_y - min->_y;
  f32 dz = max->_z - min->_z;

  f32 x = min->_x + (dx * Randf());
  f32 y = min->_y + (dy * Randf());
  f32 z = min->_z + (dz * Randf());
 
  vec->_x = x;
  vec->_y = y;
  vec->_z = z;
}

//------------------------------------------------------------------------------
// 4d vector operations
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd4(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x + rhs;
  f32 y = lhs->_y + rhs;
  f32 z = lhs->_z + rhs;
  f32 w = lhs->_w + rhs;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAdd4(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x + rhs->_x;
  f32 y = lhs->_y + rhs->_y;
  f32 z = lhs->_z + rhs->_z;
  f32 w = lhs->_w + rhs->_w;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub4(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x - rhs;
  f32 y = lhs->_y - rhs;
  f32 z = lhs->_z - rhs;
  f32 w = lhs->_w - rhs;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecSub4(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs)
{
  f32 x = lhs->_x - rhs->_x;
  f32 y = lhs->_y - rhs->_y;
  f32 z = lhs->_z - rhs->_z;
  f32 w = lhs->_w - rhs->_w;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecScale4(vec4f_ptr result, vec4f_arg lhs, f32 rhs)
{
  f32 x = lhs->_x * rhs;
  f32 y = lhs->_y * rhs;
  f32 z = lhs->_z * rhs;
  f32 w = lhs->_w * rhs;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecAbs4(vec4f_ptr result, vec4f_arg vec)
{
  f32 x = Absf(vec->_x);
  f32 y = Absf(vec->_y);
  f32 z = Absf(vec->_z);
  f32 w = Absf(vec->_w);

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNegate4(vec4f_ptr result, vec4f_arg vec)
{
  f32 x = -vec->_x;
  f32 y = -vec->_y;
  f32 z = -vec->_z;
  f32 w = -vec->_w;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLength4(vec4f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  f32 zz = vec->_z * vec->_z;
  f32 ww = vec->_w * vec->_w;
  
  f32 sum  = xx + yy + zz + ww;
  f32 root = Sqrtf(sum);
  return root;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE f32 VecLengthSqrd4(vec4f_arg vec)
{
  f32 xx = vec->_x * vec->_x;
  f32 yy = vec->_y * vec->_y;
  f32 zz = vec->_z * vec->_z;
  f32 ww = vec->_w * vec->_w;

  f32 sum = xx + yy + zz + ww;
  return sum;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecNormalize4(vec4f_ptr result, vec4f_arg vec)
{
  f32 length  = VecLength4(vec);
  NK_ASSERT(length);
  f32 inverse = 1.0f / length;

  f32 x = vec->_x * inverse;
  f32 y = vec->_y * inverse;
  f32 z = vec->_z * inverse;
  f32 w = vec->_w * inverse;
  
  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecLerp4(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs, f32 t)
{
  f32 dx = rhs->_x - lhs->_x;
  f32 dy = rhs->_y - lhs->_y;
  f32 dz = rhs->_z - lhs->_z;
  f32 dw = rhs->_w - lhs->_w;
  
  f32 x = lhs->_x + (dx * t);
  f32 y = lhs->_y + (dy * t);
  f32 z = lhs->_z + (dz * t);
  f32 w = lhs->_w + (dw * t);

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecZero4(vec4f_ptr vec)
{
  vec->_x = 0.0f;
  vec->_y = 0.0f;
  vec->_z = 0.0f;
  vec->_w = 0.0f;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE bool VecEqual4(vec4f_arg lhs, vec4f_arg rhs)
{
  bool x = lhs->_x == rhs->_x;
  bool y = lhs->_y == rhs->_y;
  bool z = lhs->_z == rhs->_z;
  bool w = lhs->_w == rhs->_w;

  bool is_equal = x & y & z & w;
  return is_equal;
}

//------------------------------------------------------------------------------

void VecRand4(vec4f_ptr vec, f32 min, f32 max)
{
  NK_ASSERT(min <= max);

  f32 d = max - min;
  f32 x = min + (d * Randf());
  f32 y = min + (d * Randf());
  f32 z = min + (d * Randf());
  f32 w = min + (w * Randf());
 
  vec->_x = x;
  vec->_y = y;
  vec->_z = z;
  vec->_w = w;
}

//------------------------------------------------------------------------------

void VecRand4(vec4f_ptr vec, vec4f_arg min, vec4f_arg max)
{
  f32 dx = max->_x - min->_x;
  f32 dy = max->_y - min->_y;
  f32 dz = max->_z - min->_z;
  f32 dw = max->_w - min->_w;

  f32 x = min->_x + (dx * Randf());
  f32 y = min->_y + (dy * Randf());
  f32 z = min->_z + (dz * Randf());
  f32 w = min->_w + (dw * Randf());
 
  vec->_x = x;
  vec->_y = y;
  vec->_z = z;
  vec->_w = w;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecProjVec(vec4f_ptr result, vec4f_arg vec, vec4f_arg unit_vec)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void VecProjPlane(vec4f_ptr result, vec4f_arg vec, vec4f_arg unit_normal)
{
}

//------------------------------------------------------------------------------

#endif //  _NECKTAR_MATH_INLINE_
