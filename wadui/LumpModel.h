//
//  LumpModel.h
//  wadui
//
//  Created by Michael on 20/12/2019.
//  Copyright © 2019 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LumpModel : NSObject

@property (nonatomic, assign) NSInteger size;
@property (nonatomic, assign) NSInteger offset;
@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *about;

@end

NS_ASSUME_NONNULL_END
