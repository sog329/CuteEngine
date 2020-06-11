//
// Created by Jack on 2015/11/18 0018.
//

#include "ILayer.h"
#include "../util/Gl2Helper.h"
#include "../platform/PlatformHelper.h"

int ILayer::mSequence = 0;

ILayer::ILayer(int viewId, int threadNum) {
    mSequence++;
    mLayerId = mSequence;
    mViewId = viewId;
    mWidth = 0;
    mHeight = 0;

    new PicLoader(viewId, mLayerId, threadNum, &mLstPicLoader); // picLoader
    new PicLoader(viewId, mLayerId, 1, &mLstPicLoader); // txtLoader

    mWidth = 0;
    mHeight = 0;

    mIsUseSensor = false;
    mIsTouchalbe = false;
    mIsFling = false;
    mIsDataChange = false;
    mNeedInitProgram = true;
}

ILayer::~ILayer() {
    show("~ILayer");
    clearItem();
    clearData();
    for (int i = 0; i < mLstPicLoader.size(); i++) {
        delete mLstPicLoader[i];
    }
    mLstPicLoader.clear();
}

int ILayer::getId() {
    return mLayerId;
}

PicLoader *ILayer::getPtPicLoader(int loaderId) {
    PicLoader *ptPicLoader = NULL;
    if (loaderId < mLstPicLoader.size()) {
        ptPicLoader = mLstPicLoader[loaderId];
    }
    return ptPicLoader;
}

PicLoader::Task *ILayer::getTask(int loaderId) {
    PicLoader *ptPicLoader = getPtPicLoader(loaderId);
    if (ptPicLoader != NULL) {
        return ptPicLoader->getTask();
    } else {
        return NULL;
    }
}

void ILayer::releaseThread(int loaderId, int threadIndex) {
    PicLoader *ptPicLoader = getPtPicLoader(loaderId);
    if (ptPicLoader != NULL) {
        ptPicLoader->releaseThread(threadIndex);
    }
}

bool ILayer::onItemGetBmp(string itemId, BmpHelper *ptBmpHelper) {
    bool hasSet = false;
    for (int i = 0; i < mLstItem.size(); i++) {
        deque<Pic *> lstPic = mLstItem[i]->mLstPic;
        for (int j = 0; j < lstPic.size(); j++) {
            Pic *ptPic = lstPic[j];
            hasSet = ptPic->setBmp(itemId, ptBmpHelper);
            if (hasSet) {
                break;
            }
        }
        if (hasSet) {
            break;
        }
    }
    return hasSet;
}

void ILayer::onResume() {
    show("ILayer::onResume");
}

void ILayer::onPause(bool inGLThread) {
    show("ILayer::onPause");
    for (int i = 0; i < mLstItem.size(); i++) {
        deque<Pic *> lstPic = mLstItem[i]->mLstPic;
        for (int j = 0; j < lstPic.size(); j++) {
            Pic *ptPic = lstPic[j];
            ptPic->onPause(mViewId, inGLThread);
        }
    }
}

void ILayer::onSizeChange(int w, int h) {
    mWidth = w;
    mHeight = h;
    updateItem();
};

void ILayer::clearItem() {
    for (int i = 0; i < mLstItem.size(); i++) {
        delete mLstItem[i];
    }
    mLstItem.clear();
}

void ILayer::clearData() {
    mIsDataChange = true;
    for (int i = 0; i < mLstData.size(); i++) {
        delete mLstData[i];
    }
    mLstData.clear();
    for (int i = 0; i < mLstAdd.size(); i++) {
        delete mLstAdd[i];
    }
    mLstAdd.clear();
}

void ILayer::addData(void *data) {
    mIsDataChange = true;
    mLstAdd.push_back(data);
    show("addData");
}

void ILayer::checkDataChange() {
    if (mIsDataChange) {
        show("ILayer::checkDataChange() mIsDataChange");
        mIsDataChange = false;
        for (int i = 0; i < mLstAdd.size(); i++) {
            mLstData.push_back(mLstAdd[i]);
        }
        mLstAdd.clear();
        updateItem();
    }
}

bool ILayer::judgeTouchEvent() {
    return false;
}