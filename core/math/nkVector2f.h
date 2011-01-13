//------------------------------------------------------------------------------
// nkVector2f.h
//------------------------------------------------------------------------------

#ifndef _NKVECTOR2F_H_
#define _NKVECTOR2F_H_

//------------------------------------------------------------------------------
// includes 
//------------------------------------------------------------------------------

#include "math/nkMath.h"
#include "math/nkVector4f.h"

//------------------------------------------------------------------------------
// typdefs
//------------------------------------------------------------------------------

typedef struct vec2f;
typedef vec2f *vec2f_ptr; 
typedef const vec2f *vec2f_arg; 

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class vec2f 
{
  
  public:
  
    // Constructors
    explicit vec2f();
    explicit vec2f(f32 x);
    explicit vec2f(f32 x, f32 y);
    explicit vec2f(vec2f_arg vec);
  
    // Getters
    f32 X() const;
    f32 Y() const;
  
    // Setters
    void SetX(f32 x);
    void SetY(f32 y);
    void SetXY(f32 x, f32 y);
    void SetXY(vec4f_arg vec);
  
    // Operators
    f32& operator[](i32 i);
  
  public:
  
    union
    {
      f32 _v[2];
      struct { f32 _x, _y; };
    };
};

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

void VecAdd2(vec2f_ptr result, vec2f_arg lhs, f32 rhs);
void VecAdd2(vec2f_ptr result, vec2f_arg lhs, vec2f_arg rhs);
void VecSub2(vec2f_ptr result, vec2f_arg lhs, f32 rhs);
void VecSub2(vec2f_ptr result, vec2f_arg lhs, vec2f_arg rhs);
void VecScale2(vec2f_ptr result, vec2f_arg lhs, f32 rhs);
void VecAbs2(vec2f_ptr result, vec2f_arg vec);
void VecNegate2(vec2f_ptr result, vec2f_arg vec);
f32  VecLength2(vec2f_arg vec);
f32  VecLengthSqrd2(vec2f_arg vec);
void VecNormalize2(vec2f_ptr result, vec2f_arg vec);
void VecLerp2(vec2f_ptr result, vec2f_arg lhs, vec2f_arg rhs, f32 t);
void VecZero2(vec2f_ptr vec);
f32  VecDot2(vec2f_arg lhs, vec2f_arg rhs);
f32  VecAngleBetween2(vec2f_ptr lhs, vec2f_arg rhs);
bool VecEqual2(vec2f_arg lhs, vec2f_arg rhs);
void VecRand2(vec2f_ptr vec, f32 min, f32 max);
void VecRand2(vec2f_ptr vec, vec2f_arg min, vec2f_arg max);
void VecPerp2(vec2f_ptr result, vec2f_arg vec);

void VecProjVec2(vec2f_ptr result, vec2f_arg vec, vec2f_arg unit_vec);

//------------------------------------------------------------------------------
// include implementation
//------------------------------------------------------------------------------

#endif // _NKVECTOR2F_H_
