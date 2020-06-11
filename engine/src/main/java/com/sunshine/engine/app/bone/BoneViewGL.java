/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.app.bone;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;

import com.sunshine.engine.base.CuteViewGL;
import com.sunshine.engine.base.Lib;


/**
 * Created by Jack on 15/12/7.
 */
public class BoneViewGL extends CuteViewGL {
    private String mId = null;

    public BoneViewGL(Context context) {
        super(context);
    }

    public BoneViewGL(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return false;
    }

    public void start(String id, String xmlUrl, String picUrl) {
        mId = id;
        Lib.setBoneAnimView(hashCode(), id, xmlUrl, picUrl);
    }

    public void setPercent(float percent) {
        Lib.setStagePercent(mId, percent);
    }
}
