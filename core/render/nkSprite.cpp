//------------------------------------------------------------------------------
// nkSprite.cpp
//------------------------------------------------------------------------------

#include "render/nkSprite.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

void nkSprite::Initialize(nkSprite *sprite)
{
  VecZero3(&sprite->m_position);
  LoadIdentity(&sprite->m_rotation);
  sprite->m_tint.SetXYZW(1.0f, 1.0f, 1.0f, 1.0f);
}


