//
//  SOMotionDetecter.h
//  MotionDetection
//
// The MIT License (MIT)
//
// Created by : arturdev
// Copyright (c) 2014 SocialObjects Software. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

#import <Foundation/Foundation.h>
#import "SOLocationManager.h"
#import <CoreMotion/CoreMotion.h>

@class SOMotionDetector;
typedef enum
{
  MotionTypeNotMoving = 1,
  MotionTypeWalking,
  MotionTypeCycling,
  MotionTypeRunning,
  MotionTypeAutomotive
} SOMotionType;

@protocol SOMotionDetectorDelegate <NSObject>

@optional
- (void)motionDetector:(SOMotionDetector *)motionDetector motionTypeChanged:(SOMotionType)motionType;
- (void)motionDetector:(SOMotionDetector *)motionDetector locationChanged:(CLLocation *)location;
- (void)motionDetector:(SOMotionDetector *)motionDetector accelerationChanged:(CMAcceleration)acceleration;
- (void)motionDetector:(SOMotionDetector *)motionDetector locationWasPaused:(BOOL)changed;

@end

@interface SOMotionDetector : NSObject

#pragma mark - Singleton
+ (SOMotionDetector *)sharedInstance;

#pragma mark - Properties
@property (weak, nonatomic) id<SOMotionDetectorDelegate> delegate DEPRECATED_MSG_ATTRIBUTE(" Use blocks instead");

@property (copy) void (^motionTypeChangedBlock) (SOMotionType motionType);
@property (copy) void (^locationChangedBlock) (CLLocation *location);
@property (copy) void (^accelerationChangedBlock) (CMAcceleration acceleration);
@property (copy) void (^locationWasPausedBlock) (BOOL changed);

@property (nonatomic, readonly) SOMotionType motionType;
@property (nonatomic, readonly) double currentSpeed;
@property (nonatomic, readonly) CMAcceleration acceleration;
@property (nonatomic, readonly) BOOL isShaking;


#pragma mark - Methods
- (void)startDetection;
- (void)stopDetection;

#pragma mark - Customization Methods

/**
 *@param speed  The minimum speed value less than which will be considered as not moving state
 */
- (void)setMinimumSpeed:(CGFloat)speed;

/**
 *@param speed  The maximum speed value more than which will be considered as running state
 */
- (void)setMaximumWalkingSpeed:(CGFloat)speed;

/**
 *@param speed  The maximum speed value more than which will be considered as automotive state
 */
- (void)setMaximumRunningSpeed:(CGFloat)speed;

/**
 *@param acceleration  The minimum acceleration value less than which will be considered as non shaking state
 */
- (void)setMinimumRunningAcceleration:(CGFloat)acceleration;


@end
