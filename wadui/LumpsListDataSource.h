//
//  LumpsListDataSource.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@protocol LumpsServiceProtocol;

NS_ASSUME_NONNULL_BEGIN

@interface LumpsListDataSource : NSObject<NSTableViewDataSource, NSTableViewDelegate>

@property (nonatomic, strong, nullable) id<LumpsServiceProtocol> lumpsService;
@property (weak) IBOutlet NSTableView *lumpsListTableView;

@end

NS_ASSUME_NONNULL_END
