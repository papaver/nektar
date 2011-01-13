//------------------------------------------------------------------------------
// ES1Renderer.h
//------------------------------------------------------------------------------

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import "ESRenderer.h"

//-------------------------------------------------------------------------------
// interface definition
//-------------------------------------------------------------------------------

@interface ES1Renderer : NSObject <ESRenderer>
{

@private

  EAGLContext *context;
  
  // The pixel dimensions of the CAEAGLLayer
  GLint backingWidth;
  GLint backingHeight;
	
  // The OpenGL names for the framebuffer and renderbuffer used to render to this view
  GLuint defaultFramebuffer;
  GLuint colorRenderbuffer;
}

- (void) render;
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

@end
