//
//  MainMenuHandler.m
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "MainMenuHandler.h"
#import <Cocoa/Cocoa.h>

@implementation MainMenuHandler

- (IBAction)openDocument:(id)sender {
    NSOpenPanel* openDialog = [NSOpenPanel openPanel];
    if ([openDialog runModal] == NSModalResponseOK) {
        if (!self.delegate) {
            return;
        }
        [self.delegate openFileResults:openDialog.URLs];
    }
}

- (IBAction)performClose:(id)sender {
    if (!self.delegate) {
        return;
    }
    
    [self.delegate closeCurrentWad];
}

- (IBAction)hideMaps:(id)sender {
    
}

- (IBAction)showMarkersOnly:(id)sender {
    
}

- (IBAction)useHex:(id)sender {
    
}

- (IBAction)exportSelectedLumps:(id)sender {
    if (!self.delegate) {
        return;
    }
    
    [self.delegate exportSelectedLumps];
}

@end
