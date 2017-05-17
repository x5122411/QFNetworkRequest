/**
* 'QFNetworkRequest' encapsulates a network request as an object, which uses a request operation ('AFHTTPRequestOperation' or 'NSURLSessionTask') to perform network tasks.


eg:

- (void)loadData {
    NSDictionary *parameters = @{ @"type": @(1), "size": @(10) };
    
    QFNetworkRequest *request = [[QFNetworkRequest alloc] initWithOwner:self 
                                                                urlPath:@"/student_center/index"
                                                             parameters:parameters];
                                                             
    request.cachePolicy = QFNetworkRequestReturnCacheDataThenLoad;

    [request startWithSuccessCallback:^(QFNetworkRequest * _Nonnull request) {
        NSLog(@"[%@]-Load data succeeded!", NSStringFromClass([self class]));
    } 
        failureCallback:^(QFNetworkRequest * _Nonnull request) {
        NSLog(@"[%@]-Load data failed!", NSStringFromClass([self class]));
    }];
}

- (void)cancelLoadData {
// [self.request cancel];
// [QFNetworkRequest cancelRequestsWithOwner:self];
// [[QFNetworkAgent sharedInstance] cancelRequestsWithOwner:self];
}

* @endcode
