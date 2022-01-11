//
//  LodModel.h
//  wadui
//
//  Created by Michael Terekhov on 12.01.2022.
//  Copyright © 2022 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LodModel : NSObject

@property (nonatomic, assign) NSInteger size;
@property (nonatomic, assign) NSInteger offset;
@property (nonatomic, copy, nullable) NSString *name;

@end

NS_ASSUME_NONNULL_END
