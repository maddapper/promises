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

@interface FSLPromise<Value>(DelayAdditions)

/**
 Creates a new pending promise that fulfills with the same value as `self` after the `delay`, or
 rejects with the same error immediately.

 @param interval Time to wait in seconds.
 @return A new pending promise that fulfills at least `delay` seconds later than `self`, or rejects
         with the same error immediately.
 */
- (FSLPromise *)delay:(NSTimeInterval)interval NS_SWIFT_UNAVAILABLE("");

/**
 Creates a new pending promise that fulfills with the same value as `self` after the `delay`, or
 rejects with the same error immediately.

 @param queue A queue to dispatch on.
 @param interval Time to wait in seconds.
 @return A new pending promise that fulfills at least `delay` seconds later than `self`, or rejects
         with the same error immediately.
 */
- (FSLPromise *)onQueue:(dispatch_queue_t)queue
                  delay:(NSTimeInterval)interval NS_REFINED_FOR_SWIFT;

@end

/**
 Convenience dot-syntax wrappers for `FSLPromise` `delay` operators.
 Usage: promise.delay(...)
 */
@interface FSLPromise<Value>(DotSyntax_DelayAdditions)

- (FSLPromise * (^)(NSTimeInterval))delay FSL_PROMISES_DOT_SYNTAX NS_SWIFT_UNAVAILABLE("");
- (FSLPromise * (^)(dispatch_queue_t, NSTimeInterval))delayOn FSL_PROMISES_DOT_SYNTAX
    NS_SWIFT_UNAVAILABLE("");

@end

NS_ASSUME_NONNULL_END
