//------------------------------------------------------------------------------
// nkGameplayManager.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "gameplay/nkGameplayManager.h"
#include "gameplay/nkMovableObjectBase.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// statics
//------------------------------------------------------------------------------

nkGameplayManager* nkGameplayManager::getInstance()
{
  static nkGameplayManager m_gameplay_manager;
  return &m_gameplay_manager;
}

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool nkGameplayManager::initialize()
{
  // init counter
  m_game_object_count = 0;

  return true;
}

//------------------------------------------------------------------------------

void nkGameplayManager::preUpdate(f32 time)
{
  u32 count = m_game_object_count;
  for (u32 index = 0; index < count; ++index) 
  {
    m_game_objects[index]->preUpdate(time);
  }
}

//------------------------------------------------------------------------------

void nkGameplayManager::update(f32 time)
{
  u32 count = m_game_object_count;
  for (u32 index = 0; index < count; ++index) 
  {
    m_game_objects[index]->update(time);
  }
}

//------------------------------------------------------------------------------

void nkGameplayManager::postUpdate(f32 time)
{
  u32 count = m_game_object_count;
  for (u32 index = 0; index < count; ++index) 
  {
    m_game_objects[index]->postUpdate(time);
  }
}

//------------------------------------------------------------------------------

void nkGameplayManager::deinitialize()
{
  
}

//------------------------------------------------------------------------------

void nkGameplayManager::submitObj(nkMovableObjectBase *obj)
{
  obj->initialize();

  m_game_objects[m_game_object_count++] = obj;
  NK_ASSERT(m_game_object_count < MAX_UPDATE_OBJECTS);
}

