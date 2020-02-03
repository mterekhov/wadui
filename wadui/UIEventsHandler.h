//
//  MainMenuHandler.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIEventsHandlerDelegate <NSObject>

- (void)exportSelectedLumps:(NSString *)path;
- (void)exportSelectedLumpsAsImage:(NSString *)path;
- (void)openFileResults:(NSArray<NSURL *> *)urls;
- (void)closeCurrentWad;
- (void)showMarkersOnly;
- (void)hideMaps;
- (void)showAll;
- (BOOL)canExport;
- (void)searchWithText:(NSString *)text;

@end

@interface UIEventsHandler : NSObject<NSSearchFieldDelegate>

@property (weak, nonatomic, nullable) IBOutlet id<UIEventsHandlerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
