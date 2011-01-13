//------------------------------------------------------------------------------
// nkTexureManager.h
//------------------------------------------------------------------------------

#ifndef _NKTEXTUREMANAGER_H_
#define _NKTEXTUREMANAGER_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include "math/nk_math.h"

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

enum nkTextureFormat
{
	Auto = 0,
	Alpha,
	RGB_565,
	RGB_888,
	RGBA_4444,
	RGBA_5551,
	RGBA_8888,
	Luminance,
	LuminanceAlpha,
  DepthComponent,
};

enum nkTextureWrapMode 
{
  Repeat,
  Clamp,
  MirroredRepeat,
};

enum nkTextureMagFilter 
{
  Nearest,
  Linear,
};

enum nkTextureMinFilter 
{
  NearestMipMapOff,
  NearestMipMapNearest,
  NearestMipMapLinear,
  LinearMipMapOff,
  LinearMipMapNearest,
  LinearMipMapLinear,
};

typedef struct _nkTextureHandle 
{
  u32 m_handle;
} nkTextureHandle;

typedef struct _nkTexture 
{
  u32 m_id;
  u16 m_width;
  u16 m_height;
  u16 m_src_width;
  u16 m_src_height;

  u8  m_state;
  u8  m_format;
  u8  m_wrap_s;
  u8  m_wrap_t;
  u8  m_magfilter;
  u8  m_minfilter;

  u16 m_pad;
} nkTexture;

typedef struct _nkTextureAtlas
{
  nkTexture *m_texture;

  u16 m_rows;
  u16 m_cols;
  u16 m_row_width;
  u16 m_col_height;
  u16 m_offset_x;
  u16 m_offset_y;
  u16 m_spacing;
  u16 m_pad;

} nkTextureAtlas;

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

namespace TEXTURE
{

  bool Initialize();
  void Deinitialize();

  nkTexture* LoadFile(const char *filepath);
  nkTexture* LoadBuffer(const u8* buffer, nkTextureFormat format, u32 width, u32 height);

};

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

#endif // _NKTEXTUREMANAGER_H_
