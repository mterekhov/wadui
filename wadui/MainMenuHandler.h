//
//  MainMenuHandler.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MainMenuHandlerDelegate <NSObject>

- (void)openFileResults:(NSArray<NSURL *> *)urls;

@end

@interface MainMenuHandler : NSObject

@property (weak, nonatomic, nullable) IBOutlet id<MainMenuHandlerDelegate> delegate;

- (IBAction)openDocument:(id)sender;

@end

NS_ASSUME_NONNULL_END
