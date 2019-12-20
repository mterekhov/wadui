//
//  LumpsListView.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "LumpsListDataSource.h"
#import "LumpsService.h"
#import "LumpModel.h"
#import "MainMenuHandler.h"

static const NSString *LumpsListNameCellID = @"LumpsListNameCellID";
static const NSString *LumpsListSizeCellID = @"LumpsListSizeCellID";
static const NSString *LumpsListOffsetCellID = @"LumpsListOffsetCellID";
static const NSString *LumpsListAboutCellID = @"LumpsListAboutCellID";

@interface LumpsListDataSource ()<MainMenuHandlerDelegate>

@property (nonatomic, strong, nullable) NSArray<LumpModel *> *lumpsList;

@end

@implementation LumpsListDataSource

#pragma mark - MainMenuHandlerDelegate -

- (void)openFileResults:(NSArray<NSURL *> *)urls {
    if (!urls.count) {
        return;
    }
    
    NSString *wadFilePath = urls.firstObject.path;
    self.lumpsService = [[LumpsService alloc] initWithWadFileName:wadFilePath];
    [self refreshLumpsList];
    [self.lumpsListTableView reloadData];
}

#pragma mark - NSTableViewDataSource -

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return self.lumpsList.count;
}

#pragma mark - NSTableViewDelegate -

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    NSString *cellId = [LumpsListNameCellID copy];
    NSString *cellText = @"FUCK";
    
    if ([tableColumn isEqualTo:tableView.tableColumns[0]]) {
        cellId = [LumpsListNameCellID copy];
        cellText = self.lumpsList[row].name;
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[1]]) {
        cellId = [LumpsListOffsetCellID copy];
        cellText = [NSString stringWithFormat:@"%li", (long)self.lumpsList[row].offset];
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[2]]) {
        cellId = [LumpsListSizeCellID copy];
        cellText = [NSString stringWithFormat:@"%li", (long)self.lumpsList[row].size];
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[3]]) {
        cellId = [LumpsListAboutCellID copy];
        cellText = self.lumpsList[row].about;
    }

    NSTableCellView *newCell = [tableView makeViewWithIdentifier:cellId owner:nil];
    newCell.textField.stringValue = cellText;
    
    return newCell;
}

#pragma mark - Routine -

- (NSString *)findCellIdWithTableView:(NSTableView *)tableView tableColumn:(NSTableColumn *)tableColumn {
    if ([tableColumn isEqualTo:tableView.tableColumns[0]]) {
        return [LumpsListNameCellID copy];
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[1]]) {
        return  [LumpsListOffsetCellID copy];
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[2]]) {
        return [LumpsListSizeCellID copy];
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[3]]) {
        return [LumpsListAboutCellID copy];
    }

    return [LumpsListNameCellID copy];
}

- (void)refreshLumpsList {
    self.lumpsList = [self.lumpsService lumpsList];
}

@end
