//
//  AppDelegate.m
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "AppDelegate.h"
#import "MenuEventsHandler.h"

@interface AppDelegate ()

@property (weak, nonatomic, nullable) IBOutlet MenuEventsHandler *menuHandler;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
