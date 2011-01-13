//------------------------------------------------------------------------------
// nkMatrix4f.h
//------------------------------------------------------------------------------

#ifndef _NKMATRIX4F_H_
#define _NKMATRIX4F_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nkMath.h"
#include "math/nkVector4f.h"

//------------------------------------------------------------------------------
// typedefs
//------------------------------------------------------------------------------

typedef struct mtx4f;
typedef mtx4f *mtx4f_ptr; 
typedef const mtx4f *mtx4f_arg; 

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class mtx4f
{

  public:

    // Constructors
    explicit mtx4f();
    explicit mtx4f(mtx4f_arg mat);

    // Getters
    vec4f_ptr V0(); 
    vec4f_ptr V1(); 
    vec4f_ptr V2(); 
    vec4f_ptr V3(); 

    void GetScale(f32 *x, f32 *y, f32 *z);

    // Setters
    void SetScale(f32 s);
    void SetScale(f32 x, f32 y, f32 z);
    void SetTranslation(vec4f_arg trans);
    void SetTranslation(f32 x, f32 y, f32 z);
    void SetTranslation(f32 x, f32 y, f32 z, f32 w);

    // Operators

  public:

  /*
    union
    {
      f32 _m[16];
      struct { vec4f _v0, _v1, _v2, _v3; };
    };
  */
    vec4f _v0, _v1, _v2, _v3;

};

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

void LoadIdentity(mtx4f_ptr mat);
void LoadScale(mtx4f_ptr mat, f32 s);
void LoadScale(mtx4f_ptr mat, f32 sx, f32 sy, f32 sz);
void LoadRotationX(mtx4f_ptr mat, f32 phi);
void LoadRotationY(mtx4f_ptr mat, f32 theta);
void LoadRotationZ(mtx4f_ptr mat, f32 psi);
void LoadTranslation(mtx4f_ptr mat, f32 tx, f32 ty, f32 tz);
void LoadTranslation(mtx4f_ptr mat, vec4f_arg vec);
void LoadPrespective(mtx4f_ptr mat, f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
void LoadPrespective(mtx4f_ptr mat, f32 fov, f32 aspect, f32 near, f32 far);
void LoadOrthographic(mtx4f_ptr mat, f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
void LoadOrthographic(mtx4f_ptr mat, f32 width, f32 height, f32 near, f32 far);

void SetScale(mtx4f_ptr mat, f32 s);
void SetScale(mtx4f_ptr mat, f32 sx, f32 sy, f32 sz);
void SetScale(mtx4f_ptr mat, vec4f_arg vec);
void SetTranslation(mtx4f_ptr mat, f32 tx, f32 ty, f32 tz);
void SetTranslation(mtx4f_ptr mat, f32 tx, f32 ty, f32 tz, f32 tw);
void SetTranslation(mtx4f_ptr mat, vec4f_arg vec);

void RotateX(mtx4f_ptr mat, f32 phi);
void RotateY(mtx4f_ptr mat, f32 theta);
void RotateZ(mtx4f_ptr mat, f32 psi);

void VecMulMat(vec4f_ptr result, mtx4f_arg lhs, vec4f_arg rhs);
void MatMulMat(mtx4f_ptr result, mtx4f_arg lhs, mtx4f_arg rhs);

bool MatEqual(mtx4f_arg lhs, mtx4f_arg rhs);

#endif // _NKMATRIX4F_H_
