//
// Created by Jack on 15/11/20.
//

#include "ILyListView.h"
#include "../util/TouchHelper.h"
#include "../platform/PlatformHelper.h"
#include "../util/TimeHelper.h"

using std::min;

ILyListView::ILyListView(int viewId, int threadNum) : ILayer(viewId, threadNum) {
    mItemHeightK = .75;

    mItemPaddingK = 0;
    mItemPadding = 0;

    mVisibleItemNum = 0;
    mPreloadItemNum = 0;

    mFirstItemDataIndex = 0;
    mItemHeight = 0;
    mScrollY = 0;

    mItemContentWidth = 0;
    mItemContentHeight = 0;
    mItemCurrentY = 0;

    mHasMoreData = true;
    mIsGettingData = false;
    ptAddMore = new Pic(getPtPicLoader(1));
    setAddPageMode(string(), .2);
    mAddMoreHeight = 0;

    ptDefaultPic = new Pic(getPtPicLoader(1));
    mDefaultPicUrl = string();

    mMaxScrollY = 0;

    // 增加小图预览
    new PicLoader(viewId, getId(), 2, &mLstPicLoader);
}

ILyListView::~ILyListView() {
    delete ptAddMore;
    ptAddMore = NULL;
    delete ptDefaultPic;
    ptDefaultPic = NULL;
}

void ILyListView::initItemSize(float itemHeightK, float paddingK, int visibleItemNum, int preloadItemNum) {
    mItemHeightK = itemHeightK;
    mItemPaddingK = paddingK;
    mVisibleItemNum = visibleItemNum;
    mPreloadItemNum = preloadItemNum;
    if (mPreloadItemNum < 1) {
        mPreloadItemNum = 1;
    }
    mFirstItemDataIndex = -mPreloadItemNum;
    int total = mVisibleItemNum + 2 * mPreloadItemNum;
    for (int i = 0; i < total; i++) {
        Item *pt = getItemObject();
        mLstItem.push_back(pt);
    }
}

void ILyListView::onSizeChange(int w, int h) {
    mItemPadding = mItemPaddingK * min(w, h);
    mItemHeight = w * mItemHeightK;
    mItemContentWidth = w - 2 * mItemPadding;
    mItemContentHeight = mItemHeight - mItemPadding;
    mAddMoreHeight = mItemContentWidth * mAddMoreK;
    mSpringHelper.onSizeChange(w, h);
    updateMaxScrollY();
    for (int i = 0; i < (int) mLstItem.size(); i++) {
        Item *ptItem = mLstItem[i];
        int smallPicH = mItemContentWidth / 4;
        ptItem->mLstPic[0]->setSize(smallPicH * 8, smallPicH * 4); // 图片尺寸
        ptItem->mLstPic[1]->setSize(mItemContentWidth, mItemContentHeight / 7); // 文字尺寸
        ptItem->mLstPic[2]->setSize(smallPicH * 2, smallPicH); // 图片尺寸
    }
    ptAddMore->setSize(mItemContentWidth, mAddMoreHeight);
    ptDefaultPic->setSize(mItemContentWidth, mItemContentHeight);
    ILayer::onSizeChange(w, h);
}

bool ILyListView::setItemPosition(int itemIndex) {
    int dataIndex = mFirstItemDataIndex + itemIndex;
    if (dataIndex < mLstData.size()) {
        if (mPreloadItemNum - 1 <= itemIndex && itemIndex < mPreloadItemNum + mVisibleItemNum + 1) {
            mItemCurrentY = mHeight - (mFirstItemDataIndex + itemIndex + 1) * mItemHeight + mScrollY + mSpringHelper.getOffset();
            if (mItemCurrentY > mHeight || mItemCurrentY + mItemContentHeight <= 0) {
                return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool ILyListView::onDraw() {
    bool needShow = false;
    if (mHasMoreData) {
        if ((int) mLstData.size() == 0) {
            mItemCurrentY = (mHeight + mAddMoreHeight) / 2;
        } else {
            int tmp = mAddMoreHeight + mItemPadding;
            if (mItemCurrentY > tmp) {
                mItemCurrentY -= (mItemCurrentY - tmp) / 2;
            }
        }
        if (mItemCurrentY > 0) {
            mItemCurrentY -= mAddMoreHeight;
            if (!mIsGettingData) {
                NextPageInfo *ptInfo = new NextPageInfo();
                ptInfo->viewId = mViewId;
                ptInfo->layerId = getId();
                pthread_t thread;
                if (pthread_create(&thread, NULL, onLoadNextPageData, ptInfo) == 0) {
                    mIsGettingData = true;
                } else {
                    mIsGettingData = false;
                    delete ptInfo;
                }
            }
            needShow = true;
        }
    }
    return needShow;
}

void *ILyListView::onLoadNextPageData(void *obj) {
    if (obj != NULL) {
        NextPageInfo *ptInfo = (NextPageInfo *) obj;
        PlatformHelper::onLoadNextPageData(ptInfo->viewId, ptInfo->layerId);
        delete ptInfo;
    }
    return NULL;
}

bool ILyListView::judgeTouchEvent() {
    bool isMove = false;
    TouchHelper::Result *ptResult = TouchHelper::getPtResult(mViewId);
    if (ptResult != NULL) {
        int disY = ptResult->disY;
        mIsFling = ptResult->isFling;
        if (disY != 0) {
            scrollBy(disY);
        }
        if (mIsFling && ptResult->speedX == 0 && ptResult->speedY == 0) {
            TouchHelper::stopFling(mViewId);
        } else if (mIsFling && ptResult->speedY < 0 && mSpringHelper.getOffset() < 0) { // 当在弹性位置时
            TouchHelper::stopFling(mViewId);
        }
        int clickX = ptResult->clickX;
        int clickY = ptResult->clickY;
        if (clickX != TouchHelper::NONE && clickY != TouchHelper::NONE) {
            if (mItemHeight != 0) {
                int dataIndex = (mScrollY + clickY) / mItemHeight;
                if (dataIndex < mLstData.size()) {
                    string id = getDataId(dataIndex);
                    TouchHelper::performClick(mViewId, dataIndex, id);
                }
            }
        }
        mSpringHelper.moveToIdle(false);
    } else {
        mSpringHelper.moveToIdle(true);
    }
    return isMove;
}

int ILyListView::getFirstVisibleItemDataIndex(int scrollY) {
    int index = 0;
    if (mItemHeight > 0) {
        index = ceil(1.0 * scrollY / mItemHeight);
    }
    index = min(index, (int) (mLstData.size() - 1));
    index = index < 0 ? 0 : index;
    return index;
}

/**
 * >0: 向下
 */
void ILyListView::scrollBy(int distance) {
    int firstVisibleItemIndex = getFirstVisibleItemDataIndex(mScrollY);
    mScrollY = mSpringHelper.setScrollY(mScrollY, mScrollY + distance, mMaxScrollY, mViewId, mHeight);
    int moveItemNum = getFirstVisibleItemDataIndex(mScrollY) - firstVisibleItemIndex;
    mFirstItemDataIndex += moveItemNum;
    if (moveItemNum > 0) {
        for (int i = 0; i < moveItemNum; i++) {
            Item *ptItem = mLstItem[0];
            mLstItem.pop_front();
            mLstItem.push_back(ptItem);
        }
        updateItem();
    } else if (moveItemNum < 0) {
        moveItemNum = -moveItemNum;
        for (int i = 0; i < moveItemNum; i++) {
            Item *ptItem = mLstItem[mLstItem.size() - 1];
            mLstItem.pop_back();
            mLstItem.push_front(ptItem);
        }
        updateItem();
    }
}

void ILyListView::updateMaxScrollY() {
    int tmp = mMaxScrollY;
    mMaxScrollY = (int) (mLstData.size()) * mItemHeight - mHeight + mItemPadding;
    if (mHasMoreData) {
        mMaxScrollY += mAddMoreHeight;
    }
    if (mMaxScrollY < 0) {
        mMaxScrollY = 0;
    }
    if (tmp != mMaxScrollY) {
        scrollBy(0);
    }
}

void ILyListView::onPause(bool inGLThread) {
    ILayer::onPause(inGLThread);
    ptAddMore->onPause(mViewId, inGLThread);
    ptDefaultPic->onPause(mViewId, inGLThread);
}

void ILyListView::updateItem() {
    ptAddMore->setUrl(Item::getItemTvId("loading"), mAddMoreContent);
    ptDefaultPic->setUrl(Item::getItemIvId("default"), mDefaultPicUrl);
    updateMaxScrollY();
}

void ILyListView::setAddPageMode(string content, float heightK) {
    mAddMoreContent = content;
    mAddMoreK = heightK;
}

void ILyListView::requestNextPageDataEnd(bool hasMoreData) {
    mIsGettingData = false;
    mHasMoreData = hasMoreData;
    updateMaxScrollY();
}

void ILyListView::setDefaultPicUrl(string picUrl) {
    if (mDefaultPicUrl != picUrl) {
        mDefaultPicUrl = picUrl;
        ptDefaultPic->setUrl(Item::getItemIvId("default"), mDefaultPicUrl);
    }
}