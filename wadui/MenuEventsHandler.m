//
//  MainMenuHandler.m
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import "MenuEventsHandler.h"
#import "LumpsService.h"
#import "LodService.h"
#import "ModelsServiceProtocol.h"
#import "TableViewDataSource.h"
#import "AppDelegate.h"

@interface MenuEventsHandler ()

@property (nonatomic, strong, nullable) id<ModelsServiceProtocol> modelsService;
@property (weak, nonatomic, nullable) IBOutlet NSTableView *tableView;
@property (weak, nonatomic, nullable) IBOutlet TableViewDataSource *tableViewDataSource;

@end

@implementation MenuEventsHandler

- (void)controlTextDidEndEditing: (NSNotification *)obj {
    if (![obj.object isKindOfClass:[NSSearchField class]]) {
        return;
    }
    
    NSSearchField *searchField = obj.object;
    self.tableViewDataSource.modelsList = [self.modelsService modelsListWithFilterString: searchField.stringValue];
    [self.tableView reloadData];
}

- (IBAction)openDocument: (id)sender {
    NSOpenPanel* openDialog = [NSOpenPanel openPanel];
    if ([openDialog runModal] == NSModalResponseOK) {
        if (!openDialog.URLs.count) {
            return;
        }
        
        NSURL *path = openDialog.URLs.firstObject;
        if ([path.pathExtension.lowercaseString isEqualToString:@"lod"]) {
            self.modelsService = [[LodService alloc] initWithLodFileName: path.path];
            AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
            appDelegate.window.title = [NSString stringWithFormat:@"%@ - %li LOD items", path.lastPathComponent, self.tableViewDataSource.modelsList.count];
        }
        
        if ([openDialog.URLs.firstObject.pathExtension.lowercaseString isEqualToString:@"wad"]) {
            self.modelsService = [[LumpsService alloc] initWithWadFileName: path.path];
            AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
            appDelegate.window.title = [NSString stringWithFormat:@"%@ - %li lump", path.lastPathComponent, self.tableViewDataSource.modelsList.count];
        }

        self.tableViewDataSource.modelsList = [self.modelsService modelsList];
        [self.tableView reloadData];
    }
}

- (IBAction)performClose: (id)sender {
    [self.tableViewDataSource cleanData];
    self.modelsService = nil;
    [self.tableView reloadData];
    
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    appDelegate.window.title = @"wadui";
}

- (IBAction)showAll: (id)sender {
    self.tableViewDataSource.modelsList = [self.modelsService modelsList];
    [self.tableView reloadData];
}

- (IBAction)hideMaps: (id)sender {
    self.tableViewDataSource.modelsList = [self.modelsService modelsListWithoutMaps];
    [self.tableView reloadData];
}

- (IBAction)showMarkersOnly: (id)sender {
    self.tableViewDataSource.modelsList = [self.modelsService modelsListWithMarkersOnly];
    [self.tableView reloadData];
}

- (IBAction)exportAsImage: (id)sender {
//    if (self.delegate == nil) {
//        return;
//    }
//
//    if (![self.delegate canExport]) {
//        return;
//    }
//    NSOpenPanel* openDialog = [NSOpenPanel openPanel];
//    openDialog.canChooseDirectories = YES;
//    openDialog.canChooseFiles = NO;
//    if ([openDialog runModal] == NSModalResponseOK) {
//        [self.lumpsListTableView.selectedRowIndexes enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * _Nonnull stop) {
//            [self.lumpsService exportLump:self.lumpsList[idx]
//                               folderPath:openDialog.URLs.firstObject.path];
//        }];
//    }
}

- (IBAction)exportSelectedLumps: (id)sender {
//    if (self.delegate == nil) {
//        return;
//    }
//    
//    if (![self.delegate canExport]) {
//        return;
//    }
//    NSOpenPanel* openDialog = [NSOpenPanel openPanel];
//    openDialog.canChooseDirectories = YES;
//    openDialog.canChooseFiles = NO;
//    if ([openDialog runModal] == NSModalResponseOK) {
//        if (self.lumpsService == nil) {
//            return;
//        }
//
//        [self.lumpsListTableView.selectedRowIndexes enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL * _Nonnull stop) {
//            [self.lumpsService exportLump:self.lumpsList[idx]
//                               folderPath:openDialog.URLs.firstObject.path];
//        }];
//    }
}

@end
