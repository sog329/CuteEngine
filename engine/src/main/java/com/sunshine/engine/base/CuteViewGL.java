/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.base;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.MotionEvent;

import com.sunshine.engine.util.TouchHelper;
import com.sunshine.engine.util.callback.Callback;
import com.sunshine.engine.util.callback.ListCallback;
import com.sunshine.engine.util.callback.TvCallback;
import com.sunshine.engine.util.reflex.Engine;

import java.util.HashMap;
import java.util.Map;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Jack on 15/12/7.
 */
public class CuteViewGL extends GLSurfaceView {
    private TouchHelper mTouchHelper = null;
    private Callback mCallback = null;
    private int mViewId = hashCode();
    private boolean mIsResume = false;

    private Map<String, TvCallback> mTvCbMap = new HashMap<String, TvCallback>();

    public void addTvCallback(String id, TvCallback callback) {
        mTvCbMap.put(id, callback);
    }

    public TvCallback getTvCallback(String id) {
        return mTvCbMap.get(id);
    }

    public CuteViewGL(Context context) {
        super(context);
        init();
    }

    public CuteViewGL(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        setEGLContextClientVersion(2);
        final int id = hashCode();
        Renderer rd = new Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
                Lib.onSurfaceCreated(id);
            }

            @Override
            public void onSurfaceChanged(GL10 gl10, int w, int h) {
                Lib.onSurfaceChanged(id, w, h);
            }

            @Override
            public void onDrawFrame(GL10 gl10) {
                if (mIsResume) {
                    Lib.onDrawFrame(id);
                }
            }
        };
        setEGLConfigChooser(5, 6, 5, 0, 16, 0);
        setRenderer(rd);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        Engine.onCreate(this);
        Lib.onCreate(id);
        mTouchHelper = new TouchHelper(getContext(), id);
    }

    public void onDestroy() {
        Lib.onDestroy(hashCode());
        Engine.onDestroy(this);
    }

    public void onPause() {
        mIsResume = false;
        super.onPause();
        Lib.onPause(hashCode());
    }

    public void onResume() {
        mIsResume = true;
        super.onResume();
        Lib.onResume(hashCode());
    }

    public boolean isResume() {
        return mIsResume;
    }

    public int getViewId() {
        return mViewId;
    }

    public void setDataCallback(ListCallback callback) {
        mCallback = callback;
    }

    public Callback getDataCallback() {
        return mCallback;
    }

    @Override
    public void setOnClickListener(OnClickListener l) {
        mTouchHelper.setOnClickListener(l);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return mTouchHelper.onTouchEvent(event);
    }
}
