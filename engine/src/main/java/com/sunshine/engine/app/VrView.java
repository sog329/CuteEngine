/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.app;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;

import com.sunshine.engine.base.CuteViewGL;
import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.SensorHelper;
import com.sunshine.engine.util.pic.SdcardHelper;


/**
 * Created by Jack on 16/1/6.
 */
public class VrView extends CuteViewGL {

    private SensorHelper mSensorHelper = null;

    public VrView(Context context) {
        super(context);
        onCreate();
    }

    public VrView(Context context, AttributeSet attrs) {
        super(context, attrs);
        onCreate();
    }

    public void setVrView(int tileLevel, String picId, String picUrl, String picCachePath, int maxNumber) {
        SdcardHelper.addFolderPath(picId, picCachePath, maxNumber);
        Lib.setVrView(getViewId(), tileLevel, picId, picUrl);
    }

    private void onCreate() {
        mSensorHelper = new SensorHelper((Activity) getContext(), SensorHelper.Type.Rtt);
    }

    @Override
    public void onResume() {
        super.onResume();
        mSensorHelper.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mSensorHelper.onPause();
    }
}
