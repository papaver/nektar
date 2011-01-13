//------------------------------------------------------------------------------
// nkVector4f.h
//------------------------------------------------------------------------------

#ifndef _NKVECTOR4F_H_
#define _NKVECTOR4F_H_

//------------------------------------------------------------------------------
// includes 
//------------------------------------------------------------------------------

#include "math/nkMath.h"

//------------------------------------------------------------------------------
// typdefs
//------------------------------------------------------------------------------

typedef struct vec4f;
typedef vec4f *vec4f_ptr; 
typedef const vec4f *vec4f_arg; 

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class vec4f 
{

  public:

    // Constructors
    explicit vec4f();
    explicit vec4f(f32 x);
    explicit vec4f(f32 x, f32 y);
    explicit vec4f(f32 x, f32 y, f32 z);
    explicit vec4f(f32 x, f32 y, f32 z, f32 w);
    explicit vec4f(vec4f_arg vec);

    // Getters
    f32 X() const;
    f32 Y() const;
    f32 Z() const;
    f32 W() const;

    // Setters
    void SetX(f32 x);
    void SetY(f32 y);
    void SetZ(f32 z);
    void SetW(f32 w);
    void SetXY(f32 x, f32 y);
    void SetXY(vec4f_arg vec);
    void SetXZ(f32 x, f32 z);
    void SetXW(f32 x, f32 w);
    void SetYZ(f32 y, f32 z);
    void SetYW(f32 y, f32 w);
    void SetZW(f32 z, f32 w);
    void SetXYZ(f32 x, f32 y, f32 z);
    void SetXYZ(vec4f_arg vec);
    void SetXYW(f32 x, f32 y, f32 w);
    void SetXZW(f32 x, f32 z, f32 w);
    void SetYZW(f32 y, f32 z, f32 w);
    void SetXYZW(f32 x, f32 y, f32 z, f32 w);
    void SetXAxis();
    void SetYAxis();
    void SetZAxis();
    void SetUp();
    void SetDown();
    void SetForward();
    void SetBackward();
    void SetLeft();
    void SetRight();

    // Operators

  public:

    union
    {
      f32 _v[4];
      struct { f32 _x, _y, _z, _w; };
    };
};

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

void VecAdd2(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecAdd2(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecSub2(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecSub2(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecScale2(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecAbs2(vec4f_ptr result, vec4f_arg vec);
void VecNegate2(vec4f_ptr result, vec4f_arg vec);
f32  VecLength2(vec4f_arg vec);
f32  VecLengthSqrd2(vec4f_arg vec);
void VecNormalize2(vec4f_ptr result, vec4f_arg vec);
void VecLerp2(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs, f32 t);
void VecZero2(vec4f_ptr vec);
f32  VecDot2(vec4f_arg lhs, vec4f_arg rhs);
f32  VecAngleBetween2(vec4f_ptr lhs, vec4f_arg rhs);
bool VecEqual2(vec4f_arg lhs, vec4f_arg rhs);
void VecRand2(vec4f_ptr vec, f32 min, f32 max);
void VecRand2(vec4f_ptr vec, vec4f_arg min, vec4f_arg max);

void VecAdd3(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecAdd3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecSub3(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecSub3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecScale3(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecAbs3(vec4f_ptr result, vec4f_arg vec);
void VecNegate3(vec4f_ptr result, vec4f_arg vec);
f32  VecLength3(vec4f_arg vec);
f32  VecLengthSqrd3(vec4f_arg vec);
void VecNormalize3(vec4f_ptr result, vec4f_arg vec);
void VecLerp3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs, f32 t);
void VecZero3(vec4f_ptr vec);
f32  VecDot3(vec4f_arg lhs, vec4f_arg rhs);
void VecCross3(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecRotateAboutXAxis3(vec4f_ptr vec, f32 phi);
void VecRotateAboutYAxis3(vec4f_ptr vec, f32 theta);
void VecRotateAboutZAxis3(vec4f_ptr vec, f32 psi);
f32  VecAngleBetween3(vec4f_arg lhs, vec4f_arg rhs);
bool VecEqual3(vec4f_arg lhs, vec4f_arg rhs);
void VecRand3(vec4f_ptr vec);
void VecRand3(vec4f_ptr vec, vec4f_arg min, vec4f_arg max);

void VecAdd4(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecAdd4(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecSub4(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecSub4(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs);
void VecScale4(vec4f_ptr result, vec4f_arg lhs, f32 rhs);
void VecAbs4(vec4f_ptr result, vec4f_arg vec);
void VecNegate4(vec4f_ptr result, vec4f_arg vec);
f32  VecLength4(vec4f_arg vec);
f32  VecLengthSqrd4(vec4f_arg vec);
void VecNormalize4(vec4f_ptr result, vec4f_arg vec);
void VecLerp4(vec4f_ptr result, vec4f_arg lhs, vec4f_arg rhs, f32 t);
void VecZero4(vec4f_ptr vec);
bool VecEqual4(vec4f_arg lhs, vec4f_arg rhs);
void VecRand4(vec4f_ptr vec);
void VecRand4(vec4f_ptr vec, vec4f_arg min, vec4f_arg max);

void VecProjVec(vec4f_ptr result, vec4f_arg vec, vec4f_arg unit_vec);
void VecProjPlane(vec4f_ptr result, vec4f_arg vec, vec4f_arg unit_normal);

//------------------------------------------------------------------------------
// include implementation
//------------------------------------------------------------------------------

#endif // _NKVECTOR4F_H_
