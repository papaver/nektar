//-------------------------------------------------------------------------------
// nektarAppDelegate.m
//-------------------------------------------------------------------------------

#import "nektarAppDelegate.h"
#import "EAGLView.h"

//-------------------------------------------------------------------------------
// interface implementation
//-------------------------------------------------------------------------------

@implementation nektarAppDelegate

@synthesize window;
@synthesize glView;

//-------------------------------------------------------------------------------

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
  //application.statusBarHidden      = YES;
  //application.statusBarOrientation = UIInterfaceOrientationLandscapeLeft;
  [application setStatusBarHidden:YES animated:NO];
  [glView startAnimation];
}

//-------------------------------------------------------------------------------

- (void) applicationWillResignActive:(UIApplication *)application
{
  [glView stopAnimation];
}

//-------------------------------------------------------------------------------

- (void) applicationDidBecomeActive:(UIApplication *)application
{
  [application setStatusBarHidden:YES animated:NO];
  [glView startAnimation];
}

//-------------------------------------------------------------------------------

- (void)applicationWillTerminate:(UIApplication *)application
{
  [glView stopAnimation];
}

//-------------------------------------------------------------------------------

- (void) dealloc
{
  [window release];
  [glView release];
	
  [super dealloc];
}

@end
