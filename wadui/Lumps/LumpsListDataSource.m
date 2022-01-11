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
#import "UIEventsHandler.h"
#import "AppDelegate.h"

static const NSString *LumpsListNameCellID = @"LumpsListNameCellID";
static const NSString *LumpsListSizeCellID = @"LumpsListSizeCellID";
static const NSString *LumpsListOffsetCellID = @"LumpsListOffsetCellID";
static const NSString *LumpsListAboutCellID = @"LumpsListAboutCellID";

@interface LumpsListDataSource ()<UIEventsHandlerDelegate>

@property (nonatomic, strong, nullable) NSArray<LumpModel *> *lumpsList;

@end

@implementation LumpsListDataSource

- (IBAction)lumpSelected:(id)sender {
    NSLog(@"sender %@", sender);
}

#pragma mark - MainMenuHandlerDelegate -

- (void)searchWithText:(NSString *)text {
    [self.lumpsService lumpsListWithFilterString:text];
    [self.lumpsListTableView reloadData];
}

- (void)showAll {
    [self refreshLumpsList];
    [self.lumpsListTableView reloadData];
}

- (void)hideMaps {
    self.lumpsList = [self.lumpsService lumpsListWithoutMaps];
    [self.lumpsListTableView reloadData];
}

- (void)showMarkersOnly {
    self.lumpsList = [self.lumpsService lumpsListWithMarkersOnly];
    [self.lumpsListTableView reloadData];
}

- (void)closeCurrentWad {
    self.lumpsList = [NSArray new];
    [self.lumpsListTableView reloadData];
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    appDelegate.window.title = @"wadui";
    self.lumpsService = nil;
}

- (BOOL)canExport {
    return !(self.lumpsService == nil);
}

- (void)exportSelectedLumps:(NSString *)path {
    if (self.lumpsService == nil) {
        return;
    }

    [self.lumpsListTableView.selectedRowIndexes enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * _Nonnull stop) {
        [self.lumpsService exportLump:self.lumpsList[idx]
                           folderPath:path];
    }];
}

- (void)exportSelectedLumpsAsImage:(NSString *)path {
    if (self.lumpsService == nil) {
        return;
    }
    
    [self.lumpsListTableView.selectedRowIndexes enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * _Nonnull stop) {
        [self.lumpsService exportLump:self.lumpsList[idx]
                           folderPath:path];
    }];
}

- (void)openFileResults:(NSArray<NSURL *> *)urls {
    if (!urls.count) {
        return;
    }
    
    NSString *wadFilePath = urls.firstObject.path;
    self.lumpsService = [[LumpsService alloc] initWithWadFileName:wadFilePath];
    [self refreshLumpsList];
    [self.lumpsListTableView reloadData];
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    appDelegate.window.title = [NSString stringWithFormat:@"%@ - %li lump", urls.firstObject.lastPathComponent, self.lumpsList.count];
}

#pragma mark - NSTableViewDataSource -

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return self.lumpsList.count;
}

#pragma mark - NSTableViewDelegate -

- (void)tableViewSelectionDidChange:(NSNotification *)notification {
    NSLog(@"selected %li", self.lumpsListTableView.selectedRowIndexes.count);
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    BOOL shouldShowInHex = YES;
    NSString *cellId = [LumpsListNameCellID copy];
    NSString *cellText = @"FUCK";
    
    NSString *printMask = @"%li";
    if (shouldShowInHex) {
        printMask = @"%#010x";
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[0]]) {
        cellId = [LumpsListNameCellID copy];
        cellText = self.lumpsList[row].name;
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[1]]) {
        cellId = [LumpsListOffsetCellID copy];
        cellText = [NSString stringWithFormat:printMask, (long)self.lumpsList[row].offset];
    }
    
    if ([tableColumn isEqualTo:tableView.tableColumns[2]]) {
        cellId = [LumpsListSizeCellID copy];
        cellText = [NSString stringWithFormat:printMask, (long)self.lumpsList[row].size];
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
