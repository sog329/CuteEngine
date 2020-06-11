//
// Created by Jack on 15/11/21.
//

#include "TouchHelper.h"
#include "TimeHelper.h"
#include "../platform/PlatformHelper.h"
#include <stdlib.h>

int TouchHelper::mId = 0;
int TouchHelper::mDisX = 0;
int TouchHelper::mDisY = 0;
float TouchHelper::mSpeedX = 0;
float TouchHelper::mSpeedY = 0;
long TouchHelper::mSpeedRecordTime = 0;
float TouchHelper::mAcceleration = 10;
int TouchHelper::mClickX = NONE;
int TouchHelper::mClickY = NONE;
bool TouchHelper::mIsDoubleClick = false;
float TouchHelper::mScale = NONE;

ThreadLock TouchHelper::mTouchLock;
TouchHelper::Result TouchHelper::mResult;

void TouchHelper::onClick(int id, int x, int y) {
    onFling(id, 0, 0);
    mTouchLock.lock();
    mId = id;
    mClickX = x;
    mClickY = y;
    mIsDoubleClick = false;
    mTouchLock.unlock();
    //    show("onClick");
}

void TouchHelper::onDoubleClick(int id) {
    onFling(id, 0, 0);
    mTouchLock.lock();
    mId = id;
    mIsDoubleClick = true;
    mTouchLock.unlock();
    show("onDoubleClick");
}

void TouchHelper::onZoom(int id, float scale) {
    mTouchLock.lock();
    mId = id;
    mIsDoubleClick = false;
    mScale = scale;
    mTouchLock.unlock();
    show("TouchHelper::onZoom scale=%f", scale);
}

void TouchHelper::onDown(int id, bool isDown) {
    mTouchLock.lock();
    if (isDown) {
        mId = id;
        mDisX = 0;
        mDisY = 0;
        mSpeedX = 0;
        mSpeedY = 0;
        mClickX = NONE;
        mClickY = NONE;
    } else {
        mId = NONE;
        show("Cancle");
    }
    mTouchLock.unlock();
}

void TouchHelper::onScroll(int id, int disX, int disY) {
    mTouchLock.lock();
    mId = id;
    mDisX += disX;
    mDisY += disY;
    mSpeedX = 0;
    mSpeedY = 0;
    mClickX = NONE;
    mClickY = NONE;
    mIsDoubleClick = false;
    mTouchLock.unlock();
    //    show("onScroll: disY=%d\n", disY);
}

void TouchHelper::onFling(int id, float speedX, float speedY) {
    mTouchLock.lock();
    mId = id;
    mSpeedX = speedX;
    mSpeedY = speedY;
    mSpeedRecordTime = TimeHelper::getCurrentTime();
    mDisX = 0;
    mDisY = 0;
    mClickX = NONE;
    mClickY = NONE;
    mIsDoubleClick = false;
    mTouchLock.unlock();
    //    show("onFling: speedY=%f\n", speedY);
}

void TouchHelper::stopFling(int id) {
    mTouchLock.lock();
    if (mId == id) {
        mSpeedX = 0;
        mSpeedY = 0;
        mId = NONE;
    }
    mTouchLock.unlock();
}

float TouchHelper::getNewSpeed(float speed, int runTime) {
    int speedNow = 0;
    if (speed != 0) {
        float changeSpeed = mAcceleration * runTime;
        if (speed > 0) {
            speedNow = speed - changeSpeed;
            if (speedNow < 0) {
                speedNow = 0;
            }
        } else if (speed < 0) {
            speedNow = speed + changeSpeed;
            if (speedNow > 0) {
                speedNow = 0;
            }
        }
    }
    return speedNow;
}

void TouchHelper::buildTouchResult(int scendId) {
    mTouchLock.lock();
    mResult.viewId = scendId;
    if (mResult.viewId == mId) {
        if (mSpeedX == 0 && mSpeedY == 0) {
            mResult.disX = mDisX;
            mResult.disY = mDisY;
            mResult.isFling = false;
            mDisX = 0;
            mDisY = 0;
        } else {
            long nowTime = TimeHelper::getCurrentTime();
            int runTime = abs((int) (nowTime - mSpeedRecordTime));
            mSpeedX = getNewSpeed(mSpeedX, runTime);
            mSpeedY = getNewSpeed(mSpeedY, runTime);
            mResult.isFling = true;
            mResult.disX = mSpeedX * runTime / 1000;
            mResult.disY = mSpeedY * runTime / 1000;
            mSpeedRecordTime = nowTime;
        }
        mResult.clickX = mClickX;
        mResult.clickY = mClickY;
        mResult.isDoubleClick = mIsDoubleClick;
        mResult.scale = mScale;
        mResult.speedX = mSpeedX;
        mResult.speedY = mSpeedY;
    } else {
        mResult.viewId = NONE;
        mResult.disX = 0;
        mResult.disY = 0;
        mResult.isFling = false;
        mResult.clickX = NONE;
        mResult.clickY = NONE;
        mResult.isDoubleClick = false;
        mResult.scale = NONE;
        mResult.speedX = mSpeedX;
        mResult.speedY = mSpeedY;
    }
    mClickX = NONE;
    mClickY = NONE;
    mIsDoubleClick = false;
    mScale = NONE;
    mTouchLock.unlock();
}

TouchHelper::Result *TouchHelper::getPtResult(int viewId) {
    Result *ptResult = NULL;
    if (mResult.viewId == viewId) {
        ptResult = &mResult;
    }
    return ptResult;
}

void TouchHelper::performClick(int viewId, int dataIndex, string dataId) {
    show("performClick");
    onDown(viewId, false);
    ClickInfo *ptInfo = new ClickInfo();
    ptInfo->viewId = viewId;
    ptInfo->dataIndex = dataIndex;
    ptInfo->dataId = dataId;
    pthread_t thread;
    if (pthread_create(&thread, NULL, performClickInThread, ptInfo) != 0) {
        delete ptInfo;
    }
}

void *TouchHelper::performClickInThread(void *obj) {
    if (obj != NULL) {
        show("performClickInThread");
        ClickInfo *ptInfo = (ClickInfo *) obj;
        PlatformHelper::onClick(ptInfo->viewId, ptInfo->dataIndex, ptInfo->dataId.c_str());
        delete ptInfo;
    }
    return NULL;
}