//
// Created by Jack on 15/12/4.
//

#include "BoneAnim.h"
#include "Interpolator.h"
#include "Bone.h"
#include "../platform/PlatformHelper.h"

BoneAnim::BoneAnim() {
    setRunPercent(0, 1, true);
    setInterpolator(Interpolator::Normal);
    setRect(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    setRotate(0, 0, 0, 0);
    setAlpha(255, 255);
}

BoneAnim::~BoneAnim() {

}

void BoneAnim::setRunPercent(float startPercent, float endPercent, bool isShow) {
    mStartPercent = startPercent;
    mEndPercent = endPercent;
    mDurationPercent = endPercent - startPercent;
    mIsShow = isShow;
}

bool BoneAnim::isShow() {
    return mIsShow;
}

void BoneAnim::setInterpolator(int interpolator) {
    mInterpolator = interpolator;
}

void BoneAnim::setRect(float fromScaleX, float fromScaleY, float toScaleX, float toScaleY, int fromCenterX, int fromCenterY, int toCenterX, int toCenterY, int picW, int picH) {
    int fromW = (int) (picW * fromScaleX);
    int fromH = (int) (picH * fromScaleY);
    int toW = (int) (picW * toScaleX);
    int toH = (int) (picH * toScaleY);
    mLeftFrom = fromCenterX - fromW / 2;
    mLeftChange = (toCenterX - toW / 2) - mLeftFrom;
    mTopFrom = fromCenterY - fromH / 2;
    mTopChange = (toCenterY - toH / 2) - mTopFrom;
    mRightFrom = fromCenterX + fromW / 2;
    mRightChange = (toCenterX + toW / 2) - mRightFrom;
    mBottomFrom = fromCenterY + fromH / 2;
    mBottomChange = (toCenterY + toH / 2) - mBottomFrom;
}

void BoneAnim::setAlpha(int from, int to) {
    mAlphaFrom = from;
    mAlphaChange = to - from;
}

void BoneAnim::setRotate(float from, float to, int rotateX, int rotateY) {
    mRotateFrom = from;
    mRotateChange = to - from;
    mRotateX = rotateX;
    mRotateY = rotateY;
}

void BoneAnim::run2d(void *pt, float percent) {
    Bone *ptBone = (Bone *) pt;
    if (mDurationPercent > 0) {
        percent = (percent - mStartPercent) / mDurationPercent;
        percent = Interpolator::getPercent(mInterpolator, percent);

        int left = mLeftFrom + (int) (percent * mLeftChange);
        int top = mTopFrom + (int) (percent * mTopChange);
        int right = mRightFrom + (int) (percent * mRightChange);
        int bottom = mBottomFrom + (int) (percent * mBottomChange);
        ptBone->setRect(left, top, right, bottom);

        float rotate = mRotateFrom + percent * mRotateChange;
        float rotateX = left + mRotateX;
        float rotateY = top + mRotateY;
        ptBone->setRotate(rotate, rotateX, rotateY);

        int alpha = mAlphaFrom + (int) (percent * mAlphaChange);
        ptBone->setAlpha(alpha);
    }
}

bool BoneAnim::isInAnim(float percent, bool isLast) {
    bool b = false;
    if (isLast) {
        if (percent >= mStartPercent && percent <= mEndPercent) {
            b = true;
        }
    } else {
        if (percent >= mStartPercent && percent < mEndPercent) {
            b = true;
        }
    }
    return b;
}