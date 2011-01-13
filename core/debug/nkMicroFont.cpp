//------------------------------------------------------------------------------
// nkMicroFont.cpp
//------------------------------------------------------------------------------

#include <OpenGLES/ES2/gl.h>
#include <cstring>

#include "debug/nkMicroFont.h"
#include "render/shader/nkShaderDebugFont.h"

#include "io/nkTextureManager.h"

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

// vertex to use for debug font
typedef struct _vtxdf 
{
  vec2f position;
  vec2f uv;
} vtxdf;

// represents a single rendered line
typedef struct _line
{
  u32    size;
  vtxdf *triangles;
} line;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

static nkShaderDebugFont g_shader_debugfont;

static vtxdf g_triangles[4000];
static u32   g_tri_count = 0;

static line g_lines[100] = {0};
static u32  g_line_count = 0;

static vec2f g_cursor(-150.0f, 220.0f);

static u32 g_font_tex_id;
u32 nkDebug::getTexId()
{
  return g_font_tex_id;
}

//------------------------------------------------------------------------------

static u8 s_glyph_width  = 5;
static u8 s_glyph_height = 5;
static u8 s_glyph_rows   = 10;
static u8 s_glyph_cols   = 10;

static char s_debug_font_table[50][7] = {
   0x01,  0x14,  0xa7,  0xc4,  0xc4,  0x22,  0x00,  
   0x01,  0x15,  0xfa,  0x09,  0x04,  0x41,  0x00,  
   0x01,  0x00,  0xa7,  0x11,  0xa0,  0x41,  0x00,  
   0x00,  0x01,  0xf2,  0xa2,  0x40,  0x41,  0x00,  
   0x01,  0x00,  0xaf,  0x45,  0xa0,  0x22,  0x00,  
   0x21,  0x04,  0x00,  0x05,  0xc4,  0x73,  0x80,  
   0xa9,  0x08,  0x00,  0x0b,  0x2c,  0x8c,  0x40,  
   0x77,  0xc1,  0xf0,  0x12,  0xb4,  0x31,  0xc0,  
   0xa9,  0x00,  0x00,  0x22,  0x64,  0x44,  0x40,  
   0x21,  0x00,  0x02,  0x41,  0xdf,  0xfb,  0x80,  
   0x97,  0xff,  0xff,  0xfc,  0x00,  0x10,  0x00,  
   0x94,  0x21,  0x18,  0xc4,  0x82,  0x27,  0xc0,  
   0xff,  0xbe,  0x1f,  0xfc,  0x00,  0x40,  0x00,  
   0x10,  0x62,  0x18,  0x84,  0x82,  0x27,  0xc0,  
   0x17,  0xbe,  0x1f,  0x84,  0x04,  0x10,  0x00,  
   0x43,  0x98,  0x4f,  0x3b,  0xdf,  0xff,  0xc0,  
   0x24,  0x64,  0xa8,  0xc6,  0x30,  0x84,  0x00,  
   0x11,  0xab,  0x1f,  0x42,  0x3e,  0xf5,  0xc0,  
   0x20,  0x25,  0xf8,  0xc6,  0x30,  0x84,  0x40,  
   0x41,  0x11,  0x1f,  0x3b,  0xdf,  0x87,  0xc0,  
   0x8f,  0xff,  0x18,  0x46,  0x2e,  0xfb,  0x80,  
   0x89,  0x09,  0x28,  0x6f,  0x31,  0x8c,  0x40,  
   0xf9,  0x09,  0xc8,  0x56,  0xb1,  0xfd,  0x40,  
   0x89,  0x09,  0x28,  0x46,  0x71,  0x84,  0x80,  
   0x8f,  0xf9,  0x1f,  0xc6,  0x2e,  0x83,  0x40,  
   0xfb,  0xff,  0x18,  0xc6,  0x31,  0xfb,  0x80,  
   0x8c,  0x09,  0x18,  0xc5,  0x4a,  0x12,  0x00,  
   0xff,  0xc9,  0x18,  0xd4,  0x84,  0x22,  0x00,  
   0x90,  0x49,  0x15,  0x55,  0x44,  0x42,  0x00,  
   0x8f,  0x88,  0xe2,  0x2a,  0x24,  0xfb,  0x80,  
   0x83,  0x88,  0x02,  0x00,  0x00,  0x00,  0x00,  
   0x40,  0x94,  0x01,  0x11,  0x00,  0x10,  0x00,  
   0x20,  0xa2,  0x00,  0x09,  0xce,  0x73,  0x80,  
   0x10,  0x80,  0x00,  0x39,  0x48,  0x53,  0x00,  
   0x0b,  0x81,  0xf0,  0x39,  0xce,  0x71,  0x80,  
   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  
   0x33,  0x90,  0x42,  0x20,  0x80,  0x00,  0x00,  
   0x23,  0x9c,  0x00,  0x28,  0x9f,  0x73,  0x80,  
   0x70,  0x94,  0x42,  0x30,  0x95,  0x52,  0x80,  
   0x23,  0x94,  0x46,  0x28,  0x91,  0x53,  0x80,  
   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  
   0x73,  0x80,  0x02,  0x00,  0x00,  0x02,  0x80,  
   0x52,  0x9c,  0x67,  0x29,  0x51,  0x53,  0x80,  
   0x73,  0x90,  0x42,  0x29,  0x55,  0x20,  0x80,  
   0x40,  0x90,  0xc3,  0x38,  0x9f,  0x51,  0x00,  
   0x00,  0x88,  0x80,  0x00,  0x8a,  0xaf,  0xc0,  
   0x01,  0x08,  0x44,  0x01,  0x55,  0x57,  0xc0,  
   0x73,  0x08,  0x6a,  0x92,  0xaa,  0xaf,  0xc0,  
   0x21,  0x08,  0x41,  0x01,  0x55,  0x57,  0xc0,  
   0x70,  0x88,  0x80,  0x00,  0x8a,  0xaf,  0xc0,  
};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

void writeChar(char c, u8 *buffer, u32 stride, u8 value);
void createFontAtlas(u8 *buffer, u32 width, u32 height);

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------

void nkDebug::Initialize()
{
  g_shader_debugfont.loadProgram();

  const u32 width  = 64;
  const u32 height = 64;
  u8 font_buffer[height][width] = {0}; 
  createFontAtlas(&font_buffer[0][0], width, height);

  nkTexture *texture = TEXTURE::LoadBuffer(&font_buffer[0][0], Luminance, width, height); 
  g_font_tex_id = texture->m_id;
}

//------------------------------------------------------------------------------

void nkDebug::Render()
{
  // setup camera matrix
  mtx4f camera_matrix;
  LoadOrthographic(&camera_matrix, 320, 480, -1.0f, 1.0f);

  // setup shader program
  glUseProgram(g_shader_debugfont.getProgram());	

  // setup camera matrix
  g_shader_debugfont.setViewport((GLfloat*)(void*)&camera_matrix);

  u32 count = g_line_count;
  for (u32 index = 0; index < count; ++index)
  {
    line *l = &g_lines[index];

    f32 *buffer = (f32*)(void*)l->triangles;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    g_shader_debugfont.setTexture((GLint)g_font_tex_id);
    g_shader_debugfont.setVertices(2, GL_FALSE, sizeof(vtxdf), buffer);
    g_shader_debugfont.setUVs(2, GL_TRUE, sizeof(vtxdf), (GLfloat*)buffer + 2);

#if defined(DEBUG)
    if (!g_shader_debugfont.validateProgram())
    {
      return;
    }
#endif
	
    // draw
    glDrawArrays(GL_TRIANGLES, 0, l->size);
  }

  g_line_count = 0;
  g_tri_count = 0;
}

//------------------------------------------------------------------------------

void nkDebug::resetCursor()
{
  // 320, 480
  g_cursor.SetXY((-320.0f/2.0)+10.0, (480.0/2.0)-10.0f-6.0f);
}

void drawChar(const char c, vtxdf *verticies);

//------------------------------------------------------------------------------

void nkDebug::print(const char *message)
{
  line *l = &g_lines[g_line_count++];

  l->size      = 0;
  l->triangles = &g_triangles[g_tri_count];

  u32   *size  = &l->size;
  vtxdf *verts = l->triangles;

  u32 len = strlen(message);
  for (u32 i = 0; i < len; ++i)
  {
    drawChar(message[i], &verts[*size]);

    *size += 6;
  }

  // update tri count
  g_tri_count += *size;

  // update cursor
  g_cursor._y -= 6;
  g_cursor._x = -150;
}

//------------------------------------------------------------------------------
// triangle layout
//    2  3 _ 5    // -0.5f, -0.5f,  u,   v+s,  // bottom_left    0
//     |\ \ |     //  0.5f, -0.5f,  u+s, v+s,  // bottom_right   1|4
//     |_\ \|     // -0.5f,  0.5f,  u,   v,    // top_left       2|3
//    0   1  4    //  0.5f,  0.5f,  u+s, v,    // top_right      5
//------------------------------------------------------------------------------

void getGlyphCoords(const char c, u32 *x, u32 *y)
{
  u32 index = c - 32;
  *x = index % s_glyph_rows;
  *y = index / s_glyph_rows;
}

void drawChar(const char c, vtxdf *verticies)
{
  u32 gx, gy;
  getGlyphCoords(c, &gx, &gy);

  f32 s = 6.0f / 64.0f;
  f32 u = gx * s;
  f32 v = gy * s;

  vtxdf *bottom_left  = &verticies[0];
  vtxdf *bottom_right = &verticies[1];
  vtxdf *top_left     = &verticies[2];
  vtxdf *top_right    = &verticies[5];

  f32 xMin = g_cursor._x;
  f32 yMin = g_cursor._y;
  f32 xMax = xMin + 6.0f;
  f32 yMax = yMin + 6.0f;

  bottom_left ->position.SetXY(xMin, yMin);
  bottom_right->position.SetXY(xMax, yMin);
  top_left    ->position.SetXY(xMin, yMax);
  top_right   ->position.SetXY(xMax, yMax);

  f32 uMin = u;
  f32 vMin = v;
  f32 uMax = u + s;
  f32 vMax = v + s;

  bottom_left ->uv.SetXY(uMin, vMax);
  bottom_right->uv.SetXY(uMax, vMax);
  top_left    ->uv.SetXY(uMin, vMin);
  top_right   ->uv.SetXY(uMax, vMin);

  verticies[3] = *top_left;
  verticies[4] = *bottom_right;

  g_cursor.SetX(xMax);
}

//------------------------------------------------------------------------------
// helper functions
//------------------------------------------------------------------------------

void createFontAtlas(u8 *buffer, u32 width, u32 height)
{
  // write entire font set to buffer
  u32 x = 1;
  u32 y = 1;
  u32 char_width  = s_glyph_width + 1;
  u32 char_height = s_glyph_height + 1;
  for (u32 c = 32; c < 127; ++c, x += char_width) 
  {
    // if at end of buffer, go to next line
    if ((width - x) < char_width) 
    {
      x = 1;
      y += char_height;
    }

    // stop at end of buffer
    if ((height - y) < char_height) 
    {
      break;
    }

    // write char to buffer 
    writeChar(c, &buffer[(y * width) + x], width, 255);
  }
}

//------------------------------------------------------------------------------

void writeChar(char c, u8 *buffer, u32 stride, u8 value) 
{
  // only process printable characters
  if ((c > 32) && (c < 127)) 
  {
    // calculate glyph position in table
    u32 glyph_index = c - 32;
    u32 glyph_row   = glyph_index / s_glyph_rows;
    u32 glyph_col   = glyph_index % s_glyph_rows;

    // calculate table rows to use
    u32 row     = glyph_row * s_glyph_height;
    u32 row_end = row + s_glyph_height;
    for (; row < row_end; ++row, buffer += (stride - s_glyph_width))
    {
      // calculate bits to be read
      u32 col     = glyph_col * s_glyph_width;
      u32 col_end = col + s_glyph_width;
      for (; col < col_end; ++col, ++buffer)
      {
        u32 x      = col / 8;
        u32 bit    = col % 8;
        u32 is_set = s_debug_font_table[row][x] & (1 << (7 - bit));

        // update buffer if bit set
        if (is_set) 
        {
          *buffer = value;
        }
      }
    }
  }
}

