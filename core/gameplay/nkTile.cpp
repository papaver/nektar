//------------------------------------------------------------------------------
// nkTile.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "gameplay/nkTile.h"
#include "gameplay/nkTileManager.h"
#include "interface/nkTouch.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define ONE_RAD 57.295779513082
#define ONE_DEG 0.0174532925199

//------------------------------------------------------------------------------
// statics
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool nkTile::initialize()
{
  m_state      = STATE_DEAD;
  m_life_count = 0;

  m_tint._x = 0.05f;
  m_tint._y = 0.05f;
  m_tint._z = 0.05f;

  m_timer   = 0.1f;

  return true;
}

//------------------------------------------------------------------------------

void nkTile::preUpdate(f32 time)
{
  nkTile *sibling;

  m_life_count  = 0;
  m_life_count += !!(sibling = m_tile_manager->North(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->NorthEast(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->East(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->SouthEast(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->South(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->SouthWest(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->West(this)) && (sibling->m_state == STATE_ALIVE);
  m_life_count += !!(sibling = m_tile_manager->NorthWest(this)) && (sibling->m_state == STATE_ALIVE);
}

//------------------------------------------------------------------------------

void nkTile::update(f32 time)
{
  //if (!TIME::DecTimer(&m_timer))
  //{
    //return;
  //}

  m_timer = 0.5f;

  switch (m_state)
  {
    case STATE_DEAD:
    {
      if (m_life_count == 3)   
      {
        m_tint._y = 0.05f;
        m_tint._x = 0.15f * 3;
        m_state = STATE_ALIVE;
      }

      break;
    };

    case STATE_ALIVE:
    {
      m_tint._y = 0.05f;
      m_tint._x = 0.15f * m_life_count;

      if ((m_life_count != 2) && (m_life_count != 3))
      {
        m_tint._x = 0.05f;
        m_tint._y = 0.05f;
        m_tint._z = 0.05f;
        m_state = STATE_DEAD;
      }

      break;
    }
  }
}

//------------------------------------------------------------------------------

void nkTile::postUpdate(f32 time)
{
  vec2f pos;
  pos._x = m_position._x;
  pos._y = m_position._y;

  // [moiz] quick fix to get compiled (ugly casting)
  bool touched = nkTouch::HitTestAny(&pos, 35.0f);
  if (touched && !(Rand() % 4)) 
  {
    m_state = STATE_ALIVE;
  }
}

//------------------------------------------------------------------------------

void nkTile::deinitialize()
{
}

