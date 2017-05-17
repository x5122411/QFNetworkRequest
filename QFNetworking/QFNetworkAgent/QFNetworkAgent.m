//
//  QFNetworkAgent.m
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkAgent.h"
#import "QFNetworkRequestInternal.h"
#import "QFDownloadNetworkRequest.h"
#import "TMCache.h"
#import "QFNetworkConfig.h"
#import "NSString+URLComposition.h"


NS_ASSUME_NONNULL_BEGIN

@interface QFNetworkAgent ()

@property (nonatomic, strong) AFHTTPSessionManager *URLSessionManager;
@property (nonatomic, strong) NSMutableDictionary<NSString *, __kindof QFNetworkRequest *> *networkRequests;

@end

@implementation QFNetworkAgent

#pragma mark - life cycle

+ (instancetype _Nonnull)sharedInstance {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    
    return sharedInstance;
}

- (instancetype _Nonnull)init {
    self = [super init];
    if (self) {
        _URLSessionManager = [AFHTTPSessionManager manager];
        AFSecurityPolicy *securityPolicy = [AFSecurityPolicy policyWithPinningMode:AFSSLPinningModeNone];
        securityPolicy.allowInvalidCertificates = NO;
        securityPolicy.validatesDomainName = YES;
        _URLSessionManager.securityPolicy = securityPolicy;
        _networkRequests = [NSMutableDictionary dictionary];
    }
    
    return self;
}


#pragma mark - managing operations

#pragma mark add

- (void)addRequest:(__kindof QFNetworkRequest * _Nonnull)request {
    NSURLRequest *customURLRequest = request.customURLRequest;
    if (customURLRequest) {
        NSURLSessionDataTask *dataTask = [self.URLSessionManager dataTaskWithRequest:customURLRequest
                                                                   completionHandler:^(NSURLResponse *response, id responseObject, NSError *error) {
                                                                       [self handleRequestResult:request responseObject:responseObject error:error];
                                                                   }];
        [dataTask resume];
        request.sessionTask = dataTask;
        
        [self addNetworkRequest:request];
        return;
    }
    
    QFNetworkRequestType requestType = request.requestType;
    QFNetworkConfig *config = [QFNetworkConfig sharedInstance];
    
    /* check base url */
    NSString *baseUrl = request.baseUrl;
    if (!baseUrl.length) {
        baseUrl = config.baseUrl;
    }
    if (!baseUrl.length) {
        NSDictionary *userInfo = @{ NSLocalizedDescriptionKey: @"Network request missing base url!" };
        NSError *error = [NSError errorWithDomain:@"QFNetworkRequestErrorDomain"
                                             code:0
                                         userInfo:userInfo];
        [self handleRequestResult:request responseObject:nil error:error];
        return;
    }
    
    /* joint urls */
    NSString *requestUrl = baseUrl;
    if (!!request.urlPath.length) {
        requestUrl = [requestUrl stringByAppendingString:request.urlPath];
    }
    
    /* filter url */
    if ([config.networkFilter respondsToSelector:@selector(filterUrl:request:)]) {
        requestUrl = [config.networkFilter filterUrl:requestUrl request:request];
    }
    
    /* filter parameters */
    NSDictionary *parameters = request.parameters;
    if ([config.networkFilter respondsToSelector:@selector(filterParameter:fullUrl:request:)]) {
        parameters = [config.networkFilter filterParameter:parameters fullUrl:requestUrl request:request];
    }
    
    /* valid url string */
    requestUrl = [self validatedUrlString:requestUrl];
    
    /* handle cache policy */
    NSString *fullRequestUrl = [requestUrl urlStringWithParameters:parameters];
    /* valid full request url string */
    fullRequestUrl = [self validatedUrlString:fullRequestUrl];
    
    NSDictionary * _Nullable (^ _Nonnull cacheHandler)() = ^ NSDictionary * _Nullable {
        NSDictionary *cachedData = [[TMCache sharedCache] objectForKey:fullRequestUrl];
        if (cachedData) {
            request.responseJSONObject = cachedData;
            dispatch_async(dispatch_get_main_queue(), ^{
                !request.successCallback ?: request.successCallback(request);
            });
        }
        return cachedData;
    };
    
    BOOL useCache = YES;
    BOOL shouldContinueRequesting = YES;
    switch (request.cachePolicy) {
        case QFNetworkRequestReloadIgnoringCacheData:
            useCache = NO;
            break;
        case QFNetworkRequestReturnCacheDataThenLoad: {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                cacheHandler();
            });
        }
            break;
        case QFNetworkRequestReturnCacheDataElseLoad:
            shouldContinueRequesting = !cacheHandler();
            break;
        case QFNetworkRequestReturnCacheDataDontLoad: {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                cacheHandler();
            });
            shouldContinueRequesting = NO;
        }
            break;
            
        default:
            break;
    }
    
    if (!shouldContinueRequesting) {
        return;
    }
    
    /* set request serializer */
    AFHTTPRequestSerializer *requestSerializer = [AFHTTPRequestSerializer serializer];
    if (QFNetworkRequestSerializerTypeJSON == request.serializerType) {
        requestSerializer = [AFJSONRequestSerializer serializer];
    }
    
    /* set request timeout interval */
    requestSerializer.timeoutInterval = request.timeoutInterval;
    
    /* set request headers */
    [request.requestHeaders enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull value, BOOL * _Nonnull stop) {
        if ([key isKindOfClass:[NSString class]] && [value isKindOfClass:[NSString class]]) {
            [requestSerializer setValue:(NSString *)value forHTTPHeaderField:(NSString *)key];
        }
    }];
    
    self.URLSessionManager.requestSerializer = requestSerializer;
    
    /* start request operation */
    if (QFNetworkRequestTypeGet == requestType) {
        request.sessionTask = [self.URLSessionManager GET:requestUrl
                                               parameters:parameters
                                                 progress:^(NSProgress * _Nonnull downloadProgress) {
                                                     
                                                 }
                                                  success:^(NSURLSessionDataTask *task, id responseObject) {
                                                      [self handleRequestResult:request responseObject:responseObject error:nil];
                                                  }
                                                  failure:^(NSURLSessionDataTask *task, NSError *error) {
                                                      [self handleRequestResult:request responseObject:nil error:error];
                                                  }];
    }
    else if (QFNetworkRequestTypePost == request.requestType) {
        if (!request.constructingBodyBlock) {
            request.sessionTask = [self.URLSessionManager POST:requestUrl
                                                    parameters:parameters
                                                      progress:^(NSProgress * _Nonnull uploadProgress) {
                                       
                                                      }
                                                       success:^(NSURLSessionDataTask *task, id responseObject) {
                                                           [self handleRequestResult:request responseObject:responseObject error:nil];
                                                       }
                                                       failure:^(NSURLSessionDataTask *task, NSError *error) {
                                                           [self handleRequestResult:request responseObject:nil error:error];
                                                       }];
        }
        else {
            request.sessionTask = [self.URLSessionManager POST:requestUrl
                                                    parameters:parameters
                                     constructingBodyWithBlock:request.constructingBodyBlock
                                                      progress:^(NSProgress * _Nonnull uploadProgress) {
                                                          
                                                      }
                                                       success:^(NSURLSessionDataTask *task, id responseObject) {
                                                           [self handleRequestResult:request responseObject:responseObject error:nil];
                                                       }
                                                       failure:^(NSURLSessionDataTask *task, NSError *error) {
                                                           [self handleRequestResult:request responseObject:nil error:error];
                                                       }];
        
        }
    }

    [self addNetworkRequest:request];
}


#pragma mark cancel

- (void)cancelRequest:(__kindof QFNetworkRequest * _Nonnull)request {
    [request.sessionTask cancel];
    
    [self removeNetworkRequest:request];
    [request clearRequestBlocks];
}

- (void)cancelRequestsWithOwner:(id _Nonnull)owner {
    NSDictionary *copyRequests = [self.networkRequests copy];
    [copyRequests enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull value, BOOL * _Nonnull stop) {
        QFNetworkRequest *request = [value isKindOfClass:[QFNetworkRequest class]] ? value : nil;
        if (request.owner == owner) {
            [request cancel];
        }
    }];
}

- (void)cancelAllRequests {
    NSDictionary *copyRequests = [self.networkRequests copy];
    [copyRequests enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull value, BOOL * _Nonnull stop) {
        QFNetworkRequest *request = [value isKindOfClass:[QFNetworkRequest class]] ? value : nil;
        [request cancel];
    }];
}

#pragma mark handle result

- (void)handleRequestResult:(QFNetworkRequest * _Nonnull)request
             responseObject:(id _Nullable)responseObject
                      error:(NSError * _Nullable)error {
    request.responseJSONObject = responseObject;
    request.error = error;
    if (!error) {
        !request.successCallback ?: request.successCallback(request);
    }
    else {
        !request.failureCallback ?: request.failureCallback(request);
    }
    
    [self removeNetworkRequest:request];
    [request clearRequestBlocks];
}

#pragma mark - private

- (NSString * _Nullable)requestHashKey:(id<NSObject> _Nonnull)object {
    NSString *key = nil;
    if ([object respondsToSelector:@selector(hash)]) {
        key = [NSString stringWithFormat:@"%lu", (unsigned long)[object hash]];
    }
    
    return key;
}

- (void)addNetworkRequest:(QFNetworkRequest * _Nonnull)request {
    NSString *key = [self requestHashKey:request.sessionTask];
    
    if (key.length) {
        @synchronized(self) {
            self.networkRequests[key] = request;
        }
    }
}

- (void)removeNetworkRequest:(QFNetworkRequest * _Nonnull)request {
    NSString *key = [self requestHashKey:request.sessionTask];
    
    if (key.length) {
        @synchronized(self) {
            [self.networkRequests removeObjectForKey:key];
        }
    }
}

- (NSString *)validatedUrlString:(NSString *)originalUrlString {
    NSString *validatedUrlString = nil;
    if ([originalUrlString respondsToSelector:@selector(stringByAddingPercentEncodingWithAllowedCharacters:)]) {
        validatedUrlString = [originalUrlString stringByAddingPercentEncodingWithAllowedCharacters:[NSCharacterSet URLQueryAllowedCharacterSet]];
    }
    else {
        validatedUrlString = [originalUrlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    }
    return validatedUrlString;
}

NS_ASSUME_NONNULL_END

@end
