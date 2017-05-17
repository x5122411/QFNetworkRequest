//
//  QFNetworkRequest+PostConstructing.m
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkRequest+PostConstructing.h"
#import "QFNetworkRequestInternal.h"

@implementation QFNetworkRequest (PostConstructing)

- (void)appendPartWithFileURL:(NSURL *)fileURL
                         name:(NSString *)name
                        error:(NSError * __autoreleasing *)error {
    self.constructingBodyBlock = ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithFileURL:fileURL name:name error:error];
    };
}

- (void)appendPartWithFileURL:(NSURL *)fileURL
                         name:(NSString *)name
                     fileName:(NSString *)fileName
                     mimeType:(NSString *)mimeType
                        error:(NSError * __autoreleasing *)error {
    self.constructingBodyBlock = ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithFileURL:fileURL name:name fileName:fileName mimeType:mimeType error:error];
    };
}

- (void)appendPartWithInputStream:(NSInputStream *)inputStream
                             name:(NSString *)name
                         fileName:(NSString *)fileName
                           length:(int64_t)length
                         mimeType:(NSString *)mimeType {
    self.constructingBodyBlock = ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithInputStream:inputStream name:name fileName:fileName length:length mimeType:mimeType];
    };
}

- (void)appendPartWithFileData:(NSData *)data
                          name:(NSString *)name
                      fileName:(NSString *)fileName
                      mimeType:(NSString *)mimeType {
    self.constructingBodyBlock = ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithFileData:data name:name fileName:fileName mimeType:mimeType];
    };
}

- (void)appendPartWithFormData:(NSData *)data
                          name:(NSString *)name {
    self.constructingBodyBlock = ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithFormData:data name:name];
    };
}

- (void)appendPartWithHeaders:(NSDictionary *)headers
                         body:(NSData *)body {
    self.constructingBodyBlock = ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithHeaders:headers body:body];
    };
}

@end
