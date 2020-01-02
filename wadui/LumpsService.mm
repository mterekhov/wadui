//
//  LumpsService.m
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "LumpsService.h"
#import "LumpModel.h"
#include "awad.h"

@interface LumpsService ()

@property (nonatomic, assign, nullable) spcWAD::AWAD *wadTools;

@end

@implementation LumpsService

- (instancetype)initWithWadFileName:(NSString *)wadFileName {
    self = [super init];
    
    _wadTools = new spcWAD::AWAD(wadFileName.UTF8String);
    
    return self;
}

- (void)exportLump:(LumpModel *)model folderPath:(NSString *)folderPath {
    spcWAD::ALump exportLump(model.size, model.offset, model.name.UTF8String);
    self.wadTools->exportLump(exportLump, folderPath.UTF8String);
}

#pragma mark - LumpsServiceProtocol -

- (NSArray<LumpModel *> *)lumpsListWithoutMaps {
    NSMutableArray<LumpModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    std::list<std::string> mapLumps = self.wadTools->mapLumpsNames();
    spcWAD::TLumpsList lowLevelLumpsList = self.wadTools->lumpsList();
    for (spcWAD::TLumpsListConstIter iter = lowLevelLumpsList.begin(); iter != lowLevelLumpsList.end(); iter++) {
        if (std::find(mapLumps.begin(), mapLumps.end(), iter->lumpName) != mapLumps.end())
        {
            continue;
        }

        LumpModel *newModel = [LumpModel new];
        
        newModel.name = [NSString stringWithUTF8String:iter->lumpName.c_str()];
        newModel.offset = iter->lumpOffset;
        newModel.size = iter->lumpSize;
        newModel.about = @"about";
        
        [lumpsList addObject:newModel];
    }
    
    return [lumpsList copy];
}

- (NSArray<LumpModel *> *)lumpsListWithMarkersOnly {
    NSMutableArray<LumpModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    spcWAD::TLumpsList lowLevelLumpsList = self.wadTools->lumpsList();
    for (spcWAD::TLumpsListConstIter iter = lowLevelLumpsList.begin(); iter != lowLevelLumpsList.end(); iter++) {
        if (iter->lumpSize != 0) {
            continue;
        }
        
        LumpModel *newModel = [LumpModel new];
        
        newModel.name = [NSString stringWithUTF8String:iter->lumpName.c_str()];
        newModel.offset = iter->lumpOffset;
        newModel.size = iter->lumpSize;
        newModel.about = @"about";
        
        [lumpsList addObject:newModel];
    }
    
    return [lumpsList copy];
}

- (NSArray<LumpModel *> *)lumpsList {
    NSMutableArray<LumpModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    spcWAD::TLumpsList lowLevelLumpsList = self.wadTools->lumpsList();
    for (spcWAD::TLumpsListConstIter iter = lowLevelLumpsList.begin(); iter != lowLevelLumpsList.end(); iter++) {
        LumpModel *newModel = [LumpModel new];
        
        newModel.name = [NSString stringWithUTF8String:iter->lumpName.c_str()];
        newModel.offset = iter->lumpOffset;
        newModel.size = iter->lumpSize;
        newModel.about = @"about";
        
        [lumpsList addObject:newModel];
    }

    return [lumpsList copy];
}

@end
