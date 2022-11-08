//
// Created by Jack on 2015/11/10 0010.
//

#include "View.h"
#include "../util/Gl2Helper.h"
#include "../util/SensorHelper.h"
#include "../util/TouchHelper.h"
#include "../platform/PlatformHelper.h"

using CuteEngine::Gl2Helper;

View::View(int id) {
    mId = id;
    mIsResume = false;
    mBgColor[0] = 0;
    mBgColor[1] = 0;
    mBgColor[2] = 0;
    mWidth = 0;
    mHeight = 0;
    mIsDirtyRender = true;
}

View::~View() {
    for (int i = 0; i < mLstLayer.size(); i++) {
        delete mLstLayer[i];
        mLstLayer[i] = NULL;
    }
    mLstLayer.clear();
    mMapTextureId.clear();
}

void View::isDirtyRender(bool isDirtyRender) {
    mIsDirtyRender = isDirtyRender;
}

void View::addLayer(ILayer *layer) {
    if (layer != NULL) {
        mLstLayer.push_back(layer);
    }
}

void View::initProgram() {
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptLayer = mLstLayer[i];
        ptLayer->initProgram();
        ptLayer->mNeedInitProgram = false;
    }
}

void View::onSizeChange(int w, int h) {
    glViewport(0, 0, w, h);
    Gl2Helper::checkGlError("glViewport");
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptLayer = mLstLayer[i];
        ptLayer->onSizeChange(w, h);
        ptLayer->updateItem();
    }
    mWidth = w;
    mHeight = h;
}

void View::clearCanvas() {
    glClearColor(mBgColor[0], mBgColor[1], mBgColor[2], 1);
    Gl2Helper::checkGlError("glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    Gl2Helper::checkGlError("glClear");
}

void View::onDraw(long drawTime) {
    clearCanvas();
    bool needRender = false;
    bool hasBuildSensorResult = false;
    bool hasBuildTouchResult = false;
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptLayer = mLstLayer[i];
        if (ptLayer->mNeedInitProgram) {
            ptLayer->initProgram();
            ptLayer->mNeedInitProgram = false;
            ptLayer->onSizeChange(mWidth, mHeight);
            ptLayer->updateItem();
        }
        if (ptLayer->mIsTouchalbe) {
            if (!hasBuildTouchResult) {
                hasBuildTouchResult = true;
                TouchHelper::buildTouchResult(mId);
            }
            ptLayer->judgeTouchEvent();
        }
        if (!hasBuildSensorResult && ptLayer->mIsUseSensor) {
            SensorHelper::buildCurrentRotationMatrix44();
            hasBuildSensorResult = true;
        }
        ptLayer->checkDataChange();
        needRender = needRender || ptLayer->onDraw(drawTime);
    }
    if (mIsDirtyRender && needRender) {
        PlatformHelper::requestRender(getId());
    }
}

void View::onResume() {
    mIsResume = true;
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptLayer = mLstLayer[i];
        ptLayer->onResume();
    }
}

void View::onPause(bool inGLThread) {
    mIsResume = false;
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptLayer = mLstLayer[i];
        ptLayer->onPause(inGLThread);
    }
}

bool View::isResume() {
    return mIsResume;
}

void View::clear() {
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptLayer = mLstLayer[i];
        delete ptLayer;
    }
    mLstLayer.clear();
}

ILayer *View::getLayer(int id) {
    ILayer *ptLayer = NULL;
    for (int i = 0; i < mLstLayer.size(); i++) {
        ILayer *ptTmp = mLstLayer[i];
        if (ptTmp->getId() == id) {
            ptLayer = ptTmp;
            break;
        }
    }
    return ptLayer;
}

int View::getId() {
    return mId;
}

void View::setBgColor(float r, float g, float b) {
    mBgColor[0] = r;
    mBgColor[1] = g;
    mBgColor[2] = b;
}

bool View::addTextureId(GLuint textureId) {
    bool canAdd = false;
    map<GLuint, View *>::iterator it = mMapTextureId.find(textureId);
    if (it != mMapTextureId.end()) {
        canAdd = false;
        show("*Gl2Helper::buildTextureId[%d] %d is using", mId, textureId);
    } else {
        canAdd = true;
        show("*Gl2Helper::buildTextureId[%d] %d is build", mId, textureId);
        mMapTextureId.insert(std::pair<GLuint, View *>(textureId, this));
    }
    return canAdd;
}

void View::removeTextureId(GLuint textureId) {
    map<GLuint, View *>::iterator it = mMapTextureId.find(textureId);
    if (it != mMapTextureId.end()) {
        mMapTextureId.erase(it);
        show("*Gl2Helper::freeTextureId[%d] %d is free", mId, textureId);
    }
}