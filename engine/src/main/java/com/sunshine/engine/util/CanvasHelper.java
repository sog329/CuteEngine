/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PaintFlagsDrawFilter;
import android.graphics.Rect;

/**
 * Created by Jack on 2015/12/6 0006.
 */
public class CanvasHelper {
    private static Object mLock = new Object();
    private static Bitmap mBitmap = null;
    private static Canvas mCanvas = null;
    private static final Paint mPaint = new Paint();
    private static final PaintFlagsDrawFilter mPaintFilter = new PaintFlagsDrawFilter(0, Paint.ANTI_ALIAS_FLAG | Paint.FILTER_BITMAP_FLAG);

    private static Rect mRcBmp = new Rect();
    private static Rect mRcDst = new Rect();

    public static void pushCanvas(Canvas canvas, Bitmap bitmap) {
        synchronized(mLock) {
            mCanvas = canvas;
            mCanvas.setDrawFilter(mPaintFilter);
            mPaint.setAntiAlias(true);
            mBitmap = bitmap;
        }
    }

    public static void popCanvas() {
        synchronized(mLock) {
            mCanvas = null;
            mBitmap = null;
        }
    }

    public static void onDraw(int mPicLeft, int mPicTop, int mPicRight, int mPicBottom, int mActualLeft, int mActualTop, int mActualRight, int mActualBottom, int mAlpha, float mRotateDegree, int mActualRotateX, int mActualRotateY) {
        synchronized(mLock) {
            if (mCanvas != null && mBitmap != null) {
                int canvasState = mCanvas.save();
                mCanvas.rotate(mRotateDegree, mActualRotateX, mActualRotateY);
                mPaint.setAlpha(mAlpha);
                mRcBmp.set(mPicLeft, mPicTop, mPicRight, mPicBottom);
                mRcDst.set(mActualLeft, mActualTop, mActualRight, mActualBottom);
                mCanvas.drawBitmap(mBitmap, mRcBmp, mRcDst, mPaint);
                mCanvas.restoreToCount(canvasState);
            }
        }
    }

}
