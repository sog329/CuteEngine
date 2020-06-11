//
// Created by Jack on 15/11/26.
//


#ifndef __ANDROID__

#include "OcHelper.h"
#include <string>
#include "../../Engine.h"
#import <Foundation/Foundation.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import "../util/TimeHelper.h"

IosInterface *OcHelper::mPtCallback = NULL;
int OcHelper::mUsingCount = 0;
ThreadLock OcHelper::mLock;

void OcHelper::setIosCallback(IosInterface * ptCallback) {
    mLock.lock();
    if (mUsingCount == 0) {
        if (mPtCallback == NULL) {
            mPtCallback = ptCallback;
        }
    }
    mLock.unlock();
}

void OcHelper::requestBmp(int viewId, int layerId, const char *itemId, const char *url, int w, int h) {
    mLock.lock();
    if (mPtCallback != NULL) {
        mUsingCount++;
        mLock.unlock();
        mPtCallback->requestBmp(viewId, layerId, itemId, url, w, h);
        mLock.lock();
        mUsingCount--;
    }
    mLock.unlock();
}

void OcHelper::onLoadNextPageData(int viewId, int layerId){
    mLock.lock();
    if (mPtCallback != NULL) {
        mUsingCount++;
        mLock.unlock();
        mPtCallback->onLoadNextPageData(viewId, layerId);
        mLock.lock();
        mUsingCount--;
    }
    mLock.unlock();
}

void OcHelper::onClick(int viewId, int dataIndex, const char *dataId){
    mLock.lock();
    if (mPtCallback != NULL) {
        mUsingCount++;
        mLock.unlock();
        mPtCallback->onClick(viewId, dataIndex, dataId);
        mLock.lock();
        mUsingCount--;
    }
    mLock.unlock();
}

#endif