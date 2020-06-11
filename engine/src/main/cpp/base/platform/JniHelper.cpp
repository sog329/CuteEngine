//
// Created by Jack on 15/11/24.
//

#ifdef __ANDROID__

#include <jni.h>
#include "PlatformHelper.h"
#include "../../Engine.h"
#include "../boneAnim/StageHelper.h"
#include "../util/SensorHelper.h"

using std::string;
using std::deque;

// CuteEngine
extern "C" {
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onSurfaceChanged(JNIEnv *env, jobject obj, jint id, jint width, jint height);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDrawFrame(JNIEnv *env, jobject obj, jint id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onSurfaceCreated(JNIEnv *env, jobject obj, jint id);

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onCreate(JNIEnv *env, jobject obj, jint id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onResume(JNIEnv *env, jobject obj, jint id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onPause(JNIEnv *env, jobject obj, jint id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDestroy(JNIEnv *env, jobject obj, jint id);

JNIEXPORT int JNICALL Java_com_sunshine_engine_base_Lib_loadListView(JNIEnv *env, jobject obj, jint viewId);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_clearListViewData(JNIEnv *env, jobject obj, jint viewId, jint layerId);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_addListViewData(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring jDataId, jstring picId, jstring picUrl, jstring jTvId, jstring text);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onLoadNextPageData(JNIEnv *env, jobject obj, jint viewId, jint layerId, jboolean hasMoreData);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setAddPageMode(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring content, jfloat heightK);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setListViewDefaultPic(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring picUrl);
//JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBallView(JNIEnv *env, jobject obj, jint id, jstring url);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setVrView(JNIEnv *env, jobject obj, jint id, jint tileLevel, jstring jPicId, jstring jStrUrl);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setTileBallView(JNIEnv *env, jobject obj, jint id, jint tileLevel, jstring jPicId, jstring jStrUrl, jint fromX, jint offsetX, jint fromY, jint offsetY);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onGetBmp(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring itemId, jobject bmp);

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDown(JNIEnv *env, jobject obj, jint viewId, jboolean isDown);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onClick(JNIEnv *env, jobject obj, jint viewId, jint x, jint y);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDoubleClick(JNIEnv *env, jobject obj, jint viewId);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onZoom(JNIEnv *env, jobject obj, jint viewId, jfloat scale);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onScroll(JNIEnv *env, jobject obj, jint viewId, jint disX, jint disY);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onFling(JNIEnv *env, jobject obj, jint viewId, jint speedX, jint speedY);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setRotateVector(JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z, jfloat w);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setAryGravity(JNIEnv *env, jobject obj, jfloatArray jAryGravity);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setAryMagnetic(JNIEnv *env, jobject obj, jfloatArray jAryMagnetic);
};

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onSurfaceChanged(JNIEnv *env, jobject obj, jint id, jint width, jint height) {
    Engine::onSurfaceChanged(id, width, height);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDrawFrame(JNIEnv *env, jobject obj, jint id) {
    Engine::onDrawFrame(id);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onSurfaceCreated(JNIEnv *env, jobject obj, jint id) {
    Engine::onSurfaceCreated(id);
}


JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onCreate(JNIEnv *env, jobject obj, jint id) {
    Engine::onCreate(id);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onResume(JNIEnv *env, jobject obj, jint id) {
    Engine::onResume(id);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onPause(JNIEnv *env, jobject obj, jint id) {
    Engine::onPause(id);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDestroy(JNIEnv *env, jobject obj, jint id) {
    Engine::onDestroy(id);
}

JNIEXPORT int JNICALL Java_com_sunshine_engine_base_Lib_loadListView(JNIEnv *env, jobject obj, jint id) {
    return Engine::loadListView(id);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_clearListViewData(JNIEnv *env, jobject obj, jint viewId, jint layerId) {
    Engine::clearListViewData(viewId, layerId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_addListViewData(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring jDataId, jstring jPicId, jstring jPicUrl, jstring jTvId, jstring jName) {
    const char *ptChar = NULL;

    ptChar = env->GetStringUTFChars(jDataId, NULL);
    string dataId = string(ptChar);
    env->ReleaseStringUTFChars(jDataId, ptChar);

    ptChar = env->GetStringUTFChars(jPicId, NULL);
    string picId = string(ptChar);
    env->ReleaseStringUTFChars(jPicId, ptChar);

    ptChar = env->GetStringUTFChars(jPicUrl, NULL);
    string picUrl = string(ptChar);
    env->ReleaseStringUTFChars(jPicUrl, ptChar);

    ptChar = env->GetStringUTFChars(jTvId, NULL);
    string tvId = string(ptChar);
    env->ReleaseStringUTFChars(jTvId, ptChar);

    ptChar = env->GetStringUTFChars(jName, NULL);
    string name = string(ptChar);
    env->ReleaseStringUTFChars(jName, ptChar);

    Engine::addListViewData(viewId, layerId, dataId, picId, picUrl, tvId, name);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onLoadNextPageData(JNIEnv *env, jobject obj, jint viewId, jint layerId, jboolean hasMoreData) {
    Engine::requestNextPageDataEnd(viewId, layerId, hasMoreData);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setAddPageMode(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring jContent, jfloat heightK) {
    const char *ptChar = env->GetStringUTFChars(jContent, NULL);
    string content = string(ptChar);
    env->ReleaseStringUTFChars(jContent, ptChar);
    Engine::setAddPageMode(viewId, layerId, content, heightK);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setListViewDefaultPic(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring jPicUrl){
    const char *ptChar = env->GetStringUTFChars(jPicUrl, NULL);
    string picUrl = string(ptChar);
    env->ReleaseStringUTFChars(jPicUrl, ptChar);
    Engine::setListViewDefaultPic(viewId, layerId, picUrl);
}

//JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBallView(JNIEnv *env, jobject obj, jint id, jstring jStrUrl) {
//    const char *ptChar = env->GetStringUTFChars(jStrUrl, NULL);
//    string url = string(ptChar);
//    env->ReleaseStringUTFChars(jStrUrl, ptChar);
//    Engine::setBallView(id, url);
//}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setVrView(JNIEnv *env, jobject obj, jint id, jint tileLevel, jstring jPicId, jstring jStrUrl) {
    const char *ptChar = NULL;
    ptChar = env->GetStringUTFChars(jStrUrl, NULL);
    string url = string(ptChar);
    env->ReleaseStringUTFChars(jStrUrl, ptChar);

    ptChar = env->GetStringUTFChars(jPicId, NULL);
    string picId = string(ptChar);
    env->ReleaseStringUTFChars(jPicId, ptChar);
    Engine::setVrView(id, tileLevel, picId, url);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setTileBallView(JNIEnv *env, jobject obj, jint id, jint tileLevel, jstring jPicId, jstring jStrUrl, jint fromX, jint offsetX, jint fromY, jint offsetY) {
    const char *ptChar = NULL;
    ptChar = env->GetStringUTFChars(jStrUrl, NULL);
    string url = string(ptChar);
    env->ReleaseStringUTFChars(jStrUrl, ptChar);

    ptChar = env->GetStringUTFChars(jPicId, NULL);
    string picId = string(ptChar);
    env->ReleaseStringUTFChars(jPicId, ptChar);
    Engine::setTileBallView(id, tileLevel, picId, url, fromX, offsetX, fromY, offsetY);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onGetBmp(JNIEnv *env, jobject obj, jint viewId, jint layerId, jstring jItemId, jobject bmp) {
    const char *ptChar = env->GetStringUTFChars(jItemId, NULL);
    string itemId = string(ptChar);
    env->ReleaseStringUTFChars(jItemId, ptChar);
    BmpHelper *ptBmpHelper = PlatformHelper::getBmpData(env, bmp);
    Engine::onItemGetBmp(viewId, layerId, itemId, ptBmpHelper);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    PlatformHelper::init(vm);
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDown(JNIEnv *env, jobject obj, jint viewId, jboolean isDown) {
    Engine::onDown(viewId, isDown);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onClick(JNIEnv *env, jobject obj, jint viewId, jint x, jint y) {
    Engine::onClick(viewId, x, y);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onDoubleClick(JNIEnv *env, jobject obj, jint viewId) {
    Engine::onDoubleClick(viewId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onZoom(JNIEnv *env, jobject obj, jint viewId, jfloat scale) {
    Engine::onZoom(viewId, scale);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onScroll(JNIEnv *env, jobject obj, jint viewId, jint disX, jint disY) {
    Engine::onScroll(viewId, disX, disY);

}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onFling(JNIEnv *env, jobject obj, jint viewId, jint speedX, jint speedY) {
    Engine::onFling(viewId, speedX, speedY);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setRotateVector(JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z, jfloat w) {
    Engine::saveRotateVector(x, y, z, w);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setAryGravity(JNIEnv *env, jobject obj, jfloatArray jAryGravity) {
    jfloat *ary = env->GetFloatArrayElements(jAryGravity, NULL);
    SensorHelper::saveAryGravity(ary);
    env->ReleaseFloatArrayElements(jAryGravity, ary, 0);
    env->DeleteLocalRef(jAryGravity);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setAryMagnetic(JNIEnv *env, jobject obj, jfloatArray jAryMagnetic) {
    jfloat *ary = env->GetFloatArrayElements(jAryMagnetic, NULL);
    SensorHelper::saveAryMagnetic(ary);
    env->ReleaseFloatArrayElements(jAryMagnetic, ary, 0);
    env->DeleteLocalRef(jAryMagnetic);
}

//

extern "C" {
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildStage(JNIEnv *env, jobject obj, jstring id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setStageSize(JNIEnv *env, jobject obj, jstring id, jint w, jint h);

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildActor(JNIEnv *env, jobject obj, jstring id);

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildBone(JNIEnv *env, jobject obj, jstring id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBonePicInfo(JNIEnv *env, jobject obj, jstring id, jint left, jint top, jint w, jint h, jint totalW, jint totalH);

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildBoneAnim(JNIEnv *env, jobject obj, jstring id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimRunPercent(JNIEnv *env, jobject obj, jstring id, jfloat startPercent, jfloat endPercent, jboolean isShow);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimInterpolator(JNIEnv *env, jobject obj, jstring id, jint interpolator);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimRect(JNIEnv *env, jobject obj, jstring id, jfloat fromScaleX, jfloat fromScaleY, jfloat toScaleX, jfloat toScaleY, jint fromCenterX, jint fromCenterY, jint toCenterX, int toCenterY);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimAlpha(JNIEnv *env, jobject obj, jstring id, jint from, jint to);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimRotate(JNIEnv *env, jobject obj, jstring id, jfloat from, jfloat to, jint rotateX, jint rotateY);

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onBoneAnimDraw(JNIEnv *env, jobject obj, jstring id, jfloat percent);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onViewSizeChange(JNIEnv *env, jobject obj, jstring id, jint width, jint height, jint left, jint top);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_stopStage(JNIEnv *env, jobject obj, jstring id);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimView(JNIEnv *env, jobject obj, jint viewId, jstring id, jstring xmlUrl, jstring picUrl);
JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setStagePercent(JNIEnv *env, jobject obj, jstring id, jfloat percent);
};


JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildStage(JNIEnv *env, jobject obj, jstring id) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::buildStage(stageId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setStageSize(JNIEnv *env, jobject obj, jstring id, jint w, jint h) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setStageSize(stageId, w, h);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildActor(JNIEnv *env, jobject obj, jstring id) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::buildActor(stageId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildBone(JNIEnv *env, jobject obj, jstring id) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::buildBone(stageId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBonePicInfo(JNIEnv *env, jobject obj, jstring id, jint left, jint top, jint w, jint h, jint totalW, jint totalH) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setBonePicInfo(stageId, left, top, w, h, totalW, totalH);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_buildBoneAnim(JNIEnv *env, jobject obj, jstring id) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::buildBoneAnim(stageId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimRunPercent(JNIEnv *env, jobject obj, jstring id, jfloat startPercent, jfloat endPercent, jboolean isShow) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setBoneAnimRunPercent(stageId, startPercent, endPercent, isShow);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimInterpolator(JNIEnv *env, jobject obj, jstring id, jint interpolator) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setBoneAnimInterpolator(stageId, interpolator);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimRect(JNIEnv *env, jobject obj, jstring id, jfloat fromScaleX, jfloat fromScaleY, jfloat toScaleX, jfloat toScaleY, jint fromCenterX, jint fromCenterY, jint toCenterX, int toCenterY) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setBoneAnimRect(stageId, fromScaleX, fromScaleY, toScaleX, toScaleY, fromCenterX, fromCenterY, toCenterX, toCenterY);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimAlpha(JNIEnv *env, jobject obj, jstring id, jint from, jint to) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setBoneAnimAlpha(stageId, from, to);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimRotate(JNIEnv *env, jobject obj, jstring id, jfloat from, jfloat to, jint rotateX, jint rotateY) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setBoneAnimRotate(stageId, from, to, rotateX, rotateY);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onBoneAnimDraw(JNIEnv *env, jobject obj, jstring id, jfloat percent) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    StageHelper::onDraw(stageId, percent);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_onViewSizeChange(JNIEnv *env, jobject obj, jstring id, jint width, jint height, jint left, jint top) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::onViewSizeChange(stageId, width, height, left, top);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_stopStage(JNIEnv *env, jobject obj, jstring id) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::stop(stageId);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setBoneAnimView(JNIEnv *env, jobject obj, jint viewId, jstring id, jstring jXmlUrl, jstring jPicUrl) {
    const char *ptChar = NULL;
    ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    ptChar = env->GetStringUTFChars(jXmlUrl, NULL);
    string xmlUrl = string(ptChar);
    env->ReleaseStringUTFChars(jXmlUrl, ptChar);
    ptChar = env->GetStringUTFChars(jPicUrl, NULL);
    string picUrl = string(ptChar);
    env->ReleaseStringUTFChars(jPicUrl, ptChar);
    Engine::setBoneAnimView(viewId, stageId, xmlUrl, picUrl);
}

JNIEXPORT void JNICALL Java_com_sunshine_engine_base_Lib_setStagePercent(JNIEnv *env, jobject obj, jstring id, jfloat percent) {
    const char *ptChar = env->GetStringUTFChars(id, NULL);
    string stageId = string(ptChar);
    env->ReleaseStringUTFChars(id, ptChar);
    Engine::setPercent(stageId, percent);
}

#endif