//
//  QFNetworkRequest.h
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkRequestDefines.h"
#import <AFNetworking/AFNetworking.h>

/**
 * 'QFNetworkRequest' encapsulates a network request as an object, which uses a request operation ('AFHTTPRequestOperation' or 'NSURLSessionTask') to perform network tasks.
 * Usage:
 *
 * @code
 
 #import "QFNetworkAgent.h"
 
 ...
 
- (void)loadData {
    NSDictionary *parameters = @{ @"type": @(1),
                                  @"size": @(10) };
    QFNetworkRequest *request = [[QFNetworkRequest alloc] initWithOwner:self
                                                                urlPath:@"/student_center/index"
                                                             parameters:parameters];
    request.cachePolicy = QFNetworkRequestReturnCacheDataThenLoad;

    [request startWithSuccessCallback:^(QFNetworkRequest * _Nonnull request) {
        NSLog(@"[%@]-Load data succeeded!", NSStringFromClass([self class]));
    } failureCallback:^(QFNetworkRequest * _Nonnull request) {
        NSLog(@"[%@]-Load data failed!", NSStringFromClass([self class]));
    }];
}

- (void)cancelLoadData {
    // [self.request cancel];
    // [QFNetworkRequest cancelRequestsWithOwner:self];
    // [[QFNetworkAgent sharedInstance] cancelRequestsWithOwner:self];
}
 
 * @endcode
 */
@interface QFNetworkRequest : NSObject

///-------------------------------------
/// @name Constructing A Network Request
///-------------------------------------

/**
 * @abstract The object that owns this network request.
 */
@property (nonatomic, weak, nullable) id owner;

/**
 * @abstract The network request type. Defaults to 'QFNetworkRequestTypeGet'.
 *
 * @see 'QFNetworkRequestType'
 */
@property (nonatomic, assign) QFNetworkRequestType requestType;

/**
 * @abstract The url used to construct the request URL from relative paths.
 *
 * @discussion The 'QFNetworkAgent' prefers to use the base url of a network request to construct the request URL. However, if it is nil, the base url of the shared 'QFNetworkConfig' is used.
 */
@property (nonatomic, copy, nullable) NSString *baseUrl;

/**
 * @abstract The url path used to create the request URL.
 */
@property (nonatomic, copy, nullable) NSString *urlPath;

/**
 * @abstract The parameters used to construct a request operation.
 */
@property (nonatomic, copy, nullable) NSDictionary *parameters;

/**
 * @abstract The network request’s cache policy. Defaults to 'QFNetworkRequestReloadIgnoringCacheData'.
 *
 * @see 'QFNetworkRequestCachePolicy'
 */
@property (nonatomic, assign) QFNetworkRequestCachePolicy cachePolicy;

/**
 * @abstract The headers used to construct requests, which are added into the header of HTTP requests.
 */
@property (nonatomic, copy, nullable) NSDictionary *requestHeaders;

/**
 * @abstract The serializer type used to generate a request serializer. Defaults to 'QFNetworkRequestSerializerTypeHTTP'.
 *
 * @see 'QFNetworkRequestSerializerType'
 */
@property (nonatomic, assign) QFNetworkRequestSerializerType serializerType;

/**
 * @abstract The timeout interval for a created request. Defaults to 20 seconds.
 */
@property (nonatomic, assign) NSTimeInterval timeoutInterval;

/**
 * @abstract Builds a custom URL request.
 *
 * @discussion All the other constructing properties are ignored if the customURLRequest is not nil.
 */
@property (nonatomic, strong, nullable) NSURLRequest *customURLRequest;

///----------------------------
/// @name Getting Response Data
///----------------------------

/**
 * @abstract Returns the URL response to this request.
 */
@property (nonatomic, readonly, strong, nullable) __kindof NSURLResponse *urlResponse;

/**
 * @abstract Returns the response json object of this request.
 */
@property (nonatomic, readonly, strong, nullable) id responseJSONObject;

/**
 * @abstract The error, if any, that occurred in the lifecycle of the request.
 */
@property (nonatomic, readonly, strong, nullable) NSError *error;

///---------------------------------
/// @name Managing Callback Handlers
///---------------------------------

/**
 * @abstract The block to be executed on the completion of a successful request.
 */
@property (nonatomic, copy, nullable) QFNetworkCallback successCallback;

/**
 * @abstract The block to be executed on the completion of an unsuccessful request.
 */
@property (nonatomic, copy, nullable) QFNetworkCallback failureCallback;

/**
 * @abstract A block to be executed when the URL request is redirected.
 */
@property (nonatomic, copy, nullable) QFRequestRedirectedBlock redirectedBlock;

/**
 * @abstract A block object to be executed during constructing a 'POST' request. The block takes a single argument and appends data to the HTTP body. The block argument is an object adopting the `AFMultipartFormData` protocol.
 *
 * @see `AFMultipartFormData`
 */
@property (nonatomic, copy, nullable) void (^constructingBodyBlock)(id<AFMultipartFormData> _Nonnull formData);

///------------------
/// @name Initializer
///------------------

/**
 * @abstract Designated initializer.
 *
 * @param owner The object that owns this network request.
 * @param baseUrl The url used to construct the request URL from relative paths.
 * @param urlPath The url path used to create the request URL.
 * @param parameters The parameters to be encoded according to the request serializer.
 */
- (instancetype _Nonnull)initWithOwner:(id _Nullable)owner
                               baseUrl:(NSString * _Nullable)baseUrl
                               urlPath:(NSString * _Nullable)urlPath
                            parameters:(NSDictionary * _Nullable)parameters NS_DESIGNATED_INITIALIZER;

/**
 * @abstract Convenient initializer.
 *
 * @param owner The object that owns this network request.
 * @param urlPath The url path used to create the request URL.
 * @param parameters The parameters to be encoded according to the request serializer.
 */
- (instancetype _Nonnull)initWithOwner:(id _Nullable)owner
                               urlPath:(NSString * _Nullable)urlPath
                            parameters:(NSDictionary * _Nullable)parameters;

///-----------------------------------
/// @name Starting / Canceling Request
///-----------------------------------

/**
 * @abstract A Boolean value indicating whether the request is currently executing. (read-only)
 *
 * @return `YES` if the operation is currently executing its main task or NO if it is not.
 */
@property(nonatomic, readonly, getter=isExecuting) BOOL executing;

/**
 * @abstract Starts the execution of the request operation.
 */
- (void)start;

/**
 * @abstract Cancels the execution of the request operation.
 */
- (void)cancel;

/**
 * @abstract Cancels network requests with a specified owner.
 *
 * @param owner The specified owner.
 */
+ (void)cancelRequestsWithOwner:(id _Nonnull)owner;

/**
 * @abstract Starts a request with a success block and a failure block.
 *
 * @param successCallback The block to be executed on the completion of a successful request. This block has no return value and takes one argument: the completed request.
 * @param failureCallback The block to be executed on the completion of an unsuccessful request. This block has no return value and takes one argument: the completed request.
 */
- (void)startWithSuccessCallback:(QFNetworkCallback _Nullable)successCallback
                 failureCallback:(QFNetworkCallback _Nullable)failureCallback;

@end
