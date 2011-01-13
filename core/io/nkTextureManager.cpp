//------------------------------------------------------------------------------
// nkTextureManager.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "io/nkTextureManager.h"

#include <OpenGLES/ES2/gl.h>
#include "FreeImage.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define MAX_TEXTURE_SIZE 1028

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

nkTexture g_textures[MAX_TEXTURES] = {0};
u32       g_texture_count          = 0;
nkTexture *g_texture_default;

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

nkTexture* LoadFreeImage(const char* filepath);

//------------------------------------------------------------------------------
// OpenGL wrappers
//------------------------------------------------------------------------------

inline GLenum nkFormatToGL(nkTextureFormat nk_format)
{
  NK_ASSERT(nk_format);

	typedef struct _nk2gl {
    nkTextureFormat nk;
    GLenum          gl;
  } nk2gl;
 
  const u32 format_count = 10;
  static nk2gl s_format_lookup[format_count] = {
    { Auto,           0                  },
    { Alpha,          GL_ALPHA           },
    { RGB_565,        GL_RGB             },
    { RGB_888,        GL_RGB             },
    { RGBA_4444,      GL_RGBA            },
    { RGBA_5551,      GL_RGBA            },
    { RGBA_8888,      GL_RGBA            },
    { Luminance,      GL_LUMINANCE       },
    { LuminanceAlpha, GL_LUMINANCE_ALPHA },
    { DepthComponent, GL_DEPTH_COMPONENT },
  };

  nk2gl *lookup = &s_format_lookup[nk_format];
  NK_ASSERT(lookup->nk == nk_format);
  return lookup->gl;
}

inline GLenum nkFormatToGL(u32 nk_format)
{
  return nkFormatToGL((nkTextureFormat)nk_format);
}

//------------------------------------------------------------------------------

inline GLenum nkPixelTypeToGL(nkTextureFormat nk_format)
{
  NK_ASSERT(nk_format);

	typedef struct _nk2gl {
    nkTextureFormat nk;
    GLenum          gl;
  } nk2gl;
 
  const u32 format_count = 10;
  static nk2gl s_format_lookup[format_count] = {
    { Auto,           0                         },
    { Alpha,          GL_UNSIGNED_BYTE          },
    { RGB_565,        GL_UNSIGNED_SHORT_5_6_5   },
    { RGB_888,        GL_UNSIGNED_BYTE          },
    { RGBA_4444,      GL_UNSIGNED_SHORT_4_4_4_4 },
    { RGBA_5551,      GL_UNSIGNED_SHORT_5_5_5_1 },
    { RGBA_8888,      GL_UNSIGNED_BYTE          },
    { Luminance,      GL_UNSIGNED_BYTE          },
    { LuminanceAlpha, GL_UNSIGNED_BYTE          },
    { DepthComponent, GL_UNSIGNED_BYTE          },
  };

  nk2gl *lookup = &s_format_lookup[nk_format];
  NK_ASSERT(lookup->nk == nk_format);
  return lookup->gl;
}

inline GLenum nkPixelTypeToGL(u32 nk_format)
{
  return nkPixelTypeToGL((nkTextureFormat)nk_format);
}

//------------------------------------------------------------------------------

inline GLenum nkWrapModeToGL(nkTextureWrapMode nk_wrapmode)
{
	typedef struct _nk2gl {
    nkTextureWrapMode nk;
    GLenum            gl;
  } nk2gl;
 
  const u32 wrapmode_count = 3;
  static nk2gl s_wrapmode_lookup[wrapmode_count] = {
    { Repeat,         GL_REPEAT          },
    { Clamp,          GL_CLAMP_TO_EDGE   },
    { MirroredRepeat, GL_MIRRORED_REPEAT },
  };

  nk2gl *lookup = &s_wrapmode_lookup[nk_wrapmode];
  NK_ASSERT(lookup->nk == nk_wrapmode);
  return lookup->gl;
}

inline GLenum nkWrapModeToGL(u32 nk_wrapmode)
{
  return nkWrapModeToGL((nkTextureWrapMode)nk_wrapmode);
}

//------------------------------------------------------------------------------

inline GLenum nkMagFilterToGL(nkTextureMagFilter nk_magfilter)
{
	typedef struct _nk2gl {
    nkTextureMagFilter nk;
    GLenum             gl;
  } nk2gl;
 
  const u32 magfilter_count  = 2;
  static nk2gl s_magfilter_lookup[magfilter_count] = {
    { Nearest, GL_NEAREST },
    { Linear,  GL_LINEAR  },
  };

  nk2gl *lookup = &s_magfilter_lookup[nk_magfilter];
  NK_ASSERT(lookup->nk == nk_magfilter);
  return lookup->gl;
}

inline GLenum nkMagFilterToGL(u32 nk_magfilter)
{
  return nkMagFilterToGL((nkTextureMagFilter)nk_magfilter);
}

//------------------------------------------------------------------------------

inline GLenum nkMinFilterToGL(nkTextureMinFilter nk_minfilter)
{
	typedef struct _nk2gl {
    nkTextureMinFilter nk;
    GLenum             gl;
  } nk2gl;
 
  const u32 minfilter_count = 6;
  static nk2gl s_minfilter_lookup[minfilter_count] = {
    { NearestMipMapOff,     GL_NEAREST                },
    { NearestMipMapNearest, GL_NEAREST_MIPMAP_NEAREST },
    { NearestMipMapLinear,  GL_NEAREST_MIPMAP_LINEAR  },
    { LinearMipMapOff,      GL_LINEAR                 },
    { LinearMipMapNearest,  GL_LINEAR_MIPMAP_NEAREST  },
    { LinearMipMapLinear,   GL_LINEAR_MIPMAP_LINEAR   },
  };

  nk2gl *lookup = &s_minfilter_lookup[nk_minfilter];
  NK_ASSERT(lookup->nk == nk_minfilter);
  return lookup->gl;
}

inline GLenum nkMinFilterToGL(u32 nk_minfilter)
{
  return nkMinFilterToGL((nkTextureMinFilter)nk_minfilter);
}

//------------------------------------------------------------------------------

void nkTextureSubmitGL(nkTexture *texture, const u8 *bytes)
{
  // use tightly packed data
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  // generate a texture object
  glGenTextures(1, &texture->m_id);
  
  // bind the texture object
  glBindTexture(GL_TEXTURE_2D, texture->m_id);
  
  // get texture modes
  GLenum magfilter = nkMagFilterToGL(texture->m_magfilter);
  GLenum minfilter = nkMinFilterToGL(texture->m_minfilter);
  GLenum wrap_s    = nkWrapModeToGL(texture->m_wrap_s);
  GLenum wrap_t    = nkWrapModeToGL(texture->m_wrap_t);
  
  // more efficient to set before submiting buffer
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magfilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minfilter);  

  // load the texture
  GLenum format     = nkFormatToGL(texture->m_format);
  GLenum pixel_type = nkPixelTypeToGL(texture->m_format);
  GLuint width      = texture->m_width;
  GLuint height     = texture->m_height;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pixel_type, bytes);
}

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

enum nkTextureState 
{
  nkTextureStateDeleted = 0,
  nkTextureStateLoaded,
  nkTextureStateActive,
  nkTextureStateInActive,
};

nkTexture* nkTextureAllocate()
{
  // [moiz] not sure how this is going to work yet
  // right now we can only allocate
 
  nkTexture *texture = &g_textures[g_texture_count++];
  NK_ASSERT(g_texture_count < MAX_TEXTURES);
  return texture;
}

void nkTextureFree()
{

}

void nkTextureLoadDefault()
{
  typedef u32 rgba;

  union {
    rgba _rgba;
    u8   _c[4];
  };

  const rgba white = 0xFFFFFFFF;
  const rgba black = 0x000000FF;

  // allocate scratch buffer
  const u32 width  = 16;
  const u32 height = 16;
  rgba *buffer = (rgba*)nk_malloc(width * height * sizeof(rgba));

  // create 2x2 checkerboard
  bool is_white;
  for (u32 y = 0; y < height; ++y)
  {
    for (u32 x = 0; x < width; ++x)
    {
      is_white = (x < 8) ^ (y < 8);
      buffer[(y * width) + x] = SelectIfZero(!is_white, white, black);
    }
  }

  // allocate texture slot and submit to gl
  nkTexture *texture = nkTextureAllocate();
  NK_ASSERT(texture);
  texture->m_format    = RGBA_8888;
  texture->m_width     = width;
  texture->m_height    = height;
  texture->m_wrap_s    = Repeat;
  texture->m_wrap_t    = Repeat;
  texture->m_magfilter = Nearest;
  texture->m_minfilter = NearestMipMapOff;

  // [moiz] fix this casting crap
  nkTextureSubmitGL(texture, (const u8*)(void*)buffer);

  // save reference
  g_texture_default = texture;

  // delete scratch memory
  nk_free(buffer);
}

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool TEXTURE::Initialize()
{
  // initialise free image library
  FreeImage_Initialise();

  // load default checkerboard texture
  nkTextureLoadDefault();

  return true;
}

//------------------------------------------------------------------------------

void TEXTURE::Deinitialize()
{
  // delete all textures
  //glDeleteTextures(g_texture_count, g_textures);

  // deinitialise free image library
  FreeImage_DeInitialise();
}

//------------------------------------------------------------------------------

nkTexture* TEXTURE::LoadFile(const char* filepath)
{
  return LoadFreeImage(filepath);
}

//------------------------------------------------------------------------------

nkTexture* TEXTURE::LoadBuffer(const u8* buffer, nkTextureFormat format, u32 width, u32 height)
{
  nkTexture *texture = nkTextureAllocate();
  if (!texture)
  {
    return g_texture_default;
  }

  texture->m_format    = format;
  texture->m_width     = width;
  texture->m_height    = height;
  texture->m_wrap_s    = Repeat;
  texture->m_wrap_t    = Repeat;
  texture->m_magfilter = Nearest;
  texture->m_minfilter = NearestMipMapOff;
  nkTextureSubmitGL(texture, buffer);

  return texture;
}

//------------------------------------------------------------------------------

nkTexture* LoadFreeImage(const char* filepath)
{
  FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
  FIBITMAP *bitmap;
  BYTE* bits;
  u32 width;
  u32 height;

  // check the file signature and deduce its format
  image_format = FreeImage_GetFileType(filepath, 0);

  // if still unknown, try to guess the file format from the file extension
  if (image_format == FIF_UNKNOWN) 
  {
    image_format = FreeImage_GetFIFFromFilename(filepath);
  }

  // if still unkown, return failure
  if (image_format == FIF_UNKNOWN)
  {
    return g_texture_default;
  }

  // check that the plugin has reading capabilities and load the file
  if (FreeImage_FIFSupportsReading(image_format))
  {
    bitmap = FreeImage_Load(image_format, filepath);
  }

  // if the image failed to load, return failure
  if (!bitmap)
  {
    return g_texture_default;
  }

  // retrieve the image data
  bits = FreeImage_GetBits(bitmap);

  // get the image width and height
  width = FreeImage_GetWidth(bitmap);
  height = FreeImage_GetHeight(bitmap);
 
  // if this somehow one of these failed (they shouldn't), return failure
  if ((bits == 0) || (width == 0) || (height == 0))
  {
    return false;
  }

  // get image format
  nkTextureFormat color_format = RGB_888;
  u32 color_type = FreeImage_GetColorType(bitmap);
  if (color_type == FIC_RGBALPHA) 
  {
    color_format = RGBA_8888;
  }
  
  // texture object handle
  nkTexture *texture;
  texture = TEXTURE::LoadBuffer(bits, color_format, width, height);

  // free FreeImage's copy of the data
  FreeImage_Unload(bitmap);

  return texture;
}

//------------------------------------------------------------------------------
// private interface
//------------------------------------------------------------------------------

