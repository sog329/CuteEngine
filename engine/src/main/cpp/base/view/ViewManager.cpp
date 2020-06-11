//
// Created by Jack on 15/11/11.
//

#include "../util/Gl2Helper.h"
#include <map>
#include "../util/TimeHelper.h"
#include "../../app/AppHelper.h"
#include "ViewManager.h"
#include "../platform/PlatformHelper.h"
#include "View.h"
#include "../util/TouchHelper.h"
#include "../util/SensorHelper.h"

using std::string;

std::map<int, View *> mMap;

ThreadLock ViewManager::mLock;
deque<int> ViewManager::mLstDrawTime;
bool ViewManager::mShowFps = false;
long ViewManager::mLastDrawTime = 0;

void ViewManager::onCreate(int id) {
    show("%d: onCreate", id);
    View *ptView = new View(id);
    mLock.lock();
    std::map<int, View *>::iterator it = mMap.find(id);
    if (it != mMap.end()) {
        mMap.erase(it);
    }
    mMap.insert(std::pair<int, View *>(id, ptView));
    mLock.unlock();
}


void ViewManager::onResume(int id) {
    show("%d: onResume", id);
    mLock.lock();
    std::map<int, View *>::iterator it;
    it = mMap.find(id);
    if (it != mMap.end()) {
        View *ptView = it->second;
        ptView->onResume();
    }
    mLock.unlock();
}


void ViewManager::onPause(int id, bool inGLThread) {
    show("%d: onPause", id);
    mLock.lock();
    std::map<int, View *>::iterator it = mMap.find(id);
    if (it != mMap.end()) {
        View *ptView = it->second;
        ptView->onPause(inGLThread);
    }
    mLock.unlock();
}

void ViewManager::onDestroy(int id) {
    show("%d: onDestroy", id);
    mLock.lock();
    std::map<int, View *>::iterator it = mMap.find(id);
    if (it != mMap.end()) {
        View *ptView = it->second;
        mMap.erase(it);
        delete ptView;
    }
    mLock.unlock();
}

void ViewManager::onSurfaceCreated(int id) {
    show("%d: onSurfaceCreated", id);
    mLock.lock();
    std::map<int, View *>::iterator it = mMap.find(id);
    if (it != mMap.end()) {
        View *ptView = it->second;
        if (ptView != NULL) {
            ptView->initProgram();
        }
    }
    mLock.unlock();
}

void ViewManager::onSurfaceChanged(int id, int w, int h) {
    show("%d: onSurfaceChanged, w=%d, h=%d", id, w, h);
    mLock.lock();
    std::map<int, View *>::iterator it = mMap.find(id);
    if (it != mMap.end()) {
        View *ptView = it->second;
        if (ptView != NULL) {
            ptView->onSizeChange(w, h);
        }
    }
    mLock.unlock();
}

void ViewManager::onDrawFrame(int id) {
    long drawTime = TimeHelper::getCurrentTime();
    mLock.lock();
    std::map<int, View *>::iterator it = mMap.find(id);
    if (it != mMap.end()) {
        View *ptView = it->second;
        if (ptView != NULL) {
            ptView->onDraw(drawTime);
        }
    }
    mLock.unlock();
    if (mShowFps) {
        if (mLastDrawTime != 0) {
            int costTime = (int) (drawTime - mLastDrawTime);
            mLstDrawTime.push_back(costTime);
            int total = (int) mLstDrawTime.size();
            if (total > 300) {
                float sum = 0;
                for (int i = 0; i < mLstDrawTime.size(); i++) {
                    sum += mLstDrawTime[i];
                }
                mLstDrawTime.clear();
                if (sum != 0) {
                    float fps = 1000 / (sum / total);
                    show("CuteEngine Fps: %f/s\n", fps);
                }
            }
        }
    }
    mLastDrawTime = drawTime;
}

void ViewManager::lock(bool lock) {
    if (lock) {
        mLock.lock();
    } else {
        mLock.unlock();
    }
}

View *ViewManager::getView(int viewId) {
    View *ptView = NULL;
    std::map<int, View *>::iterator it = mMap.find(viewId);
    if (it != mMap.end()) {
        ptView = it->second;
    }
    return ptView;
}

PicLoader::Task *ViewManager::getTask(PicLoader::ThreadInfo *ptThreadInfo) {
    PicLoader::Task *ptTask = NULL;
    if (ptThreadInfo != NULL) {
        mLock.lock();
        View *ptView = getView(ptThreadInfo->viewId);
        if (ptView != NULL) {
            ILayer *ptLayer = ptView->getLayer(ptThreadInfo->layerId);
            if (ptLayer != NULL) {
                ptTask = ptLayer->getTask(ptThreadInfo->loaderId);
                if (ptTask != NULL) {
                    ptTask->isResume = ptView->isResume();
                }
            }
        }
        mLock.unlock();
    }
    if (ptTask != NULL) {
        show("ViewManager::getTask: %s, %s", ptTask->itemId.c_str(), ptTask->url.c_str());
    }
    return ptTask;
}

void ViewManager::releaseThread(int viewId, int layerId, int loaderId, int threadIndex) {
    mLock.lock();
    ILayer *ptLayer = NULL;
    View *ptView = getView(viewId);
    if (ptView != NULL) {
        ptLayer = ptView->getLayer(layerId);
    }
    if (ptLayer != NULL) {
        ptLayer->releaseThread(loaderId, threadIndex);
    }
    mLock.unlock();
}


void ViewManager::onItemGetBmp(int viewId, int layerId, string itemId, BmpHelper *ptBmpHelper) {
    mLock.lock();
    ILayer *ptLayer = NULL;
    View *ptView = getView(viewId);
    if (ptView != NULL) {
        ptLayer = ptView->getLayer(layerId);
    }
    bool inLayer = false;
    if (ptLayer != NULL) {
        if (ptView->isResume()) {
            inLayer = ptLayer->onItemGetBmp(itemId, ptBmpHelper);
        } else {
            inLayer = ptLayer->onItemGetBmp(itemId, NULL);
        }
    }
    if (!inLayer) {
        delete ptBmpHelper;
    }
    mLock.unlock();
}