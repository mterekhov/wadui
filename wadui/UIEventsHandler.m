//
//  MainMenuHandler.m
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "UIEventsHandler.h"
#import <Cocoa/Cocoa.h>

@implementation UIEventsHandler

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

- (IBAction)showAll:(id)sender {
    if (!self.delegate) {
        return;
    }
    
    [self.delegate showAll];
}

- (IBAction)hideMaps:(id)sender {
    if (!self.delegate) {
        return;
    }
    
    [self.delegate hideMaps];
}

- (IBAction)showMarkersOnly:(id)sender {
    if (!self.delegate) {
        return;
    }
    
    [self.delegate showMarkersOnly];
}

- (IBAction)exportAsImage:(id)sender {
    if (self.delegate == nil) {
        return;
    }
    
    if (![self.delegate canExport]) {
        return;
    }
    NSOpenPanel* openDialog = [NSOpenPanel openPanel];
    openDialog.canChooseDirectories = YES;
    openDialog.canChooseFiles = NO;
    if ([openDialog runModal] == NSModalResponseOK) {
        if (!self.delegate) {
            return;
        }
        [self.delegate exportSelectedLumpsAsImage:openDialog.URLs.firstObject.path];
    }
}

- (IBAction)exportSelectedLumps:(id)sender {
    if (self.delegate == nil) {
        return;
    }
    
    if (![self.delegate canExport]) {
        return;
    }
    NSOpenPanel* openDialog = [NSOpenPanel openPanel];
    openDialog.canChooseDirectories = YES;
    openDialog.canChooseFiles = NO;
    if ([openDialog runModal] == NSModalResponseOK) {
        if (!self.delegate) {
            return;
        }
        [self.delegate exportSelectedLumps:openDialog.URLs.firstObject.path];
    }
}

@end
