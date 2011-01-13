//------------------------------------------------------------------------------
// nkTileManager.h
//------------------------------------------------------------------------------

#ifndef _NKTILEMANAGER_H_
#define _NKTILEMANAGER_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

class nkTile;
class nkSprite;

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class nkTileManager
{

enum
{
  STATE_START,
  STATE_MOVE_UP,
  STATE_MOVE_DOWN,
  STATE_END
};

public:

  static nkTileManager* getInstance();

public:

  void initialize(f32 width, f32 height, f32 size, u32 tex_id);
  void preUpdate(f32 time);
  void update(f32 time);
  void postUpdate(f32 time);
  void deinitialize();

public:

  nkTile* getTile(u32 x, u32 y);

  nkTile* North(nkTile *tile);
  nkTile* NorthEast(nkTile *tile);
  nkTile* East(nkTile *tile);
  nkTile* SouthEast(nkTile *tile);
  nkTile* South(nkTile *tile);
  nkTile* SouthWest(nkTile *tile);
  nkTile* West(nkTile *tile);
  nkTile* NorthWest(nkTile *tile);

private:

  nkTileManager();
  ~nkTileManager();

public:
  
  nkTile **m_tiles;
  u32      m_width;
  u32      m_height;

  nkSprite *m_sprite;

  u32 m_state;
  f32 m_timer;
  
};

//------------------------------------------------------------------------------
// class implementation
//------------------------------------------------------------------------------

inline nkTileManager::nkTileManager()
{
}

//------------------------------------------------------------------------------

inline nkTileManager::~nkTileManager()
{
}


#endif // _NKTILEMANAGER_H_
