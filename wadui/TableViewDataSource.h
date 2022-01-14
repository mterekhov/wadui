//
//  TableViewDataSource.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CellModel;

NS_ASSUME_NONNULL_BEGIN

@protocol TableViewDelegate <NSObject>

- (void)cellTapped: (CellModel *) model;

@end

@interface TableViewDataSource : NSObject

- (void) cleanData;

@property (nonatomic, strong, nullable) NSArray<CellModel *> *modelsList;
@property (nonatomic, weak, nullable) id<TableViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
