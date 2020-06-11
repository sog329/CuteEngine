//
// Created by Jack on 2015/11/12 0012.
//

#ifndef BASE_OLD_JNIHELPER_H
#define BASE_OLD_JNIHELPER_H


#include <math.h>
#include "../util/BmpHelper.h"
#include <string>

#ifdef __ANDROID__

#include <jni.h>
#include <GLES2/gl2.h>
#include <android/bitmap.h>
#include <malloc.h>


#ifdef IS_DEBUG
#include <android/log.h>
    #define  LOG_TAG    "____"
    #define  show(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
    #define  showError(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
    #define  show(...)
    #define  showError(...)
#endif

using std::string;

class PlatformHelper {
private:
    static JavaVM *mPtJavaVm;
    // CuteEngine
    static jclass mJCuteObj;
    static jmethodID mJRequestBmpId;
    static jmethodID mJRequestRenderId;
    static jmethodID mJOnClickId;
    static jmethodID mJOnLoadNextPageDataId;
    // BoneEngine
    static jclass mJBoneObj;
    static jmethodID mJOnDrawId;

public:
    static void init(JavaVM *vm);

    // CuteEngine
    static BmpHelper *getBmpData(JNIEnv *env, jobject bmp);

    /**
     * 引擎在PicLoader的线程池中调用的获取图片函数接口
     * itemId: 形式为 type_id_url
     *      type: iv/iv[?]，tv/tv[?]，stage
     *      id: 控件对应的id，比如loading、name等
     *      url: 图片url地址/文字内容
     */
    static void requestBmp(int viewId, int layerId, const char *itemId, const char *url, int w, int h);

    static void requestRender(int viewId);

    static void onClick(int viewId, int dataIndex, const char *dataId);

    static void onLoadNextPageData(int viewId, int layerId);

    // BoneEngine
    static void onDraw(int mPicLeft, int mPicTop, int mPicWidth, int mPicHeight, int mActualLeft, int mActualRight, int mActualTop, int mActualBottom, int mAlpha, float mRotateDegree, int mActualRotateX, int mActualRotateY);
};

#else

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include "OcHelper.h"

#ifdef IS_DEBUG
    #define  show(...)  {printf(__VA_ARGS__);putchar('\n');}
    #define  showError(...)  {printf(__VA_ARGS__);putchar('\n');}
#else
    #define  show(...)
    #define  showError(...)
#endif

class PlatformHelper {

public:

    static BmpHelper *getBmpData(void* ptSrc, int w, int h);
    
    static void requestBmp(int viewId, int layerId, const char *itemId, const char *url, int w, int h);
    
    static void requestRender(int viewId);
    
    static void onClick(int viewId, int dataIndex, const char *dataId);
    
    static void onLoadNextPageData(int viewId, int layerId);

};
#endif


#endif //BASE_OLD_JNIHELPER_H
