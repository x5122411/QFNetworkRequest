//
//  QFNetworkRequest.m
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkRequest.h"
#import "QFNetworkRequestInternal.h"
#import "QFNetworkAgent.h"

const NSTimeInterval QFNetworkRequestTimeoutInterval = 20;

@implementation QFNetworkRequest

@dynamic urlResponse;

#pragma mark - life cycle

- (instancetype _Nonnull)initWithOwner:(id _Nullable)owner
                               baseUrl:(NSString * _Nullable)baseUrl
                               urlPath:(NSString * _Nullable)urlPath
                            parameters:(NSDictionary * _Nullable)parameters {
    self = [super init];
    if (self) {
        _owner = owner;
        _baseUrl = baseUrl;
        _urlPath = urlPath;
        _parameters  = parameters;
        _timeoutInterval = QFNetworkRequestTimeoutInterval;
        _requestType = QFNetworkRequestTypeGet;
        _serializerType = QFNetworkRequestSerializerTypeHTTP;
        _cachePolicy = QFNetworkRequestReloadIgnoringCacheData;
    }
    return self;
}

- (instancetype _Nonnull)initWithOwner:(id _Nullable)owner
                               urlPath:(NSString * _Nullable)urlPath
                            parameters:(NSDictionary * _Nullable)parameters {
    return [self initWithOwner:owner baseUrl:nil urlPath:urlPath parameters:parameters];
}

- (instancetype _Nonnull)init {
    return [self initWithOwner:nil baseUrl:nil urlPath:nil parameters:nil];
}

#pragma mark - managing oprations

- (void)start {
    [[QFNetworkAgent sharedInstance] addRequest:self];
}

- (void)cancel {
    [[QFNetworkAgent sharedInstance] cancelRequest:self];
}

+ (void)cancelRequestsWithOwner:(id _Nonnull)owner {
    [[QFNetworkAgent sharedInstance] cancelRequestsWithOwner:owner];
}

- (void)startWithSuccessCallback:(QFNetworkCallback _Nullable)successCallback
                 failureCallback:(QFNetworkCallback _Nullable)failureCallback {
    self.successCallback = successCallback;
    self.failureCallback = failureCallback;
    [self start];
}

#pragma mark - private

- (void)clearRequestBlocks {
    self.successCallback = nil;
    self.failureCallback = nil;
}

#pragma mark - getters & setters



- (BOOL)isExecuting {
    return (NSURLSessionTaskStateRunning == self.sessionTask.state);
}

- (NSURLResponse *)urlResponse {
    return self.sessionTask.response;
}

@end
