//
// Created by Jack on 2016/2/13 0013.
//

#include "SpringHelper.h"
#include "../platform/PlatformHelper.h"
#include "../util/TimeHelper.h"
#include "../util/TouchHelper.h"

SpringHelper::SpringHelper() {
    mOffsetPercent = 0;
    mMaxOffset = 0;
    mOffset = 0;
    mLastTime = 0;
    mType = Spring;
}

SpringHelper::~SpringHelper() {
}

void SpringHelper::onSizeChange(int w, int h) {
    if (mType == Spring) {
        mMaxOffset = h / 4;
        updateOffset();
    }
}

int SpringHelper::getOffset() {
    int offset = 0;
    if (mType == Spring) {
        offset = (int) (mMaxOffset * mOffsetPercent);
    }
    return offset;
}

void SpringHelper::updateOffset() {
    if (mType == Spring) {
        if (mOffsetPercent != 0) {
            if (mOffsetPercent < 0) {
                float tmp = -mOffsetPercent;
                tmp = 1 - tmp;
                tmp = 1 - tmp * tmp;
                mOffset = -mMaxOffset * tmp;
            } else {
                float tmp = mOffsetPercent;
                tmp = 1 - tmp;
                tmp = 1 - tmp * tmp;
                mOffset = mMaxOffset * tmp;
            }
        } else {
            if (mOffset != 0) {
                mOffset = 0;
            }
        }
    }
}

void SpringHelper::moveToIdle(bool canMove) {
    if (mType != None) {
        if (mOffsetPercent != 0) {
            if (canMove) {
                int runTime = 0;
                if (mLastTime != 0) {
                    runTime = (int) (TimeHelper::getCurrentTime() - mLastTime);
                    if (runTime < 0) {
                        mLastTime = 0;
                    }
                } else {
                    mSpeedFactor = MAX * (mOffsetPercent > 0 ? mOffsetPercent : -mOffsetPercent);
                }
                mLastTime = TimeHelper::getCurrentTime();
                float speed = SPEED;
                if (mOffsetPercent > 0) {
                    speed += SPEED * mSpeedFactor * (mOffsetPercent);
                } else {
                    speed += SPEED * mSpeedFactor * (-mOffsetPercent);
                }
                float percent = runTime * speed;
                if (mOffsetPercent > 0) {
                    mOffsetPercent -= percent;
                    if (mOffsetPercent < 0) {
                        mOffsetPercent = 0;
                        mLastTime = 0;
                    }
                } else if (mOffsetPercent < 0) {
                    mOffsetPercent += percent;
                    if (mOffsetPercent > 0) {
                        mOffsetPercent = 0;
                        mLastTime = 0;
                    }
                }
            } else {
                mLastTime = 0;
            }
        } else {
            mLastTime = 0;
        }
        if (canMove) {
            updateOffset();
        }
    }
}

int SpringHelper::setScrollY(int scrollFrom, int scrollTo, int maxScrollY, int viewId, int viewHeight) {
    if (mType != None) {
        if (mOffsetPercent == 0) {
            if (scrollTo < 0) { // 在顶部往下滑
                float p = (float) scrollTo / viewHeight;
                mOffsetPercent = p;
                if (mOffsetPercent < -1) {
                    mOffsetPercent = -1;
                }
            } else if (scrollTo > maxScrollY) { // 在低部往上滑
                float p = (float) (scrollTo - maxScrollY) / viewHeight;
                mOffsetPercent = p;
                if (mOffsetPercent > 1) {
                    mOffsetPercent = 1;
                }
            }
        } else {
            if (scrollTo != scrollFrom) {
                float p = (float) (scrollTo - scrollFrom) / viewHeight;
                bool isDown = mOffsetPercent > 0;
                mOffsetPercent += p;
                if (isDown == (mOffsetPercent > 0)) { // 判断滑动系数在改变之后是相同方向
                    if (mOffsetPercent > 1) {
                        mOffsetPercent = 1;
                        TouchHelper::stopFling(viewId);
                    } else if (mOffsetPercent < -1) {
                        mOffsetPercent = -1;
                        TouchHelper::stopFling(viewId);
                    }
                    if (mOffsetPercent < 0) {
                        scrollTo = scrollFrom;
                    } else if (mOffsetPercent > 0) {
                        scrollTo = scrollFrom;
                    }
                } else {
                    mOffsetPercent = 0;
                }
            }
        }
        updateOffset();
        // 当滑动系数>0，但目标位置<最大位置时，清除滑动系数，指向目标位置。
        if (mOffsetPercent > 0 && scrollTo + mOffset < maxScrollY) {
            show("**** _scrollFrom=%d, scrollTo=%d, mOffset=%d, maxScrollY=%d", scrollFrom, scrollTo, mOffset, maxScrollY);
            scrollTo = scrollTo + mOffset;
            mOffsetPercent = 0;
            mOffset = 0;
            TouchHelper::stopFling(viewId);
        }
    }
    if (scrollTo < 0) {
        scrollTo = 0;
        switch (mType) {
            case Spring:
                if (mOffsetPercent == -1) {
                    TouchHelper::stopFling(viewId);
                }
                break;
            case None:
                break;
        }
    } else if (scrollTo > maxScrollY) {
        scrollTo = maxScrollY;
        switch (mType) {
            case Spring:
                if (mOffsetPercent == 1) {
                    TouchHelper::stopFling(viewId);
                }
                break;
            case None:
                break;
        }
    }
    return scrollTo;
}