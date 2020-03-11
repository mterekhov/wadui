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

- (NSArray<LumpModel *> *)lumpsListWithFilterString:(NSString *)filterString;
- (NSArray<LumpModel *> *)lumpsList;
- (NSArray<LumpModel *> *)lumpsListWithoutMaps;
- (NSArray<LumpModel *> *)lumpsListWithMarkersOnly;
- (void)exportLump:(LumpModel *)model folderPath:(NSString *)folderPath;
- (void)exportLumpAsImage:(LumpModel *)model folderPath:(NSString *)folderPath;

@end

@interface LumpsService : NSObject<LumpsServiceProtocol>

- (instancetype)initWithWadFileName:(NSString *)wadFileName;

@end

NS_ASSUME_NONNULL_END
