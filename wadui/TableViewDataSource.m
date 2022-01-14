//
//  ModelsListView.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "TableViewDataSource.h"
#import "CellModel.h"

static const NSString *ModelsListNameCellID = @"ModelsListNameCellID";
static const NSString *ModelsListSizeCellID = @"ModelsListSizeCellID";
static const NSString *ModelsListOffsetCellID = @"ModelsListOffsetCellID";
static const NSString *ModelsListAboutCellID = @"ModelsListAboutCellID";

@implementation TableViewDataSource

- (void) cleanData {
    self.modelsList = [NSArray<CellModel *> new];
}

- (IBAction)lumpSelected: (id)sender {
//    [self.delegate cellTapped: self.modelsList[]]
}


#pragma mark - NSTableViewDataSource -

- (NSInteger)numberOfRowsInTableView: (NSTableView *)tableView {
    return self.modelsList.count;
}

#pragma mark - NSTableViewDelegate -

- (void)tableViewSelectionDidChange: (NSNotification *)notification {
//    NSLog(@"selected %li", self.modelsListTableView.selectedRowIndexes.count);
}

- (NSView *)tableView: (NSTableView *)tableView viewForTableColumn: (NSTableColumn *)tableColumn row: (NSInteger)row {
    BOOL shouldShowInHex = YES;
    NSString *cellId = [ModelsListNameCellID copy];
    NSString *cellText = @"FUCK";
    
    NSString *printMask = @"%li";
    if (shouldShowInHex) {
        printMask = @"%#010x";
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[0]]) {
        cellId = [ModelsListNameCellID copy];
        cellText = self.modelsList[row].name;
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[1]]) {
        cellId = [ModelsListOffsetCellID copy];
        cellText = [NSString stringWithFormat: printMask, (long)self.modelsList[row].offset];
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[2]]) {
        cellId = [ModelsListSizeCellID copy];
        cellText = [NSString stringWithFormat: printMask, (long)self.modelsList[row].size];
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[3]]) {
        cellId = [ModelsListAboutCellID copy];
        cellText = [NSString stringWithFormat: @"%@", self.modelsList[row].about];
    }

    NSTableCellView *newCell = [tableView makeViewWithIdentifier: cellId owner: nil];
    newCell.textField.stringValue = cellText;
    
    return newCell;
}

#pragma mark - Routine -

- (NSString *)findCellIdWithTableView: (NSTableView *)tableView tableColumn: (NSTableColumn *)tableColumn {
    if ([tableColumn isEqualTo: tableView.tableColumns[0]]) {
        return [ModelsListNameCellID copy];
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[1]]) {
        return  [ModelsListOffsetCellID copy];
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[2]]) {
        return [ModelsListSizeCellID copy];
    }
    
    if ([tableColumn isEqualTo: tableView.tableColumns[3]]) {
        return [ModelsListAboutCellID copy];
    }

    return [ModelsListNameCellID copy];
}

@end
