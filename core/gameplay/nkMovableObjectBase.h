//------------------------------------------------------------------------------
// nkMovableObjectBase.h
//------------------------------------------------------------------------------

#ifndef _NKMOVABLEOBJECTBASE_H_
#define _NKMOVABLEOBJECTBASE_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"
#include "render/nkSprite.h"

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class nkMovableObjectBase : public nkSprite
{

public:

  nkMovableObjectBase();
  ~nkMovableObjectBase();

public:

  virtual bool initialize();
  virtual void preUpdate(f32 time);
  virtual void update(f32 time);
  virtual void postUpdate(f32 time);
  virtual void deinitialize();

private:

};

//------------------------------------------------------------------------------
// class implementation
//------------------------------------------------------------------------------

inline nkMovableObjectBase::nkMovableObjectBase()
{
}

//------------------------------------------------------------------------------

inline nkMovableObjectBase::~nkMovableObjectBase()
{
}

#endif // _NKMOVABLEOBJECTBASE_H_

