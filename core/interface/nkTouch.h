//------------------------------------------------------------------------------
// nkTouch.h
//------------------------------------------------------------------------------

#ifndef _NKTOUCH_H_
#define _NKTOUCH_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

namespace nkTouch
{

//------------------------------------------------------------------------------
// forward declarations 
//------------------------------------------------------------------------------

  //struct Request;
  //struct Result;

//------------------------------------------------------------------------------
// enums
//------------------------------------------------------------------------------

  enum State 
  {
    TOUCH_DOWN,
    TOUCH_MOVE,
    TOUCH_UP,
  };

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

  typedef struct _Handle
  {
    i32 touch_handle;
  } Handle;

  typedef struct _Circle
  {
    vec2f position;
    f32 radius;
  } Circle;

  typedef struct _Rectangle
  {
    vec2f position;
    vec2f size;
  } Rectangle;

  typedef struct _Request
  {
    i32 states;
  } Request;

  typedef struct _Result 
  {
    State state;
    vec2f position;
  } Result;

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

  void Initialize();
  void Update();

  bool HitTest(vec2f_arg position, f32 radius);
  bool HitTestAny(vec2f_arg position, f32 radius);

  u32 TouchCount();

  void HandleTouch(u32 touch_id, u16 state, f32 x, f32 y);

/*
  Handle RequestCircle(Request *request, Circle *circle);
  Handle RequestRectangle(Request *request, Rectangle *rectangle);
  Result* ResolveTouch(Handle handle);
*/

};

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

#endif // _NKTOUCH_H_

