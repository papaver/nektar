//------------------------------------------------------------------------------
// nkTile.h
//------------------------------------------------------------------------------

#ifndef _NKTILE_H_
#define _NKTILE_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"
#include "gameplay/nkMovableObjectBase.h"

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

struct nkTileManager;

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class nkTile : public nkMovableObjectBase
{

public:

  enum 
  {
    STATE_DEAD,
    STATE_ALIVE,
  };

public:

  nkTile();
  ~nkTile();

public:

  virtual bool initialize();
  virtual void preUpdate(f32 time);
  virtual void update(f32 time);
  virtual void postUpdate(f32 time);
  virtual void deinitialize();

public:

  nkTileManager *m_tile_manager;

  u16  m_x, m_y;
  u32  m_state;
  u32  m_life_count;
  f32  m_timer;
};

//------------------------------------------------------------------------------
// class implementation
//------------------------------------------------------------------------------

inline nkTile::nkTile()
{
}

//------------------------------------------------------------------------------

inline nkTile::~nkTile()
{
}

#endif // _NKTILE_H_

