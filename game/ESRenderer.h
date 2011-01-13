//------------------------------------------------------------------------------
// ESRenderer.h
//------------------------------------------------------------------------------

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

//-------------------------------------------------------------------------------
// interface definition
//-------------------------------------------------------------------------------

@protocol ESRenderer <NSObject>

- (void) render;
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

@end
