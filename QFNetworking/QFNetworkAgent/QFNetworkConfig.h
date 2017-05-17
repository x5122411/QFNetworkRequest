//
//  QFNetworkConfig.h
//  MVVMTest
//
//  Created by Qingfeng on 15/12/1.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@class QFNetworkRequest;

@protocol QFNetworkFilter <NSObject>

@optional

- (NSString * _Nullable)filterUrl:(NSString * _Nullable)originalUrl
                          request:(QFNetworkRequest * _Nonnull)request;

- (NSDictionary * _Nullable)filterParameter:(NSDictionary * _Nullable)originalParameter
                                    fullUrl:(NSString * _Nullable)fullUrl
                                    request:(QFNetworkRequest * _Nonnull)request;

@end

@interface QFNetworkConfig : NSObject

/**
 * @abstract Returns the shared network config.
 */
+ (instancetype _Nonnull)sharedInstance;

/**
 * @abstract The url used to construct the request URL from relative paths.
 *
 * @discussion The 'QFNetworkAgent' uses the base url of the shared network config if the base url of a network request is nil.
 */
@property (nonatomic, copy, nullable) NSString *baseUrl;

/**
 * @abstract The 'QFNetworkAgent' calls methods on this parameter filter to filter parameters of a network request.
 *
 * @discussion An app usually uses this parameter filter to add common parameters.
 */
@property (nonatomic, strong, nullable) id<QFNetworkFilter> networkFilter;

@end
