//
//  LumpsService.m
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "LumpsService.h"
#import "CellModel.h"
#include "awad.h"
#include "alumptools.h"
#include "autilities.h"

@interface LumpsService ()

@property (nonatomic, assign, nullable) spcWAD::AWAD *wadTools;

@end

@implementation LumpsService

- (instancetype)initWithWadFileName: (NSString *)wadFileName {
    self = [super init];
    
    _wadTools = new spcWAD::AWAD(wadFileName.UTF8String);
    
    return self;
}

#pragma mark - ModelsServiceProtocol -

- (NSArray<CellModel *> *)modelsList {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    spcWAD::TLumpsList lowLevelLumpsList = self.wadTools->lumpsList();
    for (spcWAD::TLumpsListConstIter iter = lowLevelLumpsList.begin(); iter != lowLevelLumpsList.end(); iter++) {
        [lumpsList addObject:[self createLumpModelWithIter:iter]];
    }
    
    return [lumpsList copy];
}

- (NSArray<CellModel *> *)modelsListWithFilterString:(NSString *)filterString {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    return [self lumpsListWithNameFilter:[self createCPPFilterWithObjcFilter:@[filterString]]
                           includeFilter:YES
                         containsCompare:YES];
}

- (NSArray<CellModel *> *)modelsListWithoutMaps {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    return [self lumpsListWithNameFilter:spcWAD::ALumpTools::doom1MapLumpsNames()
                           includeFilter:NO
                         containsCompare:NO];
}

- (NSArray<CellModel *> *)modelsListWithMarkersOnly {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    spcWAD::TLumpsList lowLevelLumpsList = self.wadTools->lumpsList();
    for (spcWAD::TLumpsListConstIter iter = lowLevelLumpsList.begin(); iter != lowLevelLumpsList.end(); iter++) {
        if (iter->lumpSize != 0) {
            continue;
        }
        
        [lumpsList addObject:[self createLumpModelWithIter:iter]];
    }
    
    return [lumpsList copy];
}

- (void)exportModel:(CellModel *)model folderPath:(NSString *)folderPath {
    spcWAD::ALump exportLump(model.size, model.offset, model.name.UTF8String);
    self.wadTools->exportLump(exportLump, folderPath.UTF8String);
}

- (void)exportModelsAsImage:(CellModel *)model folderPath:(NSString *)folderPath {
    spcWAD::ALump exportLump(model.size, model.offset, model.name.UTF8String);
    self.wadTools->exportLump(exportLump, folderPath.UTF8String);
}

#pragma mark - Routine -

- (CellModel *)createLumpModelWithIter:(spcWAD::TLumpsListConstIter)iter {
    CellModel *newModel = [CellModel new];
    
    newModel.name = [NSString stringWithUTF8String:iter->lumpName.c_str()];
    newModel.offset = iter->lumpOffset;
    newModel.size = iter->lumpSize;
    newModel.about = [NSString stringWithUTF8String:spcWAD::ALumpTools::lumpDescription(iter->lumpName).description.c_str()];

    return newModel;
}

/**
 Filters lumps list
 @param filtersList list of strings which should filter lumps names
 @param includeFilter if YES then every lump with name that matches filter list will be included in result, otherwise will be excluded
 @param containsCompare if YES then filters everything that strictly matches filter array
 @return filtered list of lumps
 */
- (NSArray<CellModel *> *)lumpsListWithNameFilter:(std::vector<std::string>) filtersList
                                    includeFilter:(BOOL)includeFilter
                                  containsCompare:(BOOL)containsCompare {
    NSMutableArray<CellModel *> *lumpsList = [NSMutableArray new];
    if (!self.wadTools) {
        return [lumpsList copy];
    }
    
    spcWAD::TLumpsList lowLevelLumpsList = self.wadTools->lumpsList();
    
    for (spcWAD::TLumpsListConstIter iter = lowLevelLumpsList.begin(); iter != lowLevelLumpsList.end(); iter++) {
        for (std::vector<std::string>::iterator filterIter = filtersList.begin(); filterIter != filtersList.end(); ++filterIter) {
            BOOL filterResult = [self filterCheckWithFilter:*filterIter
                                                   lumpName:iter->lumpName
                                            containsCompare:containsCompare];
            if (!filterResult) {
                continue;
            }
                
            if (includeFilter) {
                [lumpsList addObject:[self createLumpModelWithIter:iter]];
                break;
            }
            
            if (filterResult && !includeFilter) {
                NSLog(@"%s", iter->lumpName.c_str());
                break;
            }

            if (filterResult) {
            [lumpsList addObject:[self createLumpModelWithIter:iter]];
            break;
            }
        }
    }
    
    return [lumpsList copy];
}

- (BOOL)filterCheckWithFilter:(const std::string &)filter
                     lumpName:(const std::string &)lumpName
              containsCompare:(BOOL)containsCompare {
    if (containsCompare) {
        if (spcWAD::AUtilities::stringContainsSubstring(lumpName, filter)) {
            return true;
        }
    }
    else {
        if (spcWAD::AUtilities::stringCompare(lumpName, filter)) {
            return true;
        }
    }
    
    return false;
}

- (std::vector<std::string>)createCPPFilterWithObjcFilter:(NSArray<NSString *> *)objcFilter {
    std::vector<std::string> mapLumps;
    if (objcFilter.count == 0) {
        return mapLumps;
    }
    
    for (NSString *filterString in objcFilter) {
        mapLumps.push_back([filterString UTF8String]);
    }
    
    return mapLumps;
}

@end
