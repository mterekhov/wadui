//
//  LumpsListDataSource.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@protocol LumpsServiceProtocol;
@protocol LodServiceProtocol;

NS_ASSUME_NONNULL_BEGIN

@interface LumpsListDataSource : NSObject<NSTableViewDataSource, NSTableViewDelegate>

@property (nonatomic, strong, nullable) id<LumpsServiceProtocol> lumpsService;
@property (nonatomic, strong, nullable) id<LodServiceProtocol> lodsService;
@property (weak) IBOutlet NSTableView *lumpsListTableView;

- (IBAction)lumpSelected:(id)sender;

@end

NS_ASSUME_NONNULL_END
