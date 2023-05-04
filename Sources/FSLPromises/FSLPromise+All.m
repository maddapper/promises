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

#import "FSLPromise+All.h"

#import "FSLPromise+Async.h"
#import "FSLPromisePrivate.h"

@implementation FSLPromise (AllAdditions)

+ (FSLPromise<NSArray *> *)all:(NSArray *)promises {
  return [self onQueue:self.defaultDispatchQueue all:promises];
}

+ (FSLPromise<NSArray *> *)onQueue:(dispatch_queue_t)queue all:(NSArray *)allPromises {
  NSParameterAssert(queue);
  NSParameterAssert(allPromises);

  if (allPromises.count == 0) {
    return [[self alloc] initWithResolution:@[]];
  }
  NSMutableArray *promises = [allPromises mutableCopy];
  return [self
      onQueue:queue
        async:^(FSLPromiseFulfillBlock fulfill, FSLPromiseRejectBlock reject) {
          for (NSUInteger i = 0; i < promises.count; ++i) {
            id promise = promises[i];
            if ([promise isKindOfClass:self]) {
              continue;
            } else if ([promise isKindOfClass:[NSError class]]) {
              reject(promise);
              return;
            } else {
              [promises replaceObjectAtIndex:i
                                  withObject:[[self alloc] initWithResolution:promise]];
            }
          }
          for (FSLPromise *promise in promises) {
            [promise observeOnQueue:queue
                fulfill:^(id __unused _) {
                  // Wait until all are fulfilled.
                  for (FSLPromise *promise in promises) {
                    if (!promise.isFulfilled) {
                      return;
                    }
                  }
                  // If called multiple times, only the first one affects the result.
                  fulfill([promises valueForKey:NSStringFromSelector(@selector(value))]);
                }
                reject:^(NSError *error) {
                  reject(error);
                }];
          }
        }];
}

@end

@implementation FSLPromise (DotSyntax_AllAdditions)

+ (FSLPromise<NSArray *> * (^)(NSArray *))all {
  return ^(NSArray<FSLPromise *> *promises) {
    return [self all:promises];
  };
}

+ (FSLPromise<NSArray *> * (^)(dispatch_queue_t, NSArray *))allOn {
  return ^(dispatch_queue_t queue, NSArray<FSLPromise *> *promises) {
    return [self onQueue:queue all:promises];
  };
}

@end
