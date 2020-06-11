/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util;

import android.content.Context;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;

import com.sunshine.engine.base.Lib;


/**
 * Created by Jack on 15/11/20.
 */
public class TouchHelper implements GestureDetector.OnGestureListener, GestureDetector.OnDoubleTapListener {

    private int mId = 0;
    private float mDistance = 0;
    private GestureDetector mGestureDetector = null;
    private View.OnClickListener mClickListener = null;

    public TouchHelper(Context ct, int id) {
        mId = id;
        mGestureDetector = new GestureDetector(ct, this);
        mGestureDetector.setOnDoubleTapListener(this);
        mGestureDetector.setIsLongpressEnabled(false);
    }

    public void setOnClickListener(View.OnClickListener l) {
        mClickListener = l;
    }

    public boolean onTouchEvent(MotionEvent event) {
        boolean result = false;
        if (event.getAction() == MotionEvent.ACTION_MOVE && event.getPointerCount() == 2) {
            float x = event.getX(0) - event.getX(1);
            float y = event.getY(0) - event.getY(1);
            float value = (float) Math.sqrt(x * x + y * y);// 计算两点的距离
            if (mDistance == 0) {
                mDistance = value;
                Lib.onZoom(mId, 1);
            } else {
                if (Math.abs(value - mDistance) >= 10) {
                    float scale = value / mDistance;// 当前两点间的距离除以手指落下时两点间的距离就是需要缩放的比例。
                    Lib.onZoom(mId, scale);
                }
            }
        } else {
            mDistance = 0;
            result = mGestureDetector.onTouchEvent(event);
            if (!result && event.getPointerCount() == 1 && (event.getAction() == MotionEvent.ACTION_CANCEL || event.getAction() == MotionEvent.ACTION_UP)) {
                Lib.onDown(mId, false);
            }
        }
//        LogTool.show("TouchHelper.onTouchEvent: result" + result);
        return result;
    }

    @Override
    public boolean onSingleTapConfirmed(MotionEvent motionEvent) {
        Lib.onClick(mId, (int) motionEvent.getX(), (int) motionEvent.getY());
        if (mClickListener != null) {
            mClickListener.onClick(null);
        }
//        LogTool.show("TouchHelper.onSingleTapConfirmed");
        return false;
    }

    @Override
    public boolean onDoubleTap(MotionEvent motionEvent) {
        Lib.onDoubleClick(mId);
        return false;
    }

    @Override
    public boolean onDoubleTapEvent(MotionEvent motionEvent) {
        return false;
    }

    @Override
    public boolean onDown(MotionEvent motionEvent) {
        Lib.onDown(mId, true);
        return true;
    }

    @Override
    public void onShowPress(MotionEvent motionEvent) {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent motionEvent) {
        LogTool.show("TouchHelper.onSingleTapUp");
        return false;
    }

    @Override
    public boolean onScroll(MotionEvent motionEvent, MotionEvent motionEvent1, float disX, float disY) {
        int c1 = motionEvent.getPointerCount();
        int c2 = motionEvent1.getPointerCount();
        if (c1 == 1 && c2 == 1) {
            Lib.onScroll(mId, (int) disX, (int) disY);
        }
        LogTool.show("disX=" + disX + ";   disY=" + disY);
        return false;
    }

    @Override
    public void onLongPress(MotionEvent motionEvent) {

    }

    @Override
    public boolean onFling(MotionEvent motionEvent, MotionEvent motionEvent1, float speedX, float speedY) {
        if (motionEvent.getPointerCount() == 1 && motionEvent1.getPointerCount() == 1) {
            speedX = (int) -speedX;
            speedY = (int) -speedY;
            Lib.onFling(mId, (int) speedX, (int) speedY);
            return true;
        } else {
            return false;
        }
    }
}
