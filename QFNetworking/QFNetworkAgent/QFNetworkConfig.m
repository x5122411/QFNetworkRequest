//
//  QFNetworkConfig.m
//  MVVMTest
//
//  Created by Qingfeng on 15/12/1.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkConfig.h"

@implementation QFNetworkConfig

+ (instancetype _Nonnull)sharedInstance {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    
    return sharedInstance;
}

@end
