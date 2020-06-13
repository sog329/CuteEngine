//
// Created by Jack on 2015/11/17 0017.
//

#include "PicLoader.h"
#include "../platform/PlatformHelper.h"
#include "../view/ViewManager.h"

PicLoader::PicLoader(int viewId, int layerId, int threadNum, deque<PicLoader *> *ptLstPicLoader) {
    mViewId = viewId;
    mLayerId = layerId;
    mId = (int) ptLstPicLoader->size();
    ptLstPicLoader->push_back(this);

    show("PicLoader.mId=%d", mId);

    mLstThread.clear();
    for (int i = 0; i < threadNum; i++) {
        mLstThread.push_back(false);
    }
}

PicLoader::~PicLoader() {
    for (int i = 0; i < mLstTask.size(); i++) {
        delete mLstTask[i];
    }
    mLstTask.clear();
    show("PicLoader[%d]::~PicLoader()", mId);
}

void PicLoader::loadPic(string oldDataId, string newDataId, string url, int w, int h) {
    PicLoader::Task *ptTask = new PicLoader::Task();
    ptTask->itemId = newDataId;
    ptTask->url = url;
    ptTask->suggestWidth = w;
    ptTask->suggestHeight = h;
    if (oldDataId != newDataId) {
        for (int i = 0; i < mLstTask.size(); i++) {
            if (oldDataId == mLstTask[i]->itemId) {
                mLstTask[i]->url = url;
                mLstTask[i]->itemId = newDataId;
                mLstTask[i]->suggestWidth = w;
                mLstTask[i]->suggestHeight = h;
                delete ptTask;
                ptTask = NULL;
                break;
            }
        }
    }
    if (ptTask != NULL && !newDataId.empty()) {
        mLstTask.push_back(ptTask);
        for (int i = 0; i < mLstThread.size(); i++) {
            if (!mLstThread[i]) {
                ThreadInfo *ptThreadInfo = new ThreadInfo();
                ptThreadInfo->viewId = mViewId;
                ptThreadInfo->layerId = mLayerId;
                ptThreadInfo->loaderId = mId;
                ptThreadInfo->threadId = i;

                pthread_t thread;
                if (pthread_create(&thread, NULL, loadPic, ptThreadInfo) == 0) {
                    mLstThread[i] = true;
                    break;
                } else {
                    delete ptThreadInfo;
                }
            }
        }
    }
}

PicLoader::Task *PicLoader::getTask() {
    Task *ptTask = NULL;
    if (!mLstTask.empty()) {
        ptTask = mLstTask[0];
        mLstTask.pop_front();
    }
    return ptTask;
}

void PicLoader::sortTask(string dataId) {
    Task *ptTask = NULL;
    for (int i = 0; i < mLstTask.size(); i++) {
        if (mLstTask[i]->itemId == dataId) {
            ptTask = mLstTask[i];
            mLstTask.erase(mLstTask.begin() + i);
            break;
        }
    }
    if (ptTask != NULL) {
        mLstTask.push_front(ptTask);
    }
}

void *PicLoader::loadPic(void *obj) {
    if (obj != NULL) {
        ThreadInfo *ptThreadInfo = (ThreadInfo *) obj;
        Task *ptTask = ViewManager::getTask(ptThreadInfo);
        while (ptTask != NULL) {
            if (!ptTask->itemId.empty()) {
                if (ptTask->isResume) {
                    PlatformHelper::requestBmp(ptThreadInfo->viewId, ptThreadInfo->layerId, ptTask->itemId.c_str(), ptTask->url.c_str(), ptTask->suggestWidth, ptTask->suggestHeight);
                } else {
                    ViewManager::onItemGetBmp(ptThreadInfo->viewId, ptThreadInfo->layerId, ptTask->itemId, NULL);
                }
            }
            delete ptTask;
            ptTask = ViewManager::getTask(ptThreadInfo);
        }
        ViewManager::releaseThread(ptThreadInfo->viewId, ptThreadInfo->layerId, ptThreadInfo->loaderId, ptThreadInfo->threadId);
        delete ptThreadInfo;
    }
    return NULL;
}

void PicLoader::releaseThread(int threadIndex) {
    if (threadIndex < mLstThread.size()) {
        mLstThread[threadIndex] = false;
    }
}

