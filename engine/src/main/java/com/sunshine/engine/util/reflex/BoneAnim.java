/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.reflex;


import com.sunshine.engine.util.CanvasHelper;

/**
 * Created by Jack on 2015/12/5 0005.
 */
public class BoneAnim {
    private static CanvasHelper mCanvasHelper = new CanvasHelper();

    public static void onDraw(int mPicLeft, int mPicTop, int mPicRight, int mPicBottom, int mActualLeft, int mActualTop, int mActualRight, int mActualBottom, int mAlpha, float mRotateDegree, int mActualRotateX, int mActualRotateY) {
        mCanvasHelper.onDraw(mPicLeft, mPicTop, mPicRight, mPicBottom, mActualLeft, mActualTop, mActualRight, mActualBottom, mAlpha, mRotateDegree, mActualRotateX, mActualRotateY);
    }
}
