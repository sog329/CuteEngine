//
// Created by Jack on 2015/11/14 0014.
//

#include "LyListBall.h"
#include "../../base/util/MatrixHelper.h"
#include "../../base/util/SensorHelper.h"
#include "../../base/view/ViewManager.h"

LyListBall::LyListBall(int viewId, int threadNum) : ILyListView(viewId, threadNum) {
    mIsTouchalbe = true;
    mIsUseSensor = true;
    initItemSize(.63, .01, 3, 15);
    mPgText.isAlpha(true);
}

LyListBall::~LyListBall() {
    show("~LyListBall");
}

Item *LyListBall::getItemObject() {
    Item *ptItem = new Item();
    // 背景图
    PgBall::DrawInfo *ptIv = new PgBall::DrawInfo(getPtPicLoader(0), 0, 360, 90, 180);
    MatrixHelper::setRotateM(ptIv->getMatrixCurrentExtra(), 90, 1, 0, 0);
    ptItem->mLstPic.push_back(ptIv);
    // 文字
    Pic *ptTv = new Pic(getPtPicLoader(1));
    ptItem->mLstPic.push_back(ptTv);
    // 小图
    Pic *ptSmallIv = new Pic(getPtPicLoader(2));
    ptItem->mLstPic.push_back(ptSmallIv);
    return ptItem;
}

bool LyListBall::onDraw(long drawTime) {
    bool hasInitTexture = false; // 单次渲染线程中指初始化1次纹理
    for (int i = 0; i < mLstItem.size(); i++) {
        if (setItemPosition(i)) {
            deque<Pic *> lstPic = mLstItem[i]->mLstPic;
            if (lstPic.size() == 3) {
                glViewport(mItemPadding, mItemCurrentY, mItemContentWidth, mItemContentHeight);
                // 背景图
                PgBall::DrawInfo *ptIv = (PgBall::DrawInfo *) lstPic[0];
                Pic *ptSmallIv = lstPic[2];
                if (mIsUseSensor) {
                    MatrixHelper::copyMatrix(ptIv->getMatrixCurrent(), SensorHelper::getCurrentRotationMatrix44());
                } else {
                    MatrixHelper::setIdentityM(ptIv->getMatrixCurrent());
                }
//                if (!mIsFling) {
                if (!hasInitTexture) {
                    // 当缩略图加载完成，则开始加载正常图片
                    if (ptSmallIv->initTexture(mViewId, getPtPicLoader(2))) {
                        string smallIvId = ptSmallIv->getId();
                        string ivId = smallIvId.substr(0, smallIvId.size() - 12) + "}";
                        ptIv->setUrl(ivId, ptSmallIv->getUrl());
                        ptIv->mAnimHelper.clear();
                        ptIv->mAnimHelper.setAlphaAnim(.5, 1, 500);
                        ptIv->mAnimHelper.setScaleAnim(1.2, 1, 500);
                    }
                    if (ptIv->initTexture(mViewId, getPtPicLoader(0))) {
                        hasInitTexture = true;
                    }
                }
//                }
                if (ptSmallIv->mIsTextureReady) {
                    if (ptIv->mIsTextureReady) {
                        mPgBall.onDraw(ptIv, drawTime);
                    } else {
                        getPtPicLoader(0)->sortTask(ptIv->getId());
                        int textureId = ptIv->getTextureId();
                        ptIv->setTextureId(ptSmallIv->getTextureId());
                        mPgBall.onDraw(ptIv, drawTime);
                        ptIv->setTextureId(textureId);
                    }
                } else {
                    getPtPicLoader(2)->sortTask(ptSmallIv->getId());
//                    mPgRect.onDraw(ptIv, drawTime);
                    ptDefaultPic->initTexture(mViewId, getPtPicLoader(1));
                    if (ptDefaultPic->mIsTextureReady) {
                        mPgText.setPosition(0, 0, 1, 1);
                        mPgText.onDraw(ptDefaultPic, drawTime);
                    }
                }
                // 文字
                Pic *ptTv = lstPic[1];
                ptTv->initTexture(mViewId, getPtPicLoader(1));
                if (ptTv->mIsTextureReady) {
                    mPgText.setPosition(0, 6.0 / 7, 1, 1.0 / 7);
                    mPgText.onDraw(ptTv, drawTime);
                }
            }
        } else {
            // 当格子移动到屏幕外，则清除大图纹理，减少显存消耗。
            deque<Pic *> lstPic = mLstItem[i]->mLstPic;
            if (lstPic.size() == 3) {
                lstPic[0]->onPause(mViewId, true);
            }
        }
    }
    if (ILyListView::onDraw()) {
        ptAddMore->initTexture(mViewId, getPtPicLoader(1));
        if (ptAddMore->mIsTextureReady) {
            glViewport(mItemPadding, mItemCurrentY, mItemContentWidth, mAddMoreHeight);
            mPgText.setPosition(0, 0, 1, 1);
            mPgText.onDraw(ptAddMore, drawTime);
        }
    }
    glViewport(0, 0, mWidth, mHeight);
    return true;
}

void LyListBall::updateItem() {
    for (int i = 0; i < mLstItem.size(); i++) {
        deque<Pic *> lstPic = mLstItem[i]->mLstPic;
        int index = mFirstItemDataIndex + i;
        if (index < 0 || index > mLstData.size() - 1 || 0 == mLstData.size()) {
            lstPic[0]->clearUrl();
            lstPic[1]->clearUrl();
            lstPic[2]->clearUrl();
        } else {
            LyListBall::Data *ptData = (LyListBall::Data *) mLstData[index];
            string tvId = Item::getItemTvId(ptData->mNameTvId, index);
            lstPic[1]->setUrl(tvId, ptData->mNameStr);
            string smallIvId = Item::getItemIvId(ptData->mPicId, index, "\"scale\":\"4\"");
            bool change = lstPic[2]->setUrl(smallIvId, ptData->mPicUrl);
            // 当缩略图设置了新的图片时，清除对应的全尺寸图片的信息，即全尺寸纹理处于等待缩略图加载完成状态
            if (change) {
                lstPic[0]->clearUrl();
            }
        }
    }
    ILyListView::updateItem();
}

void LyListBall::onSizeChange(int w, int h) {
    ILyListView::onSizeChange(w, h);
    mPgBall.onSizeChange(mItemContentWidth, mItemContentHeight);
}

void LyListBall::initProgram() {
    mPgBall.init();
//    mPgRect.init();
    mPgText.init();
}

string LyListBall::getDataId(int index) {
    string id = string();
    if (index < mLstData.size()) {
        Data *ptData = (Data *) mLstData[index];
        id = ptData->mDataId;
    }
    return id;
}

bool LyListBall::onItemGetBmp(string itemId, BmpHelper *ptBmpHelper) {
    bool result = ILayer::onItemGetBmp(itemId, ptBmpHelper);
    if (!result) {
        result = ptAddMore->setBmp(itemId, ptBmpHelper);
    }
    if (!result) {
        result = ptDefaultPic->setBmp(itemId, ptBmpHelper);
    }
    return result;
}