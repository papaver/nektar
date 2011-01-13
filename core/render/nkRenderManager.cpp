//------------------------------------------------------------------------------
// nkRenderManager.cpp
// For best performance, you should interleave the standard vertex attributes 
//  in the following order: Position, Normal, Color, TexCoord0, TexCoord1, 
//   PointSize, Weight, MatrixIndex.
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "render/nkRenderManager.h"
#include "render/nkSprite.h"
#include "render/shader/nkShaderSprite.h"
#include "render/nkRenderUtils.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define QUAD_SIZE   6
#define VERTEX_SIZE 2
#define UV_SIZE     2
#define TINT_SIZE   1

#define MAX_SPRITES 1600

#ifdef offsetof
  #undef offsetof
#endif
#define offsetof(c,m) ((size_t)&(((c*)1)->m)-1)

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

typedef struct _vtx 
{
  vec2f position;
  vec2f uv;
  u32   tint;
} vtx;

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------

f32             g_screen_width;
f32             g_screen_height;

nkShaderSprite  g_shader_sprite;
nkSprite       *g_sprites[MAX_SPRITES];
u32             g_sprite_count;

vtx             g_verticies[MAX_SPRITES * QUAD_SIZE];

//------------------------------------------------------------------------------
// forward declarations
//------------------------------------------------------------------------------

void renderSprites();

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool nkRender::Initialize()
{
  // initilize shaders
  bool result;
  result = g_shader_sprite.loadProgram();

  // initialize count
  g_sprite_count = 0;

  return result;
}

//------------------------------------------------------------------------------

void nkRender::Render()
{
  renderSprites();
}

//------------------------------------------------------------------------------

void nkRender::Deinitialize()
{
  // this should be in the resource manager?
   //glDeleteTextures(1, &m_texture_id);
}

//------------------------------------------------------------------------------

void nkRender::SetScreenSize(f32 width, f32 height)
{
  g_screen_width  = width;
  g_screen_height = height;
}

//------------------------------------------------------------------------------

void nkRender::Submit(nkSprite *sprite)
{
  g_sprites[g_sprite_count++] = sprite;
  NK_ASSERT(g_sprite_count < MAX_SPRITES);
}

//------------------------------------------------------------------------------
// private interface
//------------------------------------------------------------------------------

void renderSprites()
{
  // setup camera matrix
  mtx4f camera_matrix;
  LoadOrthographic(&camera_matrix, g_screen_width, g_screen_height, -1.0f, 1.0f);

  // setup shader program
  glUseProgram(g_shader_sprite.getProgram());	

  // setup camera matrix
  g_shader_sprite.setViewport((GLfloat*)(void*)&camera_matrix);

  i32 texture_id;

  // render all of the objects 
  u32 count = g_sprite_count;
  for (u32 index = 0; index < count; ++index) 
  {
    nkSprite *sprite = g_sprites[index];

    texture_id  = sprite->m_texture_id;
    vec4f *tint = &sprite->m_tint;

    mtx4f world_matrix;
    world_matrix        = sprite->m_rotation;
    world_matrix._v3    = sprite->m_position;
    world_matrix._v3._w = 1.0f;

    static vec4f unit_bottom_left (-0.5f, -0.5f, 0.0f, 1.0f);
    static vec4f unit_bottom_right( 0.5f, -0.5f, 0.0f, 1.0f);
    static vec4f unit_top_left    (-0.5f,  0.5f, 0.0f, 1.0f);
    static vec4f unit_top_right   ( 0.5f,  0.5f, 0.0f, 1.0f);

    vtx *bottom_left  = &g_verticies[index * QUAD_SIZE + 0];
    vtx *bottom_right = &g_verticies[index * QUAD_SIZE + 1];
    vtx *top_left     = &g_verticies[index * QUAD_SIZE + 2];
    vtx *top_right    = &g_verticies[index * QUAD_SIZE + 5];

    vec4f A, B, C, D;
    VecMulMat(&A, &world_matrix, &unit_bottom_left);
    VecMulMat(&B, &world_matrix, &unit_bottom_right);
    VecMulMat(&C, &world_matrix, &unit_top_left);
    VecMulMat(&D, &world_matrix, &unit_top_right);

    bottom_left->position.SetXY(&A);
    bottom_right->position.SetXY(&B);
    top_left->position.SetXY(&C);
    top_right->position.SetXY(&D);

    u8 red   = tint->_x * 255.0f;
    u8 green = tint->_y * 255.0f;
    u8 blue  = tint->_z * 255.0f;
    u8 alpha = tint->_w * 255.0f;

	  // pack all of the color data bytes into an unsigned int
	  u32 color = (alpha << 24) | (blue << 16) | (green << 8) | (red << 0);
    bottom_left->tint  = color;
    bottom_right->tint = color;
    top_left->tint     = color;
    top_right->tint    = color;

/*
    u32 x = (u32)(Randf() * 10.0f) % 10;
    u32 y = (u32)(Randf() * 10.0f) % 10;

    f32 s = 6.0f / 64.0f;
    f32 u = x * s;
    f32 v = y * s;

    f32 uMin = u;
    f32 vMin = v;
    f32 uMax = u + s;
    f32 vMax = v + s;

    bottom_left ->uv.SetXY(uMin, vMax);
    bottom_right->uv.SetXY(uMax, vMax);
    top_left    ->uv.SetXY(uMin, vMin);
    top_right   ->uv.SetXY(uMax, vMin);
*/
    bottom_left ->uv.SetXY(0.0f, 0.0f);
    bottom_right->uv.SetXY(1.0f, 0.0f);
    top_left    ->uv.SetXY(0.0f, 1.0f);
    top_right   ->uv.SetXY(1.0f, 1.0f);

    g_verticies[index * QUAD_SIZE + 3] = *top_left;
    g_verticies[index * QUAD_SIZE + 4] = *bottom_right;
  }

  GLvoid *position = (u8*)g_verticies + offsetof(vtx, position);
  GLvoid *uv       = (u8*)g_verticies + offsetof(vtx, uv);
  GLvoid *tint     = (u8*)g_verticies + offsetof(vtx, tint);

  g_shader_sprite.setTexture((GLint)texture_id);
  g_shader_sprite.setVertices(VERTEX_SIZE, GL_FALSE, sizeof(vtx), position);
  g_shader_sprite.setUVs(UV_SIZE, GL_TRUE, sizeof(vtx), uv);
  g_shader_sprite.setTint(TINT_SIZE, GL_TRUE, sizeof(vtx), tint);

#if defined(DEBUG)
    if (!g_shader_sprite.validateProgram())
    {
      return;
    }
#endif

  // draw
  glDrawArrays(GL_TRIANGLES, 0, QUAD_SIZE * count);
}


