//
// Created by Jack on 15/12/4.
//

#include "Stage.h"
#include "../platform/PlatformHelper.h"
#include "../../app/bone/PgBoneAnim.h"
#include "StageHelper.h"

Stage::Stage(string id) {
    mId = id;
    mActualWidth = 1080;
    mActualHeight = 1860;
//    mPaddingLeft = 0;
//    mPaddingTop = 0;

    mDesignWidth = 990;
    mDesignHeight = 1280;

    mLayoutMode = LayoutModeMatchY;
    mStageScale = 1;
    mStageLeft = 0;
    mStageTop = 0;
}

Stage::~Stage() {

}

void Stage::onViewSizeChange(int w, int h, int left, int top) {
    mActualWidth = w;
    mActualHeight = h;
//    mPaddingLeft = left;
//    mPaddingTop = top;
    resizeStage();
}

void Stage::setDesignSize(int w, int h) {
    mDesignWidth = w;
    mDesignHeight = h;
}

void Stage::resizeStage() {
    if (mActualWidth > 0 && mActualHeight > 0 && mDesignWidth > 0 && mActualHeight > 0) {
        if (mLayoutMode == LayoutModeMatchY) {
            mStageScale = (float) mActualHeight / mDesignHeight;
            mStageLeft = (mActualWidth - mDesignWidth * mStageScale) / 2;// + mPaddingLeft;
            mStageTop = 0;
        }
    } else {
        mStageScale = 0;
    }
}

void Stage::onDraw(float percent, PgBoneAnim *ptProgram) {
    Actor *ptActor = NULL;
    if (mLstActor.size() > 0) {
        ptActor = mLstActor[0];
        ptActor->onDraw(percent, mStageScale, mStageLeft, mStageTop, mActualWidth, mActualHeight, ptProgram);
    }
}

void Stage::addActor(Actor *ptActor) {
    if (ptActor != NULL) {
        mLstActor.push_back(ptActor);
    }
}

Actor *Stage::getLastActor() {
    Actor *ptActor = NULL;
    if (mLstActor.size() > 0) {
        ptActor = mLstActor.back();
    }
    return ptActor;
}

string Stage::getId() {
    return mId;
}