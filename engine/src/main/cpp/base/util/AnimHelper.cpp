//
// Created by Jack on 15/11/23.
//

#include <stdlib.h>
#include "AnimHelper.h"
#include "TimeHelper.h"

using CuteEngine::AnimHelper;

AnimHelper::AnimHelper() {
    clear();
}

void AnimHelper::setAlphaAnim(float from, float to, int dutation) {
    mAlphaFrom = from;
    mAlphaChange = to - from;
    mStartTime = TimeHelper::getCurrentTime();
    mDuration = dutation;
}

void AnimHelper::setScaleAnim(float from, float to, int dutation) {
    mScaleFrom = from;
    mScaleChange = to - from;
    mStartTime = TimeHelper::getCurrentTime();
    mDuration = dutation;
}

//void AnimHelper::setValueAnim(float from, float to, int dutation) {
//    mValueFrom = from;
//    mValueChange = to - from;
//    mStartTime = TimeHelper::getCurrentTime();
//    mDuration = dutation;
//}

bool AnimHelper::run(long drawTime) {
    bool hasRun = false;
    if (mDuration > 0) {
        hasRun = true;
        int runTime = abs((int) (drawTime - mStartTime));
        float percent = 1.0 * runTime / mDuration;
        if (percent > 1) {
            clear();
        } else {
            percent = 1 - (percent - 1) * (percent - 1);
            mAlpha = mAlphaFrom + percent * mAlphaChange;
            mScale = mScaleFrom + percent * mScaleChange;
//            mValue = mValueFrom + percent * mValueChange;
        }
    }
    return hasRun;
}

float AnimHelper::getAlpha() {
    return mAlpha;
}

float AnimHelper::getScale() {
    return mScale;
}

//float AnimHelper::getValue() {
//    return mValue;
//}

void AnimHelper::clear() {
    setAlphaAnim(1, 1, 0);
    setScaleAnim(1, 1, 0);
//    setValueAnim(1, 1, 0);
}