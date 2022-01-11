//
//  LodService.m
//  wadui
//
//  Created by Michael Terekhov on 12.01.2022.
//  Copyright © 2022 Michael. All rights reserved.
//

#import "LodService.h"
#import "LodModel.h"
#include "alod.h"

@interface LodService ()

@property (nonatomic, assign, nullable) spcWAD::ALod *lodTools;
@property (nonatomic, strong, nullable) NSString *fileName;

@end

@implementation LodService

- (instancetype)initWithLodFileName: (NSString *)lodFileName {
    self = [super init];
    
    _lodTools = new spcWAD::ALod();
    _fileName = lodFileName;
    
    return self;
}

#pragma mark - LumpsServiceProtocol -

- (NSArray<LodModel *> *)lodItemsList {
    return [NSArray new];
}

- (void)exportLodItem:(LodModel *)model folderPath:(NSString *)folderPath {
    
}

- (void)exportLodAsImage:(LodModel *)model folderPath:(NSString *)folderPath {
    
}


@end
