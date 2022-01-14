//
//  LodService.m
//  wadui
//
//  Created by Michael Terekhov on 12.01.2022.
//  Copyright © 2022 Michael. All rights reserved.
//

#import "LodService.h"
#import "ModelsServiceProtocol.h"
#import "CellModel.h"
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

#pragma mark - ModelsServiceProtocol -

- (NSArray<CellModel *> *)modelsList {
    NSMutableArray<CellModel *> *cellsModelsList = [NSMutableArray new];
    
    std::list<spcWAD::ALodItem> lodItemsList = self.lodTools->extractItems(self.fileName.UTF8String);
    for (std::list<spcWAD::ALodItem>::iterator iter = lodItemsList.begin(); iter != lodItemsList.end(); iter++) {
        [cellsModelsList addObject: [self createCellModelWithLodItem: *iter]];
    }
    
    return [cellsModelsList copy];
}

- (CellModel *)createCellModelWithLodItem: (spcWAD::ALodItem) lodItem {
    CellModel *newModel = [CellModel new];
    
    newModel.name = [NSString stringWithUTF8String: lodItem.name.c_str()];
    newModel.offset = lodItem.offset;
    newModel.size = lodItem.size;

    return newModel;
}

- (NSArray<CellModel *> *)modelsListWithFilterString:(NSString *)filterString {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    return [lumpsList copy];
}

- (NSArray<CellModel *> *)modelsListWithoutMaps {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    return [lumpsList copy];
}

- (NSArray<CellModel *> *)modelsListWithMarkersOnly {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    return [lumpsList copy];
}

- (void)exportModel:(CellModel *)model folderPath:(NSString *)folderPath {
}

- (void)exportModelAsImage:(CellModel *)model folderPath:(NSString *)folderPath {
}

@end
