//------------------------------------------------------------------------------
// nkFontManager.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "io/nkFontManager.h"
#include "utils/nk_iphone.h"

// freetype includes
#include <ft2build.h>
#include FT_FREETYPE_H

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

typedef struct _nkFontPath {
  const u32   id;
  const char *name;
  const char *ext;
} nkFontPath;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

static nkFontPath g_font_paths[nkFont::FONT_COUNT] = {
  { nkFont::FONT_ARIAL,   "arial",           "ttf" },
  { nkFont::FONT_TIMES,   "times_new_roman", "ttf" },
  { nkFont::FONT_COURIER, "courier_new",     "ttf" },
  { nkFont::FONT_VERANDA, "veranda",         "ttf" }
};

static FT_Library g_font_library;
static FT_Face    g_font_faces[nkFont::FONT_COUNT] = {0};

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool nkFont::Initialize()
{
  FT_Error error;

  // load freetype library
  error = FT_Init_FreeType(&g_font_library);
  if (error) 
  {
    nk_error("FreeType library failed to initialize.");
    return false;
  }  

  // load faces
  u32 index = 0;
  for (; index < FONT_COUNT; ++index) 
  { 
    nkFontPath *font_path = &g_font_paths[index];
    NK_ASSERT(font_path->id == index);

    // get path to font
    char path[256];
    nkiPhone::getFilePath(font_path->name, font_path->ext, path, 256);

    // load font
    error = FT_New_Face(g_font_library, path, 0, &g_font_faces[index]); 
    if (error) 
    {
      g_font_faces[index] = NULL;
      nk_error("Failed to load font '%s'.", font_path->name);
      continue;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

void nkFont::Deinitialize()
{
  FT_Face font_face;

  // clean up the faces
  u32 index = 0; 
  for (index = 0; index < FONT_COUNT; ++index) 
  {
    font_face = g_font_faces[index];
    if (font_face) 
    {
      FT_Done_Face(font_face);
    }
  }

  // delete the library
  FT_Done_FreeType(g_font_library);
}

//------------------------------------------------------------------------------
// private interface
//------------------------------------------------------------------------------

void drawBitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y, u8 *buffer, u32 width, u32 height)
{
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;
  
  for (i = x, p = 0; i < x_max; i++, p++ )
  {
    for (j = y, q = 0; j < y_max; j++, q++ )
    {
      if ((i < 0) || (j < 0) || (i >= width) || (j >= height))
      {
        continue;
      }
      
      // need to work out how this will work still
      // buffer[j][i][1] |= bitmap->buffer[q * bitmap->width + p];
    }
  }
}

//------------------------------------------------------------------------------

void renderFont(nkFont::FontFace face_enum, const char *text, f32 angle, u32 height)
{
  FT_Face       face;
  FT_GlyphSlot  slot;
  FT_Matrix     matrix;                 
  FT_Vector     pen;                    
  FT_Error      error;
  
  int           n, num_chars;
  num_chars     = strlen(text);
  
  // 300dpi looks pretty good
  // the 0's just mean same as width/height
  face  = g_font_faces[(u32)face_enum];
  error = FT_Set_Char_Size(face, 20 * 64, 0, 300, 0);
  if (error)
  {
    nk_error("Failed to set font size.");
  }
                           
  slot = face->glyph;
  
  // setup matrix
  matrix.xx = (FT_Fixed)( Cosf(angle) * 0x10000L);
  matrix.xy = (FT_Fixed)(-Sinf(angle) * 0x10000L);
  matrix.yx = (FT_Fixed)( Sinf(angle) * 0x10000L);
  matrix.yy = (FT_Fixed)( Cosf(angle) * 0x10000L);
  
  // pen moves in 1/64 of an inch
  // the pen position in 26.6 cartesian space coordinates
  // start at (300,200) relative to the upper left corner 
  pen.x = 64 * 64;
  pen.y = 120 * 64; // (height - 120) * 64;
  
  for (n = 0; n < num_chars; n++)
  {
    // set the transform
    FT_Set_Transform(face, &matrix, &pen);
    
    // load glyph image into the slot (erase previous one)
    error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
    if (error)
    {
      nk_error("Failed to load glyph image.");
      continue;                 
    }
    
    /* work this out later...
    // now, draw to our target surface (convert position)
    draw_bitmap(&slot->bitmap,
                 slot->bitmap_left,
                 height - slot->bitmap_top);
    */
    
    // increment pen position 
    pen.x += slot->advance.x;
    pen.y += slot->advance.y;
  }
}


