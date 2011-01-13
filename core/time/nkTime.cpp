//------------------------------------------------------------------------------
// nkTime.cpp
//------------------------------------------------------------------------------

#include <sys/time.h>
#include "time/nkTime.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define NANOSECOND (1.0f/1000000.0f)

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

static timeval g_time_start;
static timeval g_time_current;
static timeval g_time_previous;
static timeval g_time_step;

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

int timeval_subtract(timeval *result, timeval *x, timeval *y);

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

void nkTime::Initialize()
{
  // save start time of app
  gettimeofday(&g_time_start, NULL);

  // set current time
  g_time_current = g_time_start;

  // init time step
  g_time_step.tv_usec;
}

//------------------------------------------------------------------------------

void nkTime::Update()
{
  // get current time
  g_time_previous = g_time_current;
  gettimeofday(&g_time_current, NULL);

  // update step
  timeval_subtract(&g_time_step, &g_time_current, &g_time_previous);
}

//------------------------------------------------------------------------------

f32 nkTime::GetStep()
{
  f32 step = g_time_step.tv_sec + (g_time_step.tv_usec * NANOSECOND);
  return step;
}

//------------------------------------------------------------------------------

f32 nkTime::GetStartTime()
{
  f32 seconds = g_time_start.tv_sec + (g_time_start.tv_usec * NANOSECOND);
  return seconds;
}

//------------------------------------------------------------------------------

void nkTime::GetStartTime(u32 *sec, u32 *usec)
{
  *sec  = g_time_start.tv_sec;
  *usec = g_time_start.tv_usec;
}

//------------------------------------------------------------------------------

f32 nkTime::GetCurrentTime()
{
  f32 seconds = g_time_current.tv_sec + (g_time_current.tv_usec * NANOSECOND);
  return seconds;
}

//------------------------------------------------------------------------------

void nkTime::GetCurrentTime(u32 *sec, u32 *usec)
{
  *sec  = g_time_current.tv_sec;
  *usec = g_time_current.tv_usec;
}

//------------------------------------------------------------------------------
// this is lifted from 
//  Edition 0.12, last updated 2007-10-27, of The GNU C Library Reference Manual, 
//  for Version 2.8 of the GNU C Library (thanks!)
//------------------------------------------------------------------------------

int 
timeval_subtract(timeval *result, timeval *x, timeval *y)
{
  // perform the carry for the later subtraction by updating y
  if (x->tv_usec < y->tv_usec) 
  {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }

  if ((x->tv_usec - y->tv_usec) > 1000000) 
  {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
     
  // compute the time remaining to wait, tv_usec is certainly positive.
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
     
  // return 1 if result is negative
  return x->tv_sec < y->tv_sec;
}
