/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.app.bone;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.View;

import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.CanvasHelper;
import com.sunshine.engine.util.XmlHelper;
import com.sunshine.engine.util.reflex.Engine;


/**
 * Created by Jack on 15/12/7.
 */
public class BoneView extends View {
    private Bitmap[] mAryBmp = new Bitmap[] {null};
    private String mId = null;
    private float mPercent = 0;
    private int mWidth = 0;
    private int mHeight = 0;

    public BoneView(Context context) {
        super(context);
        Engine.onCreate(this);
    }

    public BoneView(Context context, AttributeSet attrs) {
        super(context, attrs);
        Engine.onCreate(this);
    }

    public BoneView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        Engine.onCreate(this);
    }

    public void setPercent(float percent) {
        mPercent = percent;
        invalidate();
    }

    public interface Callback {
        void onGetBmp(String xmlUrl, Bitmap bmp);
    }

    public void start(final String id, final String xmlUrl, final String picUrl) {
        stop(); // 先stop再设置id，保证析构掉之前的骨骼动画数据
        mId = id;
        if (mId != null) {
            final Callback callback = new Callback() {
                @Override
                public void onGetBmp(String id, Bitmap bmp) {
                    if (mId != null && mId.equals(id)) {
                        synchronized(mAryBmp) {
                            if (mAryBmp[0] != null) {
                                mAryBmp[0].recycle();
                                mAryBmp[0] = null;
                            }
                            mAryBmp[0] = bmp;
                        }
                        Lib.onViewSizeChange(id, mWidth, mHeight, getPaddingLeft(), getPaddingTop());
                        postInvalidate();
                    } else {
                        bmp.recycle();
                    }
                }
            };
            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    new XmlHelper().parse(id, xmlUrl, picUrl, callback);
                }
            };
            Thread thread = new Thread(runnable);
            thread.start();
        }
    }

    @Override
    public void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        synchronized(mAryBmp) {
            if (mAryBmp[0] != null) {
                CanvasHelper.pushCanvas(canvas, mAryBmp[0]);
                Lib.onBoneAnimDraw(mId, mPercent);
                CanvasHelper.popCanvas();
            }
        }
    }

    public void stop() {
        synchronized(mAryBmp) {
            if (mAryBmp[0] != null) {
                mAryBmp[0].recycle();
                mAryBmp[0] = null;
            }
            mPercent = 0;
        }
        if (mId != null) {
            Lib.stopStage(mId);
        }
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        mWidth = w - getPaddingLeft() - getPaddingRight();
        mHeight = h - getPaddingTop() - getPaddingBottom();
    }
}
