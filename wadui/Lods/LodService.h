//
//  LodService.h
//  wadui
//
//  Created by Michael Terekhov on 12.01.2022.
//  Copyright © 2022 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LodModel;
@protocol ModelsServiceProtocol;

@protocol LodServiceProtocol <NSObject>

//- (NSArray<LodModel *> *)lodItemsList;
//- (void)exportLodItem:(LodModel *)model folderPath:(NSString *)folderPath;
//- (void)exportLodAsImage:(LodModel *)model folderPath:(NSString *)folderPath;

@end

@interface LodService : NSObject<LodServiceProtocol, ModelsServiceProtocol>

- (instancetype)initWithLodFileName: (NSString *)lodFileName;

@end
