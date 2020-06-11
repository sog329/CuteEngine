//
// Created by Jack on 2015/11/17 0017.
//

#include "Pic.h"
#include "../util/Gl2Helper.h"
#include "../platform/PlatformHelper.h"

using CuteEngine::Gl2Helper;

Pic::Pic(PicLoader *ptPicLoader) {
    mTextureId = GL_NONE;
    mPtBmpHelper = NULL;
    mPtPicLoader = ptPicLoader;
    clearUrl();
    setSize(0, 0);
}

Pic::~Pic() {
    show("~PicItem");
    delete mPtBmpHelper;
    mPtBmpHelper = NULL;
    mPtPicLoader = NULL; // 外部统一析构
}

string Pic::getId() {
    return mId;
}

void Pic::setSize(int w, int h) {
    if (w != 0 && h != 0) {
        int max = w > h ? w : h;
        float scale = (float) h / w;
        bool wIsMax = max == w;
        const float K = 1.2;
        // 仅处理 512, 1024, 2048, 4096，即在K的范围内，以给定的目标值为准，节省显存
        if (max > 512 && max < (int) (512 * K)) {
            max = 512;
        } else if (max > 1024 && max < (int) (1024 * K)) {
            max = 1024;
        } else if (max > 2048 && max < (int) (2048 * K)) {
            max = 2048;
        } else if (max > 4096) {
            max = 4096;
        }
        if (wIsMax) {
            w = max;
            h = (int) (w * scale);
        } else {
            h = max;
            w = (int) (h / scale);
        }
    }
    mWidth = w;
    mHeight = h;
}

void Pic::clearUrl() {
    delete mPtBmpHelper;
    mPtBmpHelper = NULL;
    mIsTextureReady = false;
    mAnimHelper.clear();
    string oldId = mId;
    mId = string();
    mUrl = string();
    if (mPtPicLoader != NULL && !oldId.empty()) {
        mPtPicLoader->loadPic(oldId, mId, mUrl, mWidth, mHeight);
    }
    mNeedCheckTexture = false;
}

bool Pic::setUrl(string dataId, string url) {
    bool change = false;
    if (mWidth != 0 && mHeight != 0 && mPtPicLoader != NULL) {
        if (mUrl != url || dataId != mId) {
            delete mPtBmpHelper;
            mPtBmpHelper = NULL;
            mIsTextureReady = false;
            mPtPicLoader->loadPic(mId, dataId, url, mWidth, mHeight);
            mAnimHelper.clear();
            change = true;
        }
        mId = dataId;
        mUrl = url;
    }
    return change;
}

void Pic::resetUrl(string url) {
    mUrl = url;
}

string Pic::getUrl() {
    return mUrl;
}

bool Pic::setBmp(string id, BmpHelper *ptBmpHelper) {
    bool hasSet = false;
    if (mId == id) {
        hasSet = true;
        delete mPtBmpHelper;
        mPtBmpHelper = ptBmpHelper;
        if (ptBmpHelper == NULL) {
            if (!mId.empty()) {
                mNeedCheckTexture = true;
            }
            mIsTextureReady = false;
        } else {
            show("_Engine.requestBmp - %s", mId.c_str());
        }
    }
    return hasSet;
}

void Pic::onPause(int viewId, bool inGLThread) {
    setBmp(mId, NULL);
    if (inGLThread && mTextureId != GL_NONE) {
        Gl2Helper::freeTextureId(viewId, &mTextureId);
    }
}

GLuint Pic::getTextureId() {
    return mTextureId;
}

void Pic::setTextureId(GLuint textureId) {
    mTextureId = textureId;
}

bool Pic::initTexture(int viewId, PicLoader *ptPicItem) {
    bool buildTexture = false;
    // 当Pause后为true，onDrawFrame第一次会检查纹理
    if (mNeedCheckTexture) {
        mNeedCheckTexture = false;
        if (!mId.empty()) {
            // Miui7.0的Android6.0对这个api支持有问题
            if (!Gl2Helper::isTextureReady(mTextureId)) {
                mIsTextureReady = false;
                ptPicItem->loadPic(mId, mId, mUrl, mWidth, mHeight);
            } else {
                mIsTextureReady = true;
            }
        }
    } else {
        if (mPtBmpHelper != NULL) {
            buildTexture = true;
            Gl2Helper::initTexture(viewId, &mTextureId, mPtBmpHelper);
            delete mPtBmpHelper;
            mPtBmpHelper = NULL;
            mIsTextureReady = true;
            show("_Engine_Pic::initTexture done: %d_%s", mTextureId, mUrl.c_str());
        }
    }
    return buildTexture;
}
