//------------------------------------------------------------------------------
// nkTime.h
//------------------------------------------------------------------------------

#ifndef _NKTIME_H_
#define _NKTIME_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"

//------------------------------------------------------------------------------
// namespace
//------------------------------------------------------------------------------

namespace nkTime
{

  void Initialize();
  void Update();

  f32 GetStep();

  f32 GetStartTime();
  void GetStartTime(u32 *sec, u32 *usec);

  f32 GetCurrentTime();
  void GetCurrentTime(u32 *sec, u32 *usec);

  void IncTimer(f32 *timer);
  bool DecTimer(f32 *timer);
  
};

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

inline void nkTime::IncTimer(f32 *timer)
{
  f32 step = GetStep();
  *timer  += step;
}

//------------------------------------------------------------------------------

inline bool nkTime::DecTimer(f32 *timer)
{
  f32 step = GetStep();
  *timer  -= step;
  *timer   = Maxf(0.0f, *timer);

  return !*timer;
}

#endif // _NKTIME_H_
