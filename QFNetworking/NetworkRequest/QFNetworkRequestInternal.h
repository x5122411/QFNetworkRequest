//
//  QFNetworkRequestInternal.h
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

// The following properties and methods are ONLY for use by 'QFNetworkRequest' and 'QFNetworkAgent'.
// These methods must never be called or overridden by other classes.

#import "QFNetworkRequest.h"

@interface QFNetworkRequest ()

/**
 * @abstract Returns the response json object of this request.
 */
@property (nonatomic, strong, nullable) id responseJSONObject;

/**
 * @abstract The error, if any, that occurred in the lifecycle of the request.
 */
@property (nonatomic, strong, nullable) NSError *error;


/**
 * @abstract The URL session task which performs the request task.
 */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_7_0
@property (nonatomic, strong, nullable) NSURLSessionTask *sessionTask;
#endif

/**
 * @abstract Sets all the blocks to nil to break retain cycle.
 */
- (void)clearRequestBlocks;

@end
