//-------------------------------------------------------------------------------
// nektarAppDelegate.h
//-------------------------------------------------------------------------------

#import <UIKit/UIKit.h>

//-------------------------------------------------------------------------------
// interface definition
//-------------------------------------------------------------------------------

@class EAGLView;

@interface nektarAppDelegate : NSObject <UIApplicationDelegate> {
  UIWindow *window;
  EAGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;

@end

