//
// Created by Jack on 15/12/7.
//

#include "LyBoneAnim.h"
#include "../../base/platform/PlatformHelper.h"
#include "../../base/boneAnim/StageHelper.h"
#include "../../base/util/TimeHelper.h"
#include "../../base/view/ILayer.h"

LyBoneAnim::LyBoneAnim(int viewId) : ILayer(viewId, 1) {
    mPtStage = NULL;

    Item *ptItem = new Item();
    PgBoneAnim::DrawInfo *ptDrawInfo = new PgBoneAnim::DrawInfo(getPtPicLoader(0));
    ptDrawInfo->setSize(4096, 4096);
    ptItem->mLstPic.push_back(ptDrawInfo);
    mLstItem.push_back(ptItem);
}

LyBoneAnim::~LyBoneAnim() {
    show("~LyBoneAnim");
    if (mPtStage != NULL) {
        string id = mPtStage->getId();
        StageHelper::stop(id);
        delete mPtStage;
        mPtStage = NULL;
    }
}

bool LyBoneAnim::onDraw(long drawTime) {
    if (mLstData.size() == 1) {
        PgBoneAnim::DrawInfo *ptDrawInfo = (PgBoneAnim::DrawInfo *) mLstItem[0]->mLstPic[0];
        if (ptDrawInfo != NULL && mPtStage != NULL) {
            ptDrawInfo->initTexture(mViewId, getPtPicLoader(0));
            if (ptDrawInfo->mIsTextureReady) {
                mPgBoneAnim.setDrawInfo(ptDrawInfo);
                mPgBoneAnim.startDraw(true);
                string id = mPtStage->getId();
                float percent = StageHelper::getPercent(id);
                mPtStage->onDraw(percent, &mPgBoneAnim);
                mPgBoneAnim.startDraw(false);
                mPgBoneAnim.setDrawInfo(NULL);
            }
        }
    }
    return true;
}

void LyBoneAnim::onSizeChange(int w, int h) {
    ILayer::onSizeChange(w, h);
    mPgBoneAnim.onSizeChange(w, h);
    if (mPtStage != NULL) {
        mPtStage->onViewSizeChange(w, h, 0, 0);
    }
}

void LyBoneAnim::initProgram() {
    mPgBoneAnim.init();
}

void LyBoneAnim::checkDataChange() {
    if (mIsDataChange && mPtStage != NULL) {
        show("LyBoneAnim::checkDataChange() - delete mPtStage");
        string id = mPtStage->getId();
        StageHelper::stop(id);
        delete mPtStage;
        mPtStage = NULL;
    }
    ILayer::checkDataChange();
}

void LyBoneAnim::updateItem() {
    if (mLstData.size() == 1) {
        Data *ptData = (Data *) mLstData[0];
        string url = ptData->id + ";" + ptData->xmlUrl + ";" + ptData->picUrl;
        show("LyBoneAnim::updateItem# url=%s", url.c_str());
        mLstItem[0]->mLstPic[0]->setUrl(Item::getItemStageId(ptData->id), url);
    }
}

bool LyBoneAnim::onItemGetBmp(string itemId, BmpHelper *ptBmpHelper) {
    show("LyBoneAnim::onItemGetBmp# itemId=%s", itemId.c_str());
    bool b = ILayer::onItemGetBmp(itemId, ptBmpHelper);
    if (b) {
        Data *ptData = (Data *) mLstData[0];
        if (mPtStage == NULL) {
            show("LyBoneAnim::onItemGetBmp# 1");
            mPtStage = StageHelper::popStage(ptData->id);
        }
        if (mPtStage != NULL) {
            show("LyBoneAnim::onItemGetBmp# 2");
            mPtStage->onViewSizeChange(mWidth, mHeight, 0, 0);
            mLstItem[0]->mLstPic[0]->resetUrl(ptData->picUrl);
        }
    }
    return b;
}