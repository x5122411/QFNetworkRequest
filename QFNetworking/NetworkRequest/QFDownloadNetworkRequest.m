//
//  QFDownloadNetworkRequest.m
//  MVVMTest
//
//  Created by Qingfeng on 15/11/30.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFDownloadNetworkRequest.h"
#import "QFNetworkRequestInternal.h"

@implementation QFDownloadNetworkRequest

- (void)clearRequestBlocks {
    [super clearRequestBlocks];
    
    self.downloadProgressCallback = nil;
}

- (BOOL)isURLSessionRequest {
    return NO;
}

@end
