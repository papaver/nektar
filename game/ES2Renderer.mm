//------------------------------------------------------------------------------
// ES2Renderer.h
//------------------------------------------------------------------------------

#import "ES2Renderer.h"

#import "nektar/nektar.h"
#import "interface/nktouch.h"
#import "gameplay/nkGameplayManager.h"
#import "gameplay/nkTileManager.h"
#import "render/nkRenderManager.h"
#import "render/nkRenderUtils.h"
#import "render/nkSprite.h"
#import "utils/nk_iphone.h"
#import "io/nkFontManager.h"
#import "io/nkTextureManager.h"
#import "io/image/nkBitmap.h"
#import "debug/nkMicroFont.h"

//-------------------------------------------------------------------------------
// interface implementation
//-------------------------------------------------------------------------------

@implementation ES2Renderer

//-------------------------------------------------------------------------------

void initializeGame()
{
  // initialize systems 
  nkTime::Initialize();
  nkTouch::Initialize();
  nkFont::Initialize();
  TEXTURE::Initialize();
  nkRender::Initialize();

  nkDebug::Initialize();

  // seed random
  u32 sec, usec;
  nkTime::GetStartTime(&sec, &usec);
  Srand(usec);

  // initialize gameplay manager
  nkGameplayManager *gameplay_manager = nkGameplayManager::getInstance();
  gameplay_manager->initialize();

  // load textures
  char path[512];
  nkiPhone::getFilePath("Heart", "png", path, 512);
  u32 white_texture = 0xFFFFFFFF;
  nkTexture *texture = TEXTURE::LoadBuffer((u8*)&white_texture, RGBA_8888, 1, 1);
  //u32 tex_id = TEXTURE::LoadFile(path);
  
  // initialize tile manager
  nkTileManager *tile_manager = nkTileManager::getInstance();
  tile_manager->initialize(320.0f, 480.0f, 10.0f, texture->m_id);


  char path_bmp[512];
  nkiPhone::getFilePath("test_0008", "bmp", path_bmp, 512);
  u32 tex_id = doBitmap(path_bmp);

  nkSprite *sprite = new nkSprite();
  nkSprite::Initialize(sprite);
  sprite->m_texture_id = tex_id;
  
  // position and id
  sprite->m_position.SetXY(0.0f, 0.0f);
  sprite->m_rotation.SetScale(128.0, 64.0, 0.0);
  sprite->m_tint.SetXYZW(1.0f, 1.0f, 1.0f, 1.0f);
  
  // submit to managers
  nkRender::Submit(sprite);
}

//-------------------------------------------------------------------------------

- (id) init
{
  if (self = [super init])	
  {
    // Create an ES 2.0 context
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!context || ![EAGLContext setCurrentContext:context])
    {
      [self release];
      return nil;
    }

    initializeGame();

    // Create default framebuffer object. 
    // The backing will be allocated for the current layer in -resizeFromLayer
    glGenFramebuffers(1, &defaultFramebuffer);
    glGenRenderbuffers(1, &colorRenderbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
  }
	
  return self;
}

//-------------------------------------------------------------------------------

- (void) render
{
  // update timer 
  nkTime::Update();

  f32 step = nkTime::GetStep();

  nkTileManager *tile_manager = nkTileManager::getInstance();
  tile_manager->preUpdate(step);
  tile_manager->update(step);

  // update gameplay objects
  nkGameplayManager *gameplay_manager = nkGameplayManager::getInstance();
  gameplay_manager->preUpdate(step);
  gameplay_manager->update(step);
  gameplay_manager->postUpdate(step);

  // update touch
  nkTouch::Update();

  // print a message

  char fps[16];
  sprintf(fps, "FPS: %f", 1.0f / step);

  nkDebug::resetCursor();
  nkDebug::print(fps);













  // This application only creates a single context which is already set current at this point.
  // This call is redundant, but needed if dealing with multiple contexts.
  [EAGLContext setCurrentContext:context];
    
  // This application only creates a single default framebuffer which is already bound at this point.
  // This call is redundant, but needed if dealing with multiple framebuffers.
  glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);

  // this defines the bounds -1.0 to 1.0 in x and y
  // all matrix cacluations need to be done manually in the vertex shader
  glViewport(0, 0, backingWidth, backingHeight);

  // clear the buffer
  glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  // render the scene
  nkRender::Render();

  // render debug 
  nkDebug::Render();

  // This application only creates a single color renderbuffer which is already bound at this point.
  // This call is redundant, but needed if dealing with multiple renderbuffers.
  glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
  [context presentRenderbuffer:GL_RENDERBUFFER];
}

//-------------------------------------------------------------------------------

- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer
{
  // allocate color buffer backing based on the current layer size
  glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
  [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);

  // notify renderer
  nkRender::SetScreenSize(backingWidth, backingHeight);
	
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    return NO;
  }
	
  return YES;
}

//-------------------------------------------------------------------------------

- (void) dealloc
{
  // update gameplay objects
  nkGameplayManager *gameplay_manager = nkGameplayManager::getInstance();
  gameplay_manager->deinitialize();

  nkFont::Deinitialize();
  TEXTURE::Deinitialize();
  nkRender::Deinitialize();

  // Tear down GL
  if (defaultFramebuffer)
  {
    glDeleteFramebuffers(1, &defaultFramebuffer);
    defaultFramebuffer = 0;
  }

  if (colorRenderbuffer)
  {
    glDeleteRenderbuffers(1, &colorRenderbuffer);
    colorRenderbuffer = 0;
  }
		
  // Tear down context
  if ([EAGLContext currentContext] == context)
  {
    [EAGLContext setCurrentContext:nil];
  }
	
  [context release];
  context = nil;
	
  [super dealloc];
}

@end
