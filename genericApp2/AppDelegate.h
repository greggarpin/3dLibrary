//
//  AppDelegate.h
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    GLView* m_view;
}

@property (strong, nonatomic) UIWindow *window;


@end

