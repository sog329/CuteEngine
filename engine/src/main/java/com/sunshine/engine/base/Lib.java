/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */

package com.sunshine.engine.base;

// Wrapper for native library

import android.graphics.Bitmap;

public class Lib {

    static {
        System.loadLibrary("CuteEngine");
    }

    public static native void onSurfaceChanged(int id, int width, int height);

    public static native void onDrawFrame(int id);

    public static native void onSurfaceCreated(int id);

    public static native void onCreate(int id);

    public static native void onResume(int id);

    public static native void onPause(int id);

    public static native void onDestroy(int id);

    public static native int loadListView(int id);

    public static native void clearListViewData(int viewId, int layerId);

    public static native void addListViewData(int viewId, int layerId, String dataId, String picId, String picUrl, String tvId, String name);

    public static native void onLoadNextPageData(int viewId, int layerId, boolean hasMoreData);

    public static native void setAddPageMode(int viewId, int layerId, String content, float heightK);

    public static native void setListViewDefaultPic(int viewId, int layerId, String picUrl);

//    public static native void setBallView(int id, String url);

    public static native void setVrView(int id, int tileLevel, String picId, String url);

    public static native void setTileBallView(int id, int tileLevel, String picId, String url, int fromX, int offsetX, int fromY, int offsetY);

    public static native void onGetBmp(int viewId, int layerId, String itemId, Bitmap bmp);

    public static native void onDown(int id, boolean isDown);

    public static native void onScroll(int id, int disX, int disY);

    public static native void onFling(int id, int speedX, int speedY);

    public static native void onClick(int id, int x, int y);

    public static native void onDoubleClick(int id);

    public static native void onZoom(int id, float scale);

    public static native void setRotateVector(float x, float y, float z, float w);

    public static native void setAryGravity(float[] aryGravity);

    public static native void setAryMagnetic(float[] aryMagnetic);

    // BoneEngine
    public static native void buildStage(String id);

    public static native void setStageSize(String id, int w, int h);

    public static native void buildActor(String id);

    public static native void buildBone(String id);

    public static native void setBonePicInfo(String id, int left, int top, int w, int h, int totalW, int totalH);

    public static native void buildBoneAnim(String id);

    public static native void setBoneAnimRunPercent(String id, float startPercent, float endPercent, boolean isShow);

    public static native void setBoneAnimInterpolator(String id, int interpolator);

    public static native void setBoneAnimRect(String id, float fromScaleX, float fromScaleY, float toScaleX, float toScaleY, int fromCenterX, int fromCenterY, int toCenterX, int toCenterY);

    public static native void setBoneAnimAlpha(String id, int from, int to);

    public static native void setBoneAnimRotate(String id, float from, float to, int rotateX, int rotateY);

    public static native void onBoneAnimDraw(String id, float percent);

    public static native void onViewSizeChange(String id, int width, int height, int left, int top);

    public static native void stopStage(String id);

    public static native void setBoneAnimView(int viewId, String id, String xmlUrl, String picUrl);

    public static native void setStagePercent(String id, float percent);
}
