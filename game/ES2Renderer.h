//------------------------------------------------------------------------------
// ES2Renderer.h
//------------------------------------------------------------------------------

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "ESRenderer.h"

//-------------------------------------------------------------------------------
// interface definition
//-------------------------------------------------------------------------------

@interface ES2Renderer : NSObject <ESRenderer>
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
