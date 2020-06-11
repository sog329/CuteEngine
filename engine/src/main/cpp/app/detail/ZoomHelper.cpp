//
// Created by Jack on 15/12/21.
//

#include "ZoomHelper.h"
#include "../../base/util/TimeHelper.h"
#include "../../base/boneAnim/Interpolator.h"
#include "../../base/platform/PlatformHelper.h"
#include <stdlib.h>

ZoomHelper::ZoomHelper() {
    mZoom = 1;
    mZoomFrom = mZoom;
    mZoomChange = 0;
    mStartTime = NONE;
}

void ZoomHelper::moveNextLevel() {
    if (mZoomChange == 0) {
        if (mZoom >= 1 && mZoom < 2) {
            mZoomFrom = mZoom;
            mZoomChange = 2 - mZoom;
        } else if (mZoom >= 2 && mZoom < 3) {
            mZoomFrom = mZoom;
            mZoomChange = 3 - mZoom;
        } else {
            mZoomFrom = 3;
            mZoomChange = -2;
        }
        mStartTime = NONE;
        show("ZoomHelper::moveNextLevel");
    }
}

void ZoomHelper::changeZoom(float scale) {
    show("ZoomHelper::changeZoom: scale=%f", scale);
    if (scale == 1) {
        mBaseZoom = mZoom;
        mZoomChange = 0;
        show("ZoomHelper::changeZoom: mBaseZoom=%f", mBaseZoom);
    } else if (scale == 0) {
        mBaseZoom = 0;
        show("ZoomHelper::changeZoom: mBaseZoom=%f", mBaseZoom);
    } else {
        float tmp = mBaseZoom * scale;
        if (tmp < 1) {
            tmp = 1;
        } else if (tmp > 3) {
            tmp = 3;
        }
        mZoomChange = tmp - mZoom;
        mZoomFrom = mZoom;
        mStartTime = NOW;
        show("ZoomHelper::changeZoom: mBaseZoom=%f;   mZoomChange=%f", mBaseZoom, mZoomChange);
    }

}

float ZoomHelper::getZoom() {
    return mZoom;
}

void ZoomHelper::run(long drawTime) {
    if (mZoomChange != 0) {
        float percent = 1;
        if (mStartTime == NONE) {
            mStartTime = drawTime;
            percent = 0;
        } else if (mStartTime != NOW) {
            int runTime = abs((int) (drawTime - mStartTime));
            percent = 1.0 * runTime / DURATION;
        }
        if (percent >= 1) {
            mZoom = mZoomFrom + mZoomChange;
            mZoomChange = 0;
        } else {
            percent = Interpolator::getPercent(Interpolator::Decelerate, percent);
            mZoom = mZoomFrom + percent * mZoomChange;
        }
    }
}

bool ZoomHelper::isZooming() {
    return mZoomChange != 0;
}