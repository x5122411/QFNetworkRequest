//
//  QFNetworkRequestDefines.h
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef QFNetworkRequestDefines_h
#define QFNetworkRequestDefines_h

extern const NSTimeInterval QFNetworkRequestTimeoutInterval;

typedef NS_ENUM(NSInteger, QFNetworkRequestType) {
    QFNetworkRequestTypeGet = 0,
    QFNetworkRequestTypePost
};

typedef NS_ENUM(NSInteger, QFNetworkRequestSerializerType) {
    QFNetworkRequestSerializerTypeHTTP = 0,
    QFNetworkRequestSerializerTypeJSON,
};

@class QFNetworkRequest;

typedef void (^QFNetworkCallback)(__kindof QFNetworkRequest * _Nonnull request);

typedef void (^QFNetworkProgressCallback)(NSInteger bytesRead, long long totalBytesRead, long long totalBytesExpected, long long totalBytesReadForFile, long long totalBytesExpectedToReadForFile);

typedef NSURLRequest * _Nonnull (^QFRequestRedirectedBlock)(NSURLRequest * _Nonnull redirectedRequest, NSURLResponse * _Nonnull redirectResponse);

/**
 * @abstract The QFNetworkRequestCachePolicy enum defines constants that can be used to specify the type of interactions that take place with the caching system when the URL loading system processes a request.
 
 * @constant QFNetworkRequestReloadIgnoringCacheData Specifies that the data for the URL load should be loaded from the origin source. No existing cache data, regardless of its freshness or validity, should be used to satisfy a URL load request.
 
 * @constant QFNetworkRequestReturnCacheDataThenLoad Specifies that the existing cache data should be used to satisfy a URL load request, regardless of its age or expiration date. Then a normal request is made to load the URL from the origin source
 
 * @constant QFNetworkRequestReturnCacheDataElseLoad Specifies that the existing cache data should be used to satisfy a URL load request, regardless of its age or expiration date. However, if there is no existing data in the cache corresponding to a URL load request, the URL is loaded from the origin source.
 
 * @constant QFNetworkRequestReturnCacheDataDontLoad Specifies that the existing cache data should be used to satisfy a URL load request, regardless of its age or expiration date. However, if there is no existing data in the cache corresponding to a URL load request, no attempt is made to load the URL from the origin source, and the load is considered to have failed. This constant specifies a behavior that is similar to an "offline" mode.
 */
typedef NS_ENUM(NSUInteger, QFNetworkRequestCachePolicy) {
    QFNetworkRequestReloadIgnoringCacheData = 0,
    QFNetworkRequestReturnCacheDataThenLoad = 1,
    QFNetworkRequestReturnCacheDataElseLoad = 2,
    QFNetworkRequestReturnCacheDataDontLoad = 3
};

#endif /* QFNetworkRequestDefines_h */
