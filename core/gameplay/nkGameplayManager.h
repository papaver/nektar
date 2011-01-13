//------------------------------------------------------------------------------
// nkGameplayManager.h
//------------------------------------------------------------------------------

#ifndef _NKGAMEPLAYMANAGER_H_
#define _NKGAMEPLAYMANAGER_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define MAX_UPDATE_OBJECTS 1600

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

class nkMovableObjectBase;

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

class nkGameplayManager
{

public:

  static nkGameplayManager* getInstance();

public:

  bool initialize();
  void preUpdate(f32 time);
  void update(f32 time);
  void postUpdate(f32 time);
  void deinitialize();

  void submitObj(nkMovableObjectBase *obj);

private:

  nkGameplayManager();
  ~nkGameplayManager();

public:
  
  nkMovableObjectBase *m_game_objects[MAX_UPDATE_OBJECTS];
  u32                  m_game_object_count;
  
};

//------------------------------------------------------------------------------
// class implementation
//------------------------------------------------------------------------------

inline nkGameplayManager::nkGameplayManager()
{
}

//------------------------------------------------------------------------------

inline nkGameplayManager::~nkGameplayManager()
{
}

#endif // _NKGAMEPLAYMANAGER_H_
