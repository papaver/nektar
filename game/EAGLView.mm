//-------------------------------------------------------------------------------
// EAGLView.m
//-------------------------------------------------------------------------------

#import "EAGLView.h"
#import "ES1Renderer.h"
#import "ES2Renderer.h"

#import "math/nk_math.h"
#import "interface/nkTouch.h"

//-------------------------------------------------------------------------------
// interface definition
//-------------------------------------------------------------------------------

@interface EAGLView (PrivateMethods)
- (void) alertMsg:(NSString *)message title:(NSString *)title cancel:(NSString *)cancel;
@end

//-------------------------------------------------------------------------------
// interface implementation
//-------------------------------------------------------------------------------

@implementation EAGLView

@synthesize animating;
@dynamic animationFrameInterval;

//-------------------------------------------------------------------------------

// You must implement this method
+ (Class) layerClass
{
  return [CAEAGLLayer class];
}

//-------------------------------------------------------------------------------

// The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id) initWithCoder:(NSCoder*)coder
{    
  if ((self = [super initWithCoder:coder]))
  {
    // Get the layer
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
    eaglLayer.opaque = TRUE;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:FALSE], 
                                    kEAGLDrawablePropertyRetainedBacking, 
                                    kEAGLColorFormatRGBA8, 
                                    kEAGLDrawablePropertyColorFormat, 
                                    nil];
    
    renderer = [[ES2Renderer alloc] init];
    if (!renderer)
    {
      renderer = [[ES1Renderer alloc] init];
      if (!renderer)
      {
        [self release];
        return nil;
      }
    }
    
    self.multipleTouchEnabled = TRUE;
    
    animating              = FALSE;
    displayLinkSupported   = FALSE;
    animationFrameInterval = 1;
    displayLink            = nil;
    animationTimer         = nil;
    
    // A system version of 3.1 or greater is required to use CADisplayLink. 
    // The NSTimer class is used as fallback when it isn't available.
    NSString *reqSysVer = @"3.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
    {
      displayLinkSupported = TRUE;
    }
  }
  
  return self;
}

//-------------------------------------------------------------------------------

- (void) drawView:(id)sender
{
  [renderer render];
}

//-------------------------------------------------------------------------------

- (void) layoutSubviews
{
  [renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
  [self drawView:nil];
}

//-------------------------------------------------------------------------------

- (NSInteger) animationFrameInterval
{
  return animationFrameInterval;
}

//-------------------------------------------------------------------------------

- (void) setAnimationFrameInterval:(NSInteger)frameInterval
{
  // Frame interval defines how many display frames must pass between each time the
  // display link fires. The display link will only fire 30 times a second when the
  // frame internal is two on a display that refreshes 60 times a second. The default
  // frame interval setting of one will fire 60 times a second when the display refreshes
  // at 60 times a second. A frame interval setting of less than one results in undefined
  // behavior.
  if (frameInterval >= 1)
  {
    animationFrameInterval = frameInterval;
    
    if (animating)
    {
      [self stopAnimation];
      [self startAnimation];
    }
  }
}

//-------------------------------------------------------------------------------

- (void) startAnimation
{
  if (!animating)
  {
    NSTimeInterval interval = (NSTimeInterval)((1.0 / 60.0) * animationFrameInterval);
    animationTimer = [NSTimer scheduledTimerWithTimeInterval:interval
                                                      target:self 
                                                    selector:@selector
                                                   (drawView:) 
                                                    userInfo:nil 
                                                     repeats:TRUE];
    animating = TRUE;
  }
}

//-------------------------------------------------------------------------------

- (void) stopAnimation
{
  if (animating)
  {
    if (displayLinkSupported)
    {
      [displayLink invalidate];
      displayLink = nil;
    }
    else
    {
      [animationTimer invalidate];
      animationTimer = nil;
    }
    
    animating = FALSE;
  }
}

//-------------------------------------------------------------------------------

- (void) dealloc
{
  [renderer release];
  [super dealloc];
}

//-------------------------------------------------------------------------------
// view overrides
//-------------------------------------------------------------------------------

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
  return YES;
}

//-------------------------------------------------------------------------------
// application events
//-------------------------------------------------------------------------------

- (void) applicationDidFinishLaunching:(UIApplication *)application 
{
  //application.statusBarHidden      = YES;
  //application.statusBarOrientation = UIInterfaceOrientationPortrait;
}

//-------------------------------------------------------------------------------
// touch events
//-------------------------------------------------------------------------------

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
  [self handleTouches:touches withEvent:event];
}

//-------------------------------------------------------------------------------

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
  [self handleTouches:touches withEvent:event];
}

//-------------------------------------------------------------------------------

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
  [self handleTouches:touches withEvent:event];
}

//-------------------------------------------------------------------------------

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
  [self handleTouches:touches withEvent:event];
}

//-------------------------------------------------------------------------------

namespace nkTouch 
{
  void HandleTouch(u16 touch_id, u16 state, f32 x, f32 y);
}

- (void) handleTouches:(NSSet *)touches withEvent:(UIEvent *)event
{

  for (UITouch *touch in touches)
  {
    // get touch interface bounds
    CGRect bounds   = self.bounds;
    f32 half_width = bounds.size.width / 2.0;
    f32 half_height = bounds.size.height / 2.0;

    // get current touch position
    CGPoint position = [touch locationInView:self];

    // normalize position
    f32 x = position.x - half_width;
    f32 y = -position.y  + half_height;

    u32 touch_id = (u32)touch;
    u32 state    = touch.phase;
    nkTouch::HandleTouch(touch_id, state, x, y);
  }
}

//-------------------------------------------------------------------------------
// example code
//-------------------------------------------------------------------------------

- (void) alertMsg:(NSString *)message title:(NSString *)title cancel:(NSString *)cancel
{  
  UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title 
                                                  message:message 
                                                 delegate:nil 
                                        cancelButtonTitle:cancel
                                        otherButtonTitles:nil];
  [alert show];
  [alert release];  
}
@end
