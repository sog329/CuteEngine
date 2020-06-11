//
// Created by Jack on 2015/11/12 0012.
//

#include "PlatformHelper.h"
#include "../util/TimeHelper.h"
#include <string>

using std::string;

#ifdef __ANDROID__

JavaVM *PlatformHelper::mPtJavaVm = NULL;

// CuteEngine
static const char *mJCuteObjName = "com/sunshine/engine/util/reflex/Engine";

static const char *mJRequestBmpName = "requestBmp";
static const char *mJRequestBmpPara = "(IILjava/lang/String;Ljava/lang/String;II)V";
jmethodID PlatformHelper::mJRequestBmpId = NULL;

jclass PlatformHelper::mJCuteObj = NULL;

static const char *mJRequestRenderName = "requestRender";
static const char *mJRequestRenderPara = "(I)V";
jmethodID PlatformHelper::mJRequestRenderId = NULL;

static const char *mJOnClickName = "onClick";
static const char *mJOnClickPara = "(IILjava/lang/String;)V";
jmethodID PlatformHelper::mJOnClickId = NULL;

static const char *mJOnLoadNextPageDataName = "onLoadNextPageData";
static const char *mJOnLoadNextPageDataPara = "(II)V";
jmethodID PlatformHelper::mJOnLoadNextPageDataId = NULL;

// BoneEngine
jclass PlatformHelper::mJBoneObj = NULL;
static const char *mJBoneObjName = "com/sunshine/engine/util/reflex/BoneAnim";
static const char *mJOnDrawName = "onDraw";
static const char *mJOnDrawPara = "(IIIIIIIIIFII)V";
jmethodID PlatformHelper::mJOnDrawId = NULL;

void PlatformHelper::init(JavaVM *vm) {
    mPtJavaVm = vm;
    if (mPtJavaVm != NULL) {
        int status;
        JNIEnv *env = NULL;
        bool isAttach = false;
        status = mPtJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status != JNI_OK) {
            status = mPtJavaVm->AttachCurrentThread(&env, NULL);
            if (status < 0) {
                return;
            }
            isAttach = true;
        }
        mJCuteObj = (jclass) env->NewGlobalRef(env->FindClass(mJCuteObjName));
        if (mJCuteObj != NULL) {
            mJRequestBmpId = env->GetStaticMethodID(mJCuteObj, mJRequestBmpName, mJRequestBmpPara);
            mJRequestRenderId = env->GetStaticMethodID(mJCuteObj, mJRequestRenderName, mJRequestRenderPara);
            mJOnClickId = env->GetStaticMethodID(mJCuteObj, mJOnClickName, mJOnClickPara);
            mJOnLoadNextPageDataId = env->GetStaticMethodID(mJCuteObj, mJOnLoadNextPageDataName, mJOnLoadNextPageDataPara);
        }
        mJBoneObj = (jclass) env->NewGlobalRef(env->FindClass(mJBoneObjName));
        if (mJBoneObj != NULL) {
            mJOnDrawId = env->GetStaticMethodID(mJBoneObj, mJOnDrawName, mJOnDrawPara);
        }
        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (isAttach) {
            mPtJavaVm->DetachCurrentThread();
        }
    }
}

BmpHelper *PlatformHelper::getBmpData(JNIEnv *env, jobject bmp) {
    BmpHelper *hp = new BmpHelper();
    long time = TimeHelper::getCurrentTime();
    if (bmp != NULL && env != NULL) {
        void *ptSrc = NULL;
        AndroidBitmapInfo info;
        int n = AndroidBitmap_getInfo(env, bmp, &info);
        if (n >= 0) {
            AndroidBitmap_lockPixels(env, bmp, &ptSrc);
            int w = info.width;
            int h = info.height;
            int len = w * h * 4;
            void *ptDest = malloc(len);
            memcpy(ptDest, ptSrc, len);
            hp->setSize(info.width, info.height);
            hp->setData(ptDest);
            AndroidBitmap_unlockPixels(env, bmp);
        }
    } else {
        show("getBmpData has NULL");
    }
    env->DeleteLocalRef(bmp);
    show("PlatformHelper::getBmpData cost: %d ms", (TimeHelper::getCurrentTime() - time));
    return hp;
}


void PlatformHelper::requestBmp(int viewId, int layerId, const char *itemId, const char *url, int w, int h) {
    show("Jni PlatformHelper::requestBmp");
    if (mPtJavaVm != NULL) {
        int status;
        JNIEnv *env = NULL;
        bool isAttach = false;
        status = mPtJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status != JNI_OK) {
            status = mPtJavaVm->AttachCurrentThread(&env, NULL);
            if (status < 0) {
                return;
            }
            isAttach = true;
        }
        if (mJCuteObj != NULL && mJRequestBmpId != NULL) {
            jstring jUrl = env->NewStringUTF(url);
            jstring jItemId = env->NewStringUTF(itemId);
            env->CallStaticVoidMethod(mJCuteObj, mJRequestBmpId, viewId, layerId, jItemId, jUrl, w, h);
            env->DeleteLocalRef(jUrl);
            env->DeleteLocalRef(jItemId);
        }
        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (isAttach) {
            mPtJavaVm->DetachCurrentThread();
        }
    }
}

void PlatformHelper::onClick(int viewId, int dataIndex, const char *dataId) {
    show("PlatformHelper::onClick");
    if (mPtJavaVm != NULL) {
        int status;
        JNIEnv *env = NULL;
        bool isAttach = false;
        status = mPtJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status != JNI_OK) {
            status = mPtJavaVm->AttachCurrentThread(&env, NULL);
            if (status < 0) {
                return;
            }
            isAttach = true;
        }
        if (mJCuteObj != NULL && mJOnClickId != NULL) {
            jstring jDataId = env->NewStringUTF(dataId);
            env->CallStaticVoidMethod(mJCuteObj, mJOnClickId, viewId, dataIndex, jDataId);
            env->DeleteLocalRef(jDataId);
        }
        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (isAttach) {
            mPtJavaVm->DetachCurrentThread();
        }
    }
}


void PlatformHelper::onLoadNextPageData(int viewId, int layerId) {
    show("PlatformHelper::onClick");
    if (mPtJavaVm != NULL) {
        int status;
        JNIEnv *env = NULL;
        bool isAttach = false;
        status = mPtJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status != JNI_OK) {
            status = mPtJavaVm->AttachCurrentThread(&env, NULL);
            if (status < 0) {
                return;
            }
            isAttach = true;
        }
        if (mJCuteObj != NULL && mJOnLoadNextPageDataId != NULL) {
            env->CallStaticVoidMethod(mJCuteObj, mJOnLoadNextPageDataId, viewId, layerId);
        }
        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (isAttach) {
            mPtJavaVm->DetachCurrentThread();
        }
    }
}

void PlatformHelper::requestRender(int viewId) {
    if (mPtJavaVm != NULL) {
        int status;
        JNIEnv *env = NULL;
        bool isAttach = false;
        status = mPtJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status != JNI_OK) {
            status = mPtJavaVm->AttachCurrentThread(&env, NULL);
            if (status < 0) {
                return;
            }
            isAttach = true;
        }
        if (mJCuteObj != NULL && mJRequestRenderId != NULL) {
            env->CallStaticVoidMethod(mJCuteObj, mJRequestRenderId, viewId);
        }
        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (isAttach) {
            mPtJavaVm->DetachCurrentThread();
        }
    }
}


void PlatformHelper::onDraw(int mPicLeft, int mPicTop, int mPicRight, int mPicBottom, int mActualLeft, int mActualTop, int mActualRight, int mActualBottom, int mAlpha, float mRotateDegree, int mActualRotateX, int mActualRotateY) {
    if (mPtJavaVm != NULL) {
        int status;
        JNIEnv *env = NULL;
        bool isAttach = false;
        status = mPtJavaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status != JNI_OK) {
            status = mPtJavaVm->AttachCurrentThread(&env, NULL);
            if (status < 0) {
                return;
            }
            isAttach = true;
        }
        if (mJBoneObj != NULL && mJOnDrawId != NULL) {
            env->CallStaticVoidMethod(mJBoneObj, mJOnDrawId, mPicLeft, mPicTop, mPicRight, mPicBottom, mActualLeft, mActualTop, mActualRight, mActualBottom, mAlpha, mRotateDegree, mActualRotateX, mActualRotateY);
        }
        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        if (isAttach) {
            mPtJavaVm->DetachCurrentThread();
        }
    }
}

#else

BmpHelper *PlatformHelper::getBmpData(void* ptSrc, int w, int h){
    BmpHelper* ptBmpHelper = NULL;
    if(ptSrc!=NULL&&w>0&&h>0){
        ptBmpHelper = new BmpHelper();
        int len = w * h * 4;
        void *ptDest = malloc(len);
        memcpy(ptDest, ptSrc, len);
        ptBmpHelper->setData(ptDest);
        ptBmpHelper->setSize(w, h);
    }
    return ptBmpHelper;
}

void PlatformHelper::requestBmp(int viewId, int layerId, const char *itemId, const char *url, int w, int h){
    show("OC PlatformHelper::requestBmp");
    OcHelper::requestBmp(viewId, layerId, itemId, url, w, h);
}

void PlatformHelper::requestRender(int viewId){
//    show("requestRender");
}

void PlatformHelper::onClick(int viewId, int dataIndex, const char *dataId){
    OcHelper::onClick(viewId, dataIndex, dataId);
}

void PlatformHelper::onLoadNextPageData(int viewId, int layerId){
    OcHelper::onLoadNextPageData(viewId, layerId);
}

#endif