//
//  QFDownloadNetworkRequest.h
//  MVVMTest
//
//  Created by Qingfeng on 15/11/30.
//  Copyright © 2015年 Qingfeng. All rights reserved.
//

#import "QFNetworkRequest.h"

@interface QFDownloadNetworkRequest : QFNetworkRequest

/**
 * @abstract A Boolean value that indicates if we should try to resume the download. Defaults is `YES`.
 */
@property (nonatomic) BOOL shouldResume;

/**
 * @abstract A Boolean value that indicates if we should allow a downloaded file to overwrite a previously downloaded file of the same name. Defaults to `NO`.
 */
@property (nonatomic) BOOL shouldOverwrite;

/**
 * @abstract A String value that defines the download target path or directory.
 */
@property (nonatomic, copy, nullable) NSString *downloadTargetPath;

/**
 * @abstract A String value that defines the download cache path.
 */
@property (nonatomic, copy, nullable) NSString *downloadCachePath;

/**
 * @abstract A block object to be executed when the download progress of the request is updated.
 */
@property (nonatomic, copy, nullable) QFNetworkProgressCallback downloadProgressCallback;

@end
