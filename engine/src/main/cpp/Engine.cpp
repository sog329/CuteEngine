//
// Created by Jack on 15/11/25.
//

#include "Engine.h"
#include "base/view/ViewManager.h"
#include "base/util/TouchHelper.h"
#include "base/util/SensorHelper.h"
#include "app/AppHelper.h"
#include "base/boneAnim/StageHelper.h"

// 渲染View的生命周期
void Engine::onCreate(int viewId) {
    ViewManager::onCreate(viewId);
}

void Engine::onResume(int viewId) {
    ViewManager::onResume(viewId);
}

void Engine::onPause(int viewId) {
#ifdef __ANDROID__
    ViewManager::onPause(viewId, false);
#else
    ViewManager::onPause(viewId, true);
#endif
}

void Engine::onDestroy(int viewId) {
    ViewManager::onDestroy(viewId);
}

// openGL线程调用的渲染接口
void Engine::onSurfaceCreated(int viewId) {
    ViewManager::onSurfaceCreated(viewId);
}

void Engine::onSurfaceChanged(int viewId, int w, int h) {
    ViewManager::onSurfaceChanged(viewId, w, h);
}

void Engine::onDrawFrame(int viewId) {
    ViewManager::onDrawFrame(viewId);
}

// 上层传递图片数据给引擎
void Engine::onItemGetBmp(int viewId, int layerId, string itemId, BmpHelper *ptBmpHelper) { // Android
    ViewManager::onItemGetBmp(viewId, layerId, itemId, ptBmpHelper);
}

#ifndef __ANDROID__
void Engine::onItemGetBmp(int viewId, int layerId, const char *itemId, void* ptSrc, int w, int h) { // ios
    BmpHelper *ptBmpHelper = PlatformHelper::getBmpData(ptSrc, w, h);
    if(ptBmpHelper!=NULL){
        string id = string(itemId);
        ViewManager::onItemGetBmp(viewId, layerId, id, ptBmpHelper);
    }
}
#endif

// 对外业务逻辑
int Engine::loadListView(int viewId) {
    return AppHelper::loadListView(viewId);
}

void Engine::clearListViewData(int viewId, int layerId) {
    AppHelper::clearListViewData(viewId, layerId);
}

void Engine::addListViewData(int viewId, int layerId, string dataId, string picId, string picUrl, string textId, string text) {
    AppHelper::addListViewData(viewId, layerId, dataId, picId, picUrl, textId, text);
}

void Engine::requestNextPageDataEnd(int viewId, int layerId, bool hasMoreData) {
    AppHelper::requestNextPageDataEnd(viewId, layerId, hasMoreData);
}

void Engine::setAddPageMode(int viewId, int layerId, string content, float heightK) {
    AppHelper::setAddPageMode(viewId, layerId, content, heightK);
}

void Engine::setListViewDefaultPic(int viewId, int layerId, string picUrl) {
    AppHelper::setListViewDefaultPic(viewId, layerId, picUrl);
}

//void Engine::setBallView(int viewId, string url) {
//    AppHelper::setBallView(viewId, url);
//}

void Engine::setVrView(int viewId, int tileLevel, string picId, string url) {
    AppHelper::setVrView(viewId, tileLevel, picId, url);
}

void Engine::setTileBallView(int viewId, int tileLevel, string picId, string url, int fromX, int offsetX, int fromY, int offsetY) {
    AppHelper::setTileBallView(viewId, tileLevel, picId, url, fromX, offsetX, fromY, offsetY);
}

// 手势
void Engine::onDown(int viewId, bool isDown) {
    TouchHelper::onDown(viewId, isDown);
}

void Engine::onClick(int viewId, int x, int y) {
    TouchHelper::onClick(viewId, x, y);
}

void Engine::onDoubleClick(int viewId) {
    TouchHelper::onDoubleClick(viewId);
}

void Engine::onZoom(int viewId, float scale) {
    TouchHelper::onZoom(viewId, scale);
}

void Engine::onScroll(int viewId, int disX, int disY) {
    TouchHelper::onScroll(viewId, disX, disY);
}

void Engine::onFling(int viewId, float speedX, float speedY) {
    TouchHelper::onFling(viewId, speedX, speedY);
}

// 传感器
void Engine::saveRotateVector(float x, float y, float z, float w) {
    SensorHelper::saveRotateVector(x, y, z, w);
}

// 骨骼动画
void Engine::buildStage(string id) {
    StageHelper::buildStage(id);
}

void Engine::setStageSize(string id, int w, int h) {
    StageHelper::setStageSize(id, w, h);
}

void Engine::buildActor(string id) {
    StageHelper::buildActor(id);
}

void Engine::buildBone(string id) {
    StageHelper::buildBone(id);
}

void Engine::setBonePicInfo(string id, int left, int top, int w, int h, int totalW, int totalH) {
    StageHelper::setBonePicInfo(id, left, top, w, h, totalW, totalH);
}

void Engine::buildBoneAnim(string id) {
    StageHelper::buildBoneAnim(id);
}

void Engine::setBoneAnimRunPercent(string id, float startPercent, float endPercent, bool isShow) {
    StageHelper::setBoneAnimRunPercent(id, startPercent, endPercent, isShow);
}

void Engine::setBoneAnimInterpolator(string id, int interpolator) {
    StageHelper::setBoneAnimInterpolator(id, interpolator);
}

void Engine::setBoneAnimRect(
        string id,
        float fromScaleX, float fromScaleY, float toScaleX, float toScaleY,
        int fromCenterX, int fromCenterY, int toCenterX, int toCenterY) {
    StageHelper::setBoneAnimRect(id, fromScaleX, fromScaleY, toScaleX, toScaleY, fromCenterX, fromCenterY, toCenterX, toCenterY);
}

void Engine::setBoneAnimAlpha(string id, int from, int to) {
    StageHelper::setBoneAnimAlpha(id, from, to);
}

void Engine::setBoneAnimRotate(string id, float from, float to, int rotateX, int rotateY) {
    StageHelper::setBoneAnimRotate(id, from, to, rotateX, rotateY);
}

void Engine::setBoneAnimView(int viewId, string id, string xmlUrl, string picUrl) {
    AppHelper::setBoneAnimView(viewId, id, xmlUrl, picUrl);
}

void Engine::onViewSizeChange(string id, int w, int h, int left, int top) {
    StageHelper::onViewSizeChange(id, w, h, left, top);
}

void Engine::stop(string id) {
    StageHelper::stop(id);
}

void Engine::setPercent(string id, float percent) {
    StageHelper::setPercent(id, percent);
}