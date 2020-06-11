//
// Created by Jack on 15/12/4.
//

#include "Bone.h"
#include "../platform/PlatformHelper.h"

Bone::Bone() {
    setPicInfo(0, 0, 0, 0, 0, 0);
    setAlpha(255);
    setRotate(0, 0, 0);
    setRect(0, 0, 0, 0);
    buildActualCoordinate(0, 0, 0);
}

Bone::~Bone() {
    for (int i = 0; i < (int) mLstBoneAnim.size(); i++) {
        delete mLstBoneAnim[i];
    }
    mLstBoneAnim.clear();
}

BoneAnim *Bone::getBoneAnim(float percent) {
    BoneAnim *ptBoneAnim = NULL;
    int total = (int) mLstBoneAnim.size();
    for (int i = 0; i < total; i++) {
        BoneAnim *ptTmp = mLstBoneAnim[i];
        bool isLast = (i == (total - 1));
        if (ptTmp->isInAnim(percent, isLast)) {
            if (ptTmp->isShow()) {
                ptBoneAnim = ptTmp;
                break;
            }
        }
    }
    return ptBoneAnim;
}

void Bone::onDraw(float percent, float scale, int left, int top, int w, int h, PgBoneAnim *ptProgram) {
    BoneAnim *ptBoneAnim = getBoneAnim(percent);
    if (ptBoneAnim != NULL) {
        ptBoneAnim->run2d(this, percent);
        buildActualCoordinate(scale, left, top);
        if (ptProgram == NULL) {
#ifdef __ANDROID__
            PlatformHelper::onDraw(
                    mPicLeft, mPicTop, mPicRight, mPicBottom,
                    mActualLeft, mActualTop, mActualRight, mActualBottom,
                    mAlpha, mRotateDegree, mActualRotateX, mActualRotateY
            );
#endif
        } else {
            float mScaleX = (float) (mActualRight - mActualLeft) / w;
            float mScaleY = (float) (mActualBottom - mActualTop) / h;
            float mCenterX = getGlCoordinateX((mActualRight + mActualLeft) / 2, w);
            float mCenterY = getGlCoordinateY((mActualBottom + mActualTop) / 2, h);
            ptProgram->setTexPosition(mTextureLeft, mTextureWidth, mTextureTop, mTextureHeight);
            ptProgram->setVerPosition(mCenterX, mCenterY, mScaleX, mScaleY);
            ptProgram->setAlpha((float) mAlpha / 255);
            float rotateX = getGlCoordinateX(mActualRotateX, w);
            float rotateY = getGlCoordinateY(mActualRotateY, h);
            ptProgram->setRotate(mRotateDegree, rotateX, rotateY);
            ptProgram->drawSelf(NULL, 0);
        }
    }
}


void Bone::setRect(int left, int top, int right, int bottom) {
    mDesignLeft = left;
    mDesignTop = top;
    mDesignRight = right;
    mDesignBottom = bottom;
}

void Bone::setAlpha(int alpha) {
    mAlpha = alpha;
}

void Bone::setRotate(float rotate, int x, int y) {
    mRotateDegree = rotate;
    mDesignRotateX = x;
    mDesignRotateY = y;
}

void Bone::buildActualCoordinate(float scale, int left, int top) {
    mActualLeft = (int) (mDesignLeft * scale) + left;
    mActualRight = (int) (mDesignRight * scale) + left;
    mActualTop = (int) (mDesignTop * scale) + top;
    mActualBottom = (int) (mDesignBottom * scale) + top;
    mActualRotateX = (int) (mDesignRotateX * scale) + left;
    mActualRotateY = (int) (mDesignRotateY * scale) + top;
}

void Bone::setPicInfo(int left, int top, int w, int h, int totalW, int totalH) {
    mPicLeft = left;
    mPicTop = top;
    mPicRight = left + w;
    mPicBottom = top + h;

    if (totalW == 0 || totalH == 0) {
        mTextureLeft = 0;
        mTextureTop = 0;
        mTextureWidth = 0;
        mTextureHeight = 0;
    } else {
        mTextureLeft = (float) mPicLeft / totalW;
        mTextureTop = (float) mPicTop / totalH;
        mTextureWidth = (float) w / totalW;
        mTextureHeight = (float) h / totalH;
    }
}

void Bone::addBoneAnim(BoneAnim *ptBoneAnim) {
    if (ptBoneAnim != NULL) {
        mLstBoneAnim.push_back(ptBoneAnim);
    }
}

BoneAnim *Bone::getLastBoneAnim() {
    BoneAnim *ptBoneAnim = NULL;
    if (mLstBoneAnim.size() > 0) {
        ptBoneAnim = mLstBoneAnim.back();
    }
    return ptBoneAnim;
}

int Bone::getBonePicWidth() {
    return mPicRight - mPicLeft;
}

int Bone::getBonePicHeight() {
    return mPicBottom - mPicTop;
}


float Bone::getGlCoordinateX(int screenX, int screenW) {
    float x = 0;
    if (screenW > 0) {
        x = (float) screenX * 2 / screenW - 1;
    }
    return x;
}

float Bone::getGlCoordinateY(int screenY, int screenH) {
    float y = 0;
    if (screenH > 0) {
        y = 1 - (float) screenY * 2 / screenH;
    }
    return y;
}

