//
// Created by Jack on 2015/11/15 0015.
//

#include "AppHelper.h"
#include "../base/util/TimeHelper.h"
#include "../base/view/View.h"
#include "../base/view/ViewManager.h"
#include "bone/LyBoneAnim.h"
#include "detail/LyBall.h"
#include "vr/LyVrBall.h"
#include "list/LyListBall.h"

int AppHelper::loadListView(int viewId) {
    int layerId = 0;
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        ptView->isDirtyRender(false);
        ptView->clear();
        ptView->setBgColor(1, 1, 1);
        LyListBall *ptLayer = new LyListBall(ptView->getId(), 3);
        ptView->addLayer(ptLayer);
        layerId = ptLayer->getId();
    }
    ViewManager::lock(false);
    return layerId;
}

void AppHelper::clearListViewData(int viewId, int layerId) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        LyListBall *ptLayer = (LyListBall *) ptView->getLayer(layerId);
        if (ptLayer != NULL) {
            ptLayer->clearData();
        }
    }
    ViewManager::lock(false);
}

void AppHelper::addListViewData(int viewId, int layerId, string dataId, string picId, string picUrl, string textId, string text) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        LyListBall *ptLayer = (LyListBall *) ptView->getLayer(layerId);
        if (ptLayer != NULL) {
            LyListBall::Data *ptData = new LyListBall::Data();
            ptData->mDataId = dataId;
            ptData->mPicId = picId;
            ptData->mPicUrl = picUrl;
            ptData->mNameStr = text;
            ptData->mNameTvId = textId;
            ptLayer->addData(ptData);
        }
    }
    ViewManager::lock(false);
}

void AppHelper::requestNextPageDataEnd(int viewId, int layerId, bool hasMoreData) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        LyListBall *ptLayer = (LyListBall *) ptView->getLayer(layerId);
        if (ptLayer != NULL) {
            ptLayer->requestNextPageDataEnd(hasMoreData);
        }
    }
    ViewManager::lock(false);
}

void AppHelper::setAddPageMode(int viewId, int layerId, string content, float heightK) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        LyListBall *ptLayer = (LyListBall *) ptView->getLayer(layerId);
        if (ptLayer != NULL) {
            ptLayer->setAddPageMode(content, heightK);
        }
    }
    ViewManager::lock(false);
}


void AppHelper::setListViewDefaultPic(int viewId, int layerId, string picUrl) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        LyListBall *ptLayer = (LyListBall *) ptView->getLayer(layerId);
        if (ptLayer != NULL) {
            ptLayer->setDefaultPicUrl(picUrl);
        }
    }
    ViewManager::lock(false);
}

//void AppHelper::setBallView(int viewId, string url) {
//    ViewManager::lock(true);
//    View *ptView = ViewManager::getView(viewId);
//    if (ptView != NULL) {
//        ptView->clear();
//        LyBall *ptLayer = new LyBall(ptView->getId(), 1, );
//        ptLayer->clearData();
//        LyBall::Data *ptData = new LyBall::Data();
//        ptData->picUrl = url;
//        ptLayer->addData(ptData);
//        ptView->addLayer(ptLayer);
//    }
//    ViewManager::lock(false);
//}

void AppHelper::setVrView(int viewId, int tileLevel, string picId, string url) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        ptView->clear();
        LyVrBall *ptLayer = new LyVrBall(ptView->getId(), 1);
        ptLayer->setTileLevel(tileLevel);
        LyVrBall::Data *ptData = new LyVrBall::Data();
        ptData->picUrl = url;
        ptData->picId = picId;
        ptLayer->addData(ptData);
        ptView->addLayer(ptLayer);
    }
    ViewManager::lock(false);
}

void AppHelper::setTileBallView(int viewId, int tileLevel, string picId, string url, int fromX, int offsetX, int fromY, int offsetY) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        ptView->clear();
        LyBall *ptLayer = new LyBall(ptView->getId(), 2, fromX, offsetX, fromY, offsetY);
        ptLayer->setTileLevel(tileLevel);
        LyBall::Data *ptData = new LyBall::Data();
        ptData->picUrl = url;
        ptData->picId = picId;
        ptLayer->addData(ptData);
        ptView->addLayer(ptLayer);
    }
    ViewManager::lock(false);
}

void AppHelper::setBoneAnimView(int viewId, string id, string xmlUrl, string picUrl) {
    ViewManager::lock(true);
    View *ptView = ViewManager::getView(viewId);
    if (ptView != NULL) {
        ptView->clear();
        LyBoneAnim *ptLayer = new LyBoneAnim(ptView->getId());
        ptView->setBgColor(1, 1, 1);
        LyBoneAnim::Data *ptData = new LyBoneAnim::Data();
        ptData->id = id;
        ptData->xmlUrl = xmlUrl;
        ptData->picUrl = picUrl;
        ptLayer->clearData();
        ptLayer->addData(ptData);
        ptView->addLayer(ptLayer);
    }
    ViewManager::lock(false);
}