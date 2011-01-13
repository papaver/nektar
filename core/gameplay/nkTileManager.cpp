//------------------------------------------------------------------------------
// nkTileManager.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "gameplay/nkTileManager.h"
#include "gameplay/nkGameplayManager.h"
#include "gameplay/nkTile.h"
#include "render/nkRenderManager.h"
#include "render/nkSprite.h"
#include "interface/nkTouch.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// statics
//------------------------------------------------------------------------------

nkTileManager* nkTileManager::getInstance()
{
  static nkTileManager m_tile_manager;
  return &m_tile_manager;
}

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

void nkTileManager::initialize(f32 width, f32 height, f32 size, u32 tex_id)
{
  // calculate tiling 
  f32 tile_width  = Floorf(width / size);
  f32 tile_height = Floorf(height / size);

  // start on top left of grid 
  f32 x = (-width + size) / 2.0f;
  f32 y = (height - size) / 2.0f;
  vec4f position(x, y);

  // save size
  m_width  = tile_width;
  m_height = tile_height;

  // allocate tile grid
  m_tiles = (nkTile**)nk_malloc(m_width * m_height * sizeof(nkTile*));

  // create the tileset
  nkTile **tile = m_tiles;
  for (u32 h = 0; h < m_height; ++h, position._x = x, position._y -= size)
  {
    for (u32 w = 0; w < m_width; ++w, position._x += size, ++tile)
    {
      // create object
      *tile = new nkTile();
      nkSprite::Initialize(*tile);
      (*tile)->m_texture_id = tex_id;

      // position and id
      (*tile)->m_tile_manager = this;
      (*tile)->m_position.SetXY(&position);
      (*tile)->m_rotation.SetScale(size * 0.9);
      (*tile)->m_x = w;
      (*tile)->m_y = h;
      
      // submit to managers
      nkGameplayManager *gameplay_manager = nkGameplayManager::getInstance();
      gameplay_manager->submitObj(*tile);
      nkRender::Submit(*tile);
    }
  }

  // temp
  m_sprite = new nkSprite();
  //Sprite::Initialize(m_sprite);
  //m_sprite->m_position.SetXY(0.0f, -480.0f);
  //m_sprite->m_rotation.SetScale(320.0f/2.0f-10.0f, 480.0f/2.0-10.0f, 1.0f);
  //m_sprite->m_tint.SetW(0.6f);
  //RENDER::Submit(m_sprite);
}

//------------------------------------------------------------------------------

void nkTileManager::preUpdate(f32 time)
{
  for (u32 h = 0; h < m_height; ++h)
  {
    for (u32 w = 0; w < m_width; ++w)
    {
      m_tiles[h * m_width + w]->preUpdate(time);
    }
  }
}

//------------------------------------------------------------------------------

void nkTileManager::update(f32 time)
{
  for (u32 h = 0; h < m_height; ++h)
  {
    for (u32 w = 0; w < m_width; ++w)
    {
      m_tiles[h * m_width + w]->update(time);
    }
  }
}

//------------------------------------------------------------------------------

void nkTileManager::postUpdate(f32 time)
{
  for (u32 h = 0; h < m_height; ++h)
  {
    for (u32 w = 0; w < m_width; ++w)
    {
      m_tiles[h * m_width + w]->postUpdate(time);
    }
  }
}

//------------------------------------------------------------------------------

void nkTileManager::deinitialize()
{
  
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::getTile(u32 x, u32 y)
{
  NK_ASSERT(m_tiles);
 
  nkTile* tile = NULL;
  /*
  f32 is_valid = (x >= 0) && (x < m_width) && (y >= 0) && (y < m_height);
  tile = is_valid ? *(m_tiles + (y * m_width) + x) : NULL;
  */
  
  // wrap coordinates
  y    = (y + m_height) % m_height;
  x    = (x + m_width) % m_width;
  tile = *(m_tiles + (y * m_width) + x);
  
  return tile;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::North(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x, tile->m_y - 1);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::NorthEast(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x + 1, tile->m_y - 1);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::East(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x + 1, tile->m_y);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::SouthEast(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x + 1, tile->m_y + 1);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::South(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x, tile->m_y + 1);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::SouthWest(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x - 1, tile->m_y + 1);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::West(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x - 1, tile->m_y);
  return sibling;
}

//------------------------------------------------------------------------------

nkTile* nkTileManager::NorthWest(nkTile *tile)
{
  nkTile *sibling = getTile(tile->m_x - 1, tile->m_y - 1);
  return sibling;
}


