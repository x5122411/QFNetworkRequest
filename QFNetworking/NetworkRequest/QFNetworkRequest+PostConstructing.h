//
//  QFNetworkRequest+PostConstructing.h
//  MVVMTest
//
//  Created by Qingfeng on 15/11/26.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkRequest.h"

@interface QFNetworkRequest (PostConstructing)

NS_ASSUME_NONNULL_BEGIN

/**
 Appends the HTTP header `Content-Disposition: file; filename=#{generated filename}; name=#{name}"` and `Content-Type: #{generated mimeType}`, followed by the encoded file data and the multipart form boundary.
 
 The filename and MIME type for this data in the form will be automatically generated, using the last path component of the `fileURL` and system associated MIME type for the `fileURL` extension, respectively.
 
 @param fileURL The URL corresponding to the file whose content will be appended to the form. This parameter must not be `nil`.
 @param name The name to be associated with the specified data. This parameter must not be `nil`.
 @param error If an error occurs, upon return contains an `NSError` object that describes the problem.
 
 */
- (void)appendPartWithFileURL:(NSURL *)fileURL
                         name:(NSString *)name
                        error:(NSError * __autoreleasing *)error;

/**
 Appends the HTTP header `Content-Disposition: file; filename=#{filename}; name=#{name}"` and `Content-Type: #{mimeType}`, followed by the encoded file data and the multipart form boundary.
 
 @param fileURL The URL corresponding to the file whose content will be appended to the form. This parameter must not be `nil`.
 @param name The name to be associated with the specified data. This parameter must not be `nil`.
 @param fileName The file name to be used in the `Content-Disposition` header. This parameter must not be `nil`.
 @param mimeType The declared MIME type of the file data. This parameter must not be `nil`.
 @param error If an error occurs, upon return contains an `NSError` object that describes the problem.
 
 */
- (void)appendPartWithFileURL:(NSURL *)fileURL
                         name:(NSString *)name
                     fileName:(NSString *)fileName
                     mimeType:(NSString *)mimeType
                        error:(NSError * __autoreleasing *)error;

/**
 Appends the HTTP header `Content-Disposition: file; filename=#{filename}; name=#{name}"` and `Content-Type: #{mimeType}`, followed by the data from the input stream and the multipart form boundary.
 
 @param inputStream The input stream to be appended to the form data
 @param name The name to be associated with the specified input stream. This parameter must not be `nil`.
 @param fileName The filename to be associated with the specified input stream. This parameter must not be `nil`.
 @param length The length of the specified input stream in bytes.
 @param mimeType The MIME type of the specified data. (For example, the MIME type for a JPEG image is image/jpeg.) For a list of valid MIME types, see http://www.iana.org/assignments/media-types/. This parameter must not be `nil`.
 */
- (void)appendPartWithInputStream:(NSInputStream *)inputStream
                             name:(NSString *)name
                         fileName:(NSString *)fileName
                           length:(int64_t)length
                         mimeType:(NSString *)mimeType;

/**
 Appends the HTTP header `Content-Disposition: file; filename=#{filename}; name=#{name}"` and `Content-Type: #{mimeType}`, followed by the encoded file data and the multipart form boundary.
 
 @param data The data to be encoded and appended to the form data.
 @param name The name to be associated with the specified data. This parameter must not be `nil`.
 @param fileName The filename to be associated with the specified data. This parameter must not be `nil`.
 @param mimeType The MIME type of the specified data. (For example, the MIME type for a JPEG image is image/jpeg.) For a list of valid MIME types, see http://www.iana.org/assignments/media-types/. This parameter must not be `nil`.
 */
- (void)appendPartWithFileData:(NSData *)data
                          name:(NSString *)name
                      fileName:(NSString *)fileName
                      mimeType:(NSString *)mimeType;

/**
 Appends the HTTP headers `Content-Disposition: form-data; name=#{name}"`, followed by the encoded data and the multipart form boundary.
 
 @param data The data to be encoded and appended to the form data.
 @param name The name to be associated with the specified data. This parameter must not be `nil`.
 */

- (void)appendPartWithFormData:(NSData *)data
                          name:(NSString *)name;


/**
 Appends HTTP headers, followed by the encoded data and the multipart form boundary.
 
 @param headers The HTTP headers to be appended to the form data.
 @param body The data to be encoded and appended to the form data. This parameter must not be `nil`.
 */
- (void)appendPartWithHeaders:(NSDictionary *)headers
                         body:(NSData *)body;

NS_ASSUME_NONNULL_END

@end
