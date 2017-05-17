//
//  QFNetworkAgent.h
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QFNetworkRequest.h"

/**
 * 'QFNetworkAgent' manages all the network requests during their life cycles.
 */
@interface QFNetworkAgent : NSObject

///----------------------------
/// @name Getting Network Agent
///----------------------------

/**
 * @abstract Returns the shared network agent.
 */
+ (instancetype _Nonnull)sharedInstance;

///----------------------------------
/// @name Adding / Canceling Requests
///----------------------------------

/**
 * @abstract Adds a new network request to the network agent.
 *
 * @param request The network request to be added to the network agent.
 */
- (void)addRequest:(__kindof QFNetworkRequest * _Nonnull)request;

/**
 * @abstract Cancels a specified network request from the network agent.
 *
 * @param request The network request to be canceled from the network agent.
 */
- (void)cancelRequest:(__kindof QFNetworkRequest * _Nonnull)request;

/**
 * @abstract Cancels network requests with a specified owner.
 *
 * @param owner The specified owner.
 */
- (void)cancelRequestsWithOwner:(id _Nonnull)owner;

/**
 * @abstract Cancels all the network requests from the network agent.
 */
- (void)cancelAllRequests;

@end
