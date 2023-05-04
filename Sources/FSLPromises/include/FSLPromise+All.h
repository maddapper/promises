/**
 Copyright 2018 Google Inc. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at:

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import "FSLPromise.h"

NS_ASSUME_NONNULL_BEGIN

@interface FSLPromise<Value>(AllAdditions)

/**
 Wait until all of the given promises are fulfilled.
 If one of the given promises is rejected, then the returned promise is rejected with same error.
 If any other arbitrary value or `NSError` appears in the array instead of `FSLPromise`,
 it's implicitly considered a pre-fulfilled or pre-rejected `FSLPromise` correspondingly.
 Promises resolved with `nil` become `NSNull` instances in the resulting array.

 @param promises Promises to wait for.
 @return Promise of an array containing the values of input promises in the same order.
 */
+ (FSLPromise<NSArray *> *)all:(NSArray *)promises NS_SWIFT_UNAVAILABLE("");

/**
 Wait until all of the given promises are fulfilled.
 If one of the given promises is rejected, then the returned promise is rejected with same error.
 If any other arbitrary value or `NSError` appears in the array instead of `FSLPromise`,
 it's implicitly considered a pre-fulfilled or pre-rejected FSLPromise correspondingly.
 Promises resolved with `nil` become `NSNull` instances in the resulting array.

 @param queue A queue to dispatch on.
 @param promises Promises to wait for.
 @return Promise of an array containing the values of input promises in the same order.
 */
+ (FSLPromise<NSArray *> *)onQueue:(dispatch_queue_t)queue
                               all:(NSArray *)promises NS_REFINED_FOR_SWIFT;

@end

/**
 Convenience dot-syntax wrappers for `FSLPromise` `all` operators.
 Usage: FSLPromise.all(@[ ... ])
 */
@interface FSLPromise<Value>(DotSyntax_AllAdditions)

+ (FSLPromise<NSArray *> * (^)(NSArray *))all FSL_PROMISES_DOT_SYNTAX NS_SWIFT_UNAVAILABLE("");
+ (FSLPromise<NSArray *> * (^)(dispatch_queue_t, NSArray *))allOn FSL_PROMISES_DOT_SYNTAX
    NS_SWIFT_UNAVAILABLE("");

@end

NS_ASSUME_NONNULL_END
