//------------------------------------------------------------------------------
// nkTouch.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "interface/nkTouch.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define MAX_TOUCHES        5
#define MAX_TOUCH_REQUESTS 128

//------------------------------------------------------------------------------
// enums
//------------------------------------------------------------------------------

enum TouchPhase
{
  TOUCH_BEGAN,
  TOUCH_MOVED,
  TOUCH_STATIONARY,
  TOUCH_ENDED,
  TOUCH_CANCELLED,
  TOUCH_INVALID,
};

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

typedef struct _Touch
{
  u32 id;
  u32 state;
  vec2f position;
} Touch;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

Touch          g_touch[MAX_TOUCHES];
u32            g_touch_count;

nkTouch::Request g_touch_requests[MAX_TOUCH_REQUESTS];
vec2f            g_touch_collision[MAX_TOUCH_REQUESTS];
u32              g_touch_request_count;

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

void nkTouch::Initialize()
{
  // invalidate touches
  g_touch[0].id    = 0;
  g_touch[0].state = TOUCH_INVALID;
  g_touch[1].id    = 0;
  g_touch[1].state = TOUCH_INVALID;
  g_touch[2].id    = 0;
  g_touch[2].state = TOUCH_INVALID;
  g_touch[3].id    = 0;
  g_touch[3].state = TOUCH_INVALID;
  g_touch[4].id    = 0;
  g_touch[4].state = TOUCH_INVALID;

  g_touch_request_count = 0;
}

//------------------------------------------------------------------------------
void nkTouch::Update()
{
  // clear out any touch requests, 
  //  they should all have been resolved by now
  g_touch_request_count = 0;

  for (u32 index = 0; index < MAX_TOUCHES; ++index)
  {
    if (g_touch[index].state == TOUCH_ENDED) 
    {
      g_touch[index].id    = 0;
      g_touch[index].state = TOUCH_INVALID;
    }
  }
}

//------------------------------------------------------------------------------

void nkTouch::HandleTouch(u32 touch_id, u16 state, f32 x, f32 y)
{
  // find the associated touch
  int index = 0;
  for (; index < MAX_TOUCHES; ++index)
  {
    if (g_touch[index].id == touch_id) 
    {
      break;
    }
  }

  // new touch
  if (index == MAX_TOUCHES) 
  {
    for (index = 0; index < MAX_TOUCHES; ++index)
    {
      if (g_touch[index].state == TOUCH_INVALID) 
      {
        break;
      }
    }
  }

  g_touch[index].id    = touch_id;
  g_touch[index].state = state;
  g_touch[index].position.SetXY(x, y);
}

//------------------------------------------------------------------------------

bool nkTouch::HitTest(vec2f_arg position, f32 radius)
{
  for (u32 index = 0; index < MAX_TOUCHES; ++index) 
  { 
    if (g_touch[index].state != TOUCH_ENDED) 
    {
      continue;
    }

    vec2f diff;
    VecSub2(&diff, &g_touch[index].position, position);

    f32 distance_sq = VecLengthSqrd2(&diff);
    if (distance_sq <= (radius * radius)) 
    {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

bool nkTouch::HitTestAny(vec2f_arg position, f32 radius)
{
  for (u32 index = 0; index < MAX_TOUCHES; ++index) 
  { 
    if (g_touch[index].state == TOUCH_INVALID) 
    {
      continue;
    }

    vec2f diff;
    VecSub2(&diff, &g_touch[index].position, position);

    f32 distance_sq = VecLengthSqrd2(&diff);
    if (distance_sq <= (radius * radius)) 
    {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

u32 nkTouch::TouchCount()
{
  u32 count = 0;
  for (u32 index = 0; index < MAX_TOUCHES; ++index) 
  { 
    count += (g_touch[index].state != TOUCH_INVALID); 
  }

  return count;
}

//------------------------------------------------------------------------------

/*
nkTouch::Handle nkTouch::RequestCircle(Request *request, Circle *circle)
{
  
}

//------------------------------------------------------------------------------

nkTouch::Handle nkTouch::RequestRectangle(Request *request, Rectangle *rectangle)
{
}

//------------------------------------------------------------------------------

nkTouch::Result* nkTouch::ResolveTouch(Handle handle)
{
}
*/

//------------------------------------------------------------------------------


