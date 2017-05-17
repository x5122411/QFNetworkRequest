//
//  NSString+URLComposition.m
//  BJEducation
//
//  Created by Qingfeng on 15/12/7.
//  Copyright © 2015年 com.bjhl. All rights reserved.
//

#import "NSString+URLComposition.h"

@implementation NSString (URLComposition)

- (NSString * _Nonnull)urlStringWithParameters:(NSDictionary * _Nonnull)parameters {
    NSMutableArray *stringPairs = [NSMutableArray array];
    [parameters enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull value, BOOL * _Nonnull stop) {
        NSString *finalValue = [value isKindOfClass:[NSString class]] ? value : [value description];
        finalValue = [finalValue stringByReplacingOccurrencesOfString:@"?" withString:@"%3F"];
        finalValue = [finalValue stringByReplacingOccurrencesOfString:@"=" withString:@"%3D"];
        NSString *pair = [NSString stringWithFormat:@"%@=%@", key, finalValue];
        [stringPairs addObject:pair];
    }];
    
    NSString *stringParams = [stringPairs componentsJoinedByString:@"&"];
    if ([self rangeOfString:@"?"].location == NSNotFound) {
        return [self stringByAppendingFormat:@"?%@", stringParams];
    }
    else {
        return [self stringByAppendingFormat:@"&%@", stringParams];
    }
}

@end
