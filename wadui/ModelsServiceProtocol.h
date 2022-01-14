//
//  ModelsServiceProtocol.h
//  wadui
//
//  Created by Michael Terekhov on 12.01.2022.
//  Copyright © 2022 Michael. All rights reserved.
//

#ifndef ModelsServiceProtocol_h
#define ModelsServiceProtocol_h

#import <Foundation/Foundation.h>

@class CellModel;

@protocol ModelsServiceProtocol <NSObject>

- (NSArray<CellModel *> *)modelsListWithFilterString: (NSString *)filterString;
- (NSArray<CellModel *> *)modelsList;
- (NSArray<CellModel *> *)modelsListWithoutMaps;
- (NSArray<CellModel *> *)modelsListWithMarkersOnly;
- (void)exportModel: (CellModel *)model folderPath: (NSString *)folderPath;
- (void)exportModelAsImage: (CellModel *)model folderPath: (NSString *)folderPath;

@end

#endif /* ModelsServiceProtocol_h */
