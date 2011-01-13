//------------------------------------------------------------------------------
// nkMatrix4f.cpp
//------------------------------------------------------------------------------

#include "math/nkMatrix4f.h"
#include "debug/nkAssert.h"

//- non-inline only ------------------------------------------------------------

#ifndef _NECKTAR_MATH_INLINE_

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

NK_MATH_INLINE mtx4f::mtx4f() :
_v0(),
_v1(),
_v2(),
_v3()
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE mtx4f::mtx4f(mtx4f_arg mat) :
_v0(mat->_v0),
_v1(mat->_v1),
_v2(mat->_v2),
_v3(mat->_v3)
{
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f_ptr mtx4f::V0()
{
  return &_v0;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f_ptr mtx4f::V1() 
{
  return &_v1;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f_ptr mtx4f::V2() 
{
  return &_v2;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE vec4f_ptr mtx4f::V3() 
{
  return &_v3;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void mtx4f::SetScale(f32 s)
{
  _v0.SetX(s);
  _v1.SetY(s);
  _v2.SetZ(s);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void mtx4f::SetScale(f32 sx, f32 sy, f32 sz)
{
  _v0.SetX(sx);
  _v1.SetY(sy);
  _v2.SetZ(sz);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void mtx4f::SetTranslation(vec4f_arg trans)
{
  _v3 = *trans;
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void mtx4f::SetTranslation(f32 tx, f32 ty, f32 tz)
{
  _v3.SetXYZ(tx, ty, tz);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void mtx4f::SetTranslation(f32 tx, f32 ty, f32 tz, f32 tw)
{
  _v3.SetXYZW(tx, ty, tz, tw);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadIdentity(mtx4f_ptr mat)
{
  mat->_v0.SetXYZW(1.0f, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f, 1.0f, 0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f, 1.0f, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadScale(mtx4f_ptr mat, f32 s)
{
  mat->_v0.SetXYZW(   s, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f,    s, 0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f,    s, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadScale(mtx4f_ptr mat, f32 sx, f32 sy, f32 sz)
{
  mat->_v0.SetXYZW(  sx, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f,   sy, 0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f,   sz, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
// 
// - matrix rotations... an imaginary concept for a feeble mind
//   - there is only scale and translate...
// - so, how is a point rotated about the origin? 
// - the distance from the origin cannot change, this is most important
// - the z translation must occur in terms of y, and y in terms of z
// - project y using cos into a shared space between y and z
// - then translate in terms of z using sin
//
//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadRotationX(mtx4f_ptr mat, f32 phi)
{
  f32 cos = Cosf(phi);
  f32 sin = Sinf(phi);

  mat->_v0.SetXYZW(1.0f, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f,  cos, -sin, 0.0f);
  mat->_v2.SetXYZW(0.0f,  sin,  cos, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadRotationY(mtx4f_ptr mat, f32 theta)
{
  f32 cos = Cosf(theta);
  f32 sin = Sinf(theta);

  mat->_v0.SetXYZW(cos,  0.0f,  sin, 0.0f);
  mat->_v1.SetXYZW(0.0f, 1.0f, 0.0f, 0.0f);
  mat->_v2.SetXYZW(-sin, 0.0f,  cos, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadRotationZ(mtx4f_ptr mat, f32 psi)
{
  f32 cos = Cosf(psi);
  f32 sin = Sinf(psi);

  mat->_v0.SetXYZW(cos, -sin,  0.0f, 0.0f);
  mat->_v1.SetXYZW(sin,  cos,  0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f, 1.0f, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadTranslation(mtx4f_ptr mat, f32 tx, f32 ty, f32 tz)
{
  mat->_v0.SetXYZW(1.0f, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f, 1.0f, 0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f, 1.0f, 0.0f);
  mat->_v3.SetXYZW(  tx,   ty,   tz, 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadTranslation(mtx4f_ptr mat, vec4f_arg t)
{
  mat->_v0.SetXYZW(  1.0f,   0.0f,   0.0f, 0.0f);
  mat->_v1.SetXYZW(  0.0f,   1.0f,   0.0f, 0.0f);
  mat->_v2.SetXYZW(  0.0f,   0.0f,   1.0f, 0.0f);
  mat->_v3.SetXYZW(t->X(), t->Y(), t->Z(), 1.0f);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void SetScale(mtx4f_ptr mat, f32 s)
{
  mat->_v0.SetX(s);
  mat->_v1.SetY(s);
  mat->_v2.SetZ(s);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void SetScale(mtx4f_ptr mat, f32 sx, f32 sy, f32 sz)
{
  mat->_v0.SetX(sx);
  mat->_v1.SetY(sy);
  mat->_v2.SetZ(sz);
}  

//------------------------------------------------------------------------------

NK_MATH_INLINE void SetScale(mtx4f_ptr mat, vec4f_arg vec)
{
  mat->_v0.SetX(vec->X());
  mat->_v1.SetY(vec->Y());
  mat->_v2.SetZ(vec->Z());
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void SetTranslation(mtx4f_ptr mat, f32 tx, f32 ty, f32 tz)
{
  mat->_v3.SetXYZ(tx, ty, tz);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void SetTranslation(mtx4f_ptr mat, f32 tx, f32 ty, f32 tz, f32 tw)
{
  mat->_v3.SetXYZW(tx, ty, tz, tw);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void SetTranslation(mtx4f_ptr mat, vec4f_arg vec)
{
  mat->_v3 = *vec;
}

//------------------------------------------------------------------------------
// RotateX, RotateY and RotateZ are to avoid the confusion of which way to
// use MatMulMat to get a proper rotation. It's done once here for reuse
//------------------------------------------------------------------------------

NK_MATH_INLINE void RotateX(mtx4f_ptr mat, f32 phi)
{
  mtx4f rot;
  LoadRotationX(&rot, phi);
  MatMulMat(mat, &rot, mat);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void RotateY(mtx4f_ptr mat, f32 theta)
{
  mtx4f rot;
  LoadRotationY(&rot, theta);
  MatMulMat(mat, &rot, mat);
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void RotateZ(mtx4f_ptr mat, f32 psi)
{
  mtx4f rot;
  LoadRotationZ(&rot, psi);
  MatMulMat(mat, &rot, mat);
}

//------------------------------------------------------------------------------
// 
// - generalized version, can be off center 
// - the pespective view matrix is a little more complicated
//   - since the view is now skewed a simple scale translate will not work
//     - why? because the x/y scale is now a factor of z (depth)
//     - to be usable in a matrix x/y translate needs to be a factor of z
//   - project x into z space, and let the translation be a factor of z
//     - this should result in an orthographic view again
//   - since the depth value shouldn't be clamped from 0.0f-1.0f multipy z by far 
//
// moiz:: depth is from 0.0f to 1.0f
//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadPrespective(mtx4f_ptr mat, f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
  f32 width  = right - left;
  f32 height = top - bottom;
  f32 depth  = far - near;

  f32 sx = (2.0f * near) / width;  // = (2.0f / width) * near;
  f32 sy = (2.0f * near) / height; // = (2.0f / height) * near;
  f32 sz = far / depth;            // = (1.0f / depth) * far;

  f32 xz = - (right + left) / width;
  f32 yz = - (top + bottom) / height;

  f32 tz = - (far * near) / depth;

  // moiz:: is my translate in the incorrect place here?
  // it should be in the last row right ?
  mat->_v0.SetXYZW(  sx, 0.0f,   xz, 0.0f);
  mat->_v1.SetXYZW(0.0f,   sy,   yz, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f,   sz,   tz);
  mat->_v3.SetXYZW(0.0f, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
// 
// - centered version
// - since the view is centered, the translates can be removed from x/y
// - fov can be used replace width/height values
// - z remains the same
//
// moiz:: depth is from 0.0f to 1.0f
//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadPrespective(mtx4f_ptr mat, f32 fov, f32 aspect, f32 near, f32 far)
{
  f32 zfactor = 1.0f / Tanf(fov / 2.0f);

  f32 depth  = far - near;

  f32 sx = zfactor * aspect;
  f32 sy = zfactor;
  f32 sz = far / depth;            

  f32 tz = - (far * near) / depth;

  // moiz:: is my translate in the incorrect place here?
  // it should be in the last row right ?
  mat->_v0.SetXYZW(  sx, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f,   sy, 0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f,   sz,   tz);
  mat->_v3.SetXYZW(0.0f, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
// 
// - generalized version, can be off center
// - the orthographic view matrix is a simple scale/translate operation
//   - P = S * T
//   - caculate the ratio from old space to new space
//     - ex. 10.0f-20.0f --> 2.0f-4.0f = (2.0f-0.0f)/(20.0f-10.0f) = 1.0f/5.0f
//   - recenter the old space into the new space 
//     - ex. 2.0f-4.0f --> 0.0f-2.0f = -(10.0f/5.0f) = -2.0f
//     - ex. 2.0f-4.0f --> -1.0f-1.0f = -((10.0f/5.0f)+(20.0f/5.0f)) = -3.0f
//
// moiz:: should depth be from 0.0f to 1.0f or -1.0f to 1.0 ?
//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadOrthographic(mtx4f_ptr mat, f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
  f32 width  = right - left;
  f32 height = top - bottom;
  f32 depth  = far - near;

  f32 sx = 2.0f / width;
  f32 sy = 2.0f / height;
  f32 sz = 2.0f / depth;

  f32 tx = - (right + left) / width;
  f32 ty = - (top + bottom) / height;
  f32 tz = - (far + near) / depth;
  
  // moiz:: is my translate in the incorrect place here?
  // it should be in the last row right ?
  mat->_v0.SetXYZW(  sx, 0.0f, 0.0f,   tx);
  mat->_v1.SetXYZW(0.0f,   sy, 0.0f,   ty);
  mat->_v2.SetXYZW(0.0f, 0.0f,   sz,   tz);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
// 
// - centered version
// - even simpler, only scale involved
// - since there are no translations they can be removed
//
// moiz:: should depth be from 0.0f to 1.0f or -1.0f to 1.0 ?
//        will need to still translate in the z if so...
//------------------------------------------------------------------------------

NK_MATH_INLINE void LoadOrthographic(mtx4f_ptr mat, f32 width, f32 height, f32 near, f32 far)
{
  f32 depth  = far - near;

  f32 sx = 2.0f / width;
  f32 sy = 2.0f / height;
  f32 sz = 2.0f / depth;

  mat->_v0.SetXYZW(  sx, 0.0f, 0.0f, 0.0f);
  mat->_v1.SetXYZW(0.0f,   sy, 0.0f, 0.0f);
  mat->_v2.SetXYZW(0.0f, 0.0f,   sz, 0.0f);
  mat->_v3.SetXYZW(0.0f, 0.0f, 0.0f, 1.0f);
}

//------------------------------------------------------------------------------
//
// - post multiply the matrix because of the layout 
// - the ROW vector is multiplied by the COL of the matrix
// - the result vector is a ROW vector 
// - the translation value should always be multiplied by w in the vector
//  
//  [ x', y', z', w' ] = [ x, y, z, w ] [ sx,  0,  0,  0 ]
//                                      [  0, sy,  0,  0 ]
//                                      [  0,  0, sz,  0 ]
//                                      [ tx, ty, tz, tw ] 
//
//
//------------------------------------------------------------------------------

NK_MATH_INLINE void VecMulMat(volatile vec4f_ptr result, mtx4f_arg lhs, vec4f_arg rhs)
{
#ifdef NK_MATH_ASSEMBLY_ARM
  vfp_mode_set(VFP_CBIT_RUN_FAST|VFP_CBIT_VEC_LEN_4);
  __asm__ __volatile__ (
    "fldmias  %0,  {s0-s3}   \n\t"  // load rhs (scalar bank)
    "fldmias  %1, {s8-s23}   \n\t"  // load lhs
    "fmuls   s24,  s8, s0    \n\t"  // result  = _v0 * x
    "fmacs   s24, s12, s1    \n\t"  // result += _v1 * y
    "fmacs   s24, s16, s2    \n\t"  // result += _v2 * z
    "fmacs   s24, s20, s3    \n\t"  // result += _v3 * w
    "fstmias  %2, {s24-s27}  \n\t"  // save result
    : // no output 
    : "r" (rhs), "r" (lhs), "r" (result)
    : "r0", "memory", VFP_CLOBBER_S00_S03, VFP_CLOBBER_S08_S23, VFP_CLOBBER_S24_S27
  );     
  vfp_mode_reset();
#else

  f32 v0x = lhs->_v0._x * rhs->_x;
  f32 v0y = lhs->_v0._y * rhs->_x;
  f32 v0z = lhs->_v0._z * rhs->_x;
  f32 v0w = lhs->_v0._w * rhs->_x;

  f32 v1x = lhs->_v1._x * rhs->_y;
  f32 v1y = lhs->_v1._y * rhs->_y;
  f32 v1z = lhs->_v1._z * rhs->_y;
  f32 v1w = lhs->_v1._w * rhs->_y;

  f32 v2x = lhs->_v2._x * rhs->_z;
  f32 v2y = lhs->_v2._y * rhs->_z;
  f32 v2z = lhs->_v2._z * rhs->_z;
  f32 v2w = lhs->_v2._w * rhs->_z;

  f32 v3x = lhs->_v3._x * rhs->_w;
  f32 v3y = lhs->_v3._y * rhs->_w;
  f32 v3z = lhs->_v3._z * rhs->_w;
  f32 v3w = lhs->_v3._w * rhs->_w;

  f32 x = v0x + v1x + v2x + v3x;
  f32 y = v0y + v1y + v2y + v3y;
  f32 z = v0z + v1z + v2z + v3z;
  f32 w = v0w + v1w + v2w + v3w;

  result->_x = x;
  result->_y = y;
  result->_z = z;
  result->_w = w;

#endif
}

//------------------------------------------------------------------------------

NK_MATH_INLINE void MatMulMat(mtx4f_ptr result, mtx4f_arg lhs, mtx4f_arg rhs)
{
#ifdef NK_MATH_ASSEMBLY_ARM
  vfp_mode_set(VFP_CBIT_RUN_FAST|VFP_CBIT_VEC_LEN_4);
  __asm__ __volatile__ (

    "fldmias  %1, {s8-s23}   \n\t"  // load lhs

    "fldmias %0!,  {s0-s7}   \n\t"  // load rhs._v0 & rhs._v1 (scalar bank)
    "fmuls   s24,  s8, s0    \n\t"  // result  = v0 * v0.x
    "fmacs   s24, s12, s1    \n\t"  // result += v1 * v0.y
    "fmacs   s24, s16, s2    \n\t"  // result += v2 * v0.z
    "fmacs   s24, s20, s3    \n\t"  // result += v3 * v0.w
    "fstmias %2!, {s24-s27}  \n\t"  // save result

    "fmuls   s28,  s8, s4    \n\t"  // result  = v0 * v1.x
    "fmacs   s28, s12, s5    \n\t"  // result += v1 * v1.y
    "fmacs   s28, s16, s6    \n\t"  // result += v2 * v1.z
    "fmacs   s28, s20, s7    \n\t"  // result += v3 * v1.w
    "fstmias %2!, {s28-s31}  \n\t"  // save result

    "fldmias %0!,  {s0-s7}   \n\t"  // load rhs._v2 & rhs._v3 (scalar bank)
    "fmuls   s24,  s8, s0    \n\t"  // result  = v0 * v2.x
    "fmacs   s24, s12, s1    \n\t"  // result += v1 * v2.y
    "fmacs   s24, s16, s2    \n\t"  // result += v2 * v2.z
    "fmacs   s24, s20, s3    \n\t"  // result += v3 * v2.w
    "fstmias %2!, {s24-s27}  \n\t"  // save result

    "fmuls   s28,  s8, s4    \n\t"  // result  = v0 * v3.x
    "fmacs   s28, s12, s5    \n\t"  // result += v1 * v3.y
    "fmacs   s28, s16, s6    \n\t"  // result += v2 * v3.z
    "fmacs   s28, s20, s7    \n\t"  // result += v3 * v3.w
    "fstmias  %2, {s28-s31}  \n\t"  // save result

    : // no output 
    : "r" (rhs), "r" (lhs), "r" (result)
    : "r0", "memory", VFP_CLOBBER_S00_S31
  );     
  vfp_mode_reset();
#else

  f32 x0x0 = lhs->_v0._x * rhs->_v0._x;
  f32 y0x0 = lhs->_v0._y * rhs->_v0._x;
  f32 z0x0 = lhs->_v0._z * rhs->_v0._x;
  f32 w0x0 = lhs->_v0._w * rhs->_v0._x;

  f32 x1y0 = lhs->_v1._x * rhs->_v0._y;
  f32 y1y0 = lhs->_v1._y * rhs->_v0._y;
  f32 z1y0 = lhs->_v1._z * rhs->_v0._y;
  f32 w1y0 = lhs->_v1._w * rhs->_v0._y;

  f32 x2z0 = lhs->_v2._x * rhs->_v0._z;
  f32 y2z0 = lhs->_v2._y * rhs->_v0._z;
  f32 z2z0 = lhs->_v2._z * rhs->_v0._z;
  f32 w2z0 = lhs->_v2._w * rhs->_v0._z;

  f32 x3w0 = lhs->_v3._x * rhs->_v0._w;
  f32 y3w0 = lhs->_v3._y * rhs->_v0._w;
  f32 z3w0 = lhs->_v3._z * rhs->_v0._w;
  f32 w3w0 = lhs->_v3._w * rhs->_v0._w;

  f32 x0x1 = lhs->_v0._x * rhs->_v1._x;
  f32 y0x1 = lhs->_v0._y * rhs->_v1._x;
  f32 z0x1 = lhs->_v0._z * rhs->_v1._x;
  f32 w0x1 = lhs->_v0._w * rhs->_v1._x;

  f32 x1y1 = lhs->_v1._x * rhs->_v1._y;
  f32 y1y1 = lhs->_v1._y * rhs->_v1._y;
  f32 z1y1 = lhs->_v1._z * rhs->_v1._y;
  f32 w1y1 = lhs->_v1._w * rhs->_v1._y;

  f32 x2z1 = lhs->_v2._x * rhs->_v1._z;
  f32 y2z1 = lhs->_v2._y * rhs->_v1._z;
  f32 z2z1 = lhs->_v2._z * rhs->_v1._z;
  f32 w2z1 = lhs->_v2._w * rhs->_v1._z;

  f32 x3w1 = lhs->_v3._x * rhs->_v1._w;
  f32 y3w1 = lhs->_v3._y * rhs->_v1._w;
  f32 z3w1 = lhs->_v3._z * rhs->_v1._w;
  f32 w3w1 = lhs->_v3._w * rhs->_v1._w;

  f32 x0x2 = lhs->_v0._x * rhs->_v2._x;
  f32 y0x2 = lhs->_v0._y * rhs->_v2._x;
  f32 z0x2 = lhs->_v0._z * rhs->_v2._x;
  f32 w0x2 = lhs->_v0._w * rhs->_v2._x;

  f32 x1y2 = lhs->_v1._x * rhs->_v2._y;
  f32 y1y2 = lhs->_v1._y * rhs->_v2._y;
  f32 z1y2 = lhs->_v1._z * rhs->_v2._y;
  f32 w1y2 = lhs->_v1._w * rhs->_v2._y;

  f32 x2z2 = lhs->_v2._x * rhs->_v2._z;
  f32 y2z2 = lhs->_v2._y * rhs->_v2._z;
  f32 z2z2 = lhs->_v2._z * rhs->_v2._z;
  f32 w2z2 = lhs->_v2._w * rhs->_v2._z;

  f32 x3w2 = lhs->_v3._x * rhs->_v2._w;
  f32 y3w2 = lhs->_v3._y * rhs->_v2._w;
  f32 z3w2 = lhs->_v3._z * rhs->_v2._w;
  f32 w3w2 = lhs->_v3._w * rhs->_v2._w;

  f32 x0x3 = lhs->_v0._x * rhs->_v3._x;
  f32 y0x3 = lhs->_v0._y * rhs->_v3._x;
  f32 z0x3 = lhs->_v0._z * rhs->_v3._x;
  f32 w0x3 = lhs->_v0._w * rhs->_v3._x;

  f32 x1y3 = lhs->_v1._x * rhs->_v3._y;
  f32 y1y3 = lhs->_v1._y * rhs->_v3._y;
  f32 z1y3 = lhs->_v1._z * rhs->_v3._y;
  f32 w1y3 = lhs->_v1._w * rhs->_v3._y;

  f32 x2z3 = lhs->_v2._x * rhs->_v3._z;
  f32 y2z3 = lhs->_v2._y * rhs->_v3._z;
  f32 z2z3 = lhs->_v2._z * rhs->_v3._z;
  f32 w2z3 = lhs->_v2._w * rhs->_v3._z;

  f32 x3w3 = lhs->_v3._x * rhs->_v3._w;
  f32 y3w3 = lhs->_v3._y * rhs->_v3._w;
  f32 z3w3 = lhs->_v3._z * rhs->_v3._w;
  f32 w3w3 = lhs->_v3._w * rhs->_v3._w;

  f32 xx = x0x0 + x1y0 + x2z0 + x3w0;
  f32 xy = y0x0 + y1y0 + y2z0 + y3w0;
  f32 xz = z0x0 + z1y0 + z2z0 + z3w0;
  f32 xw = w0x0 + w1y0 + w2z0 + w3w0;

  f32 yx = x0x1 + x1y1 + x2z1 + x3w1;
  f32 yy = y0x1 + y1y1 + y2z1 + y3w1;
  f32 yz = z0x1 + z1y1 + z2z1 + z3w1;
  f32 yw = w0x1 + w1y1 + w2z1 + w3w1;

  f32 zx = x0x2 + x1y2 + x2z2 + x3w2;
  f32 zy = y0x2 + y1y2 + y2z2 + y3w2;
  f32 zz = z0x2 + z1y2 + z2z2 + z3w2;
  f32 zw = w0x2 + w1y2 + w2z2 + w3w2;

  f32 wx = x0x3 + x1y3 + x2z3 + x3w3;
  f32 wy = y0x3 + y1y3 + y2z3 + y3w3;
  f32 wz = z0x3 + z1y3 + z2z3 + z3w3;
  f32 ww = w0x3 + w1y3 + w2z3 + w3w3;

  result->_v0.SetXYZW(xx, xy, xz, xw);
  result->_v1.SetXYZW(yx, yy, yz, yw);
  result->_v2.SetXYZW(zx, zy, zz, zw);
  result->_v3.SetXYZW(wx, wy, wz, ww);

#endif
}

//------------------------------------------------------------------------------

bool MatEqual(mtx4f_arg lhs, mtx4f_arg rhs)
{
  bool v0 = VecEqual4(&lhs->_v0, &rhs->_v0);
  bool v1 = VecEqual4(&lhs->_v1, &rhs->_v1);
  bool v2 = VecEqual4(&lhs->_v2, &rhs->_v2);
  bool v3 = VecEqual4(&lhs->_v3, &rhs->_v3);

  bool result = v0 & v1 & v2 & v3;
  return result;
}

//------------------------------------------------------------------------------

#endif //  _NECKTAR_MATH_INLINE_
