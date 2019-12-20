//
//  LumpsService.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class LumpModel;

@protocol LumpsServiceProtocol <NSObject>

- (NSArray<LumpModel *> *)lumpsList;

@end

@interface LumpsService : NSObject<LumpsServiceProtocol>

- (instancetype)initWithWadFileName:(NSString *)wadFileName;
- (NSArray<LumpModel *> *)lumpsList;

@end

NS_ASSUME_NONNULL_END
