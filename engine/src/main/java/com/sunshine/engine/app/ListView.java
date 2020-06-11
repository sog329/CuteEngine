/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.app;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.util.AttributeSet;

import com.sunshine.engine.base.CuteViewGL;
import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.SensorHelper;
import com.sunshine.engine.util.callback.TvCallback;
import com.sunshine.engine.util.pic.BmpHelper;


/**
 * Created by Jack on 16/1/6.
 */
public class ListView extends CuteViewGL {
    public static final String TV_NAME_ID = "name";
    public static final String TV_LOADING_ID = "loading";

    private int mLayerId = 0;
    private SensorHelper mSensorHelper = null;
    private float mHeightK = 1;

    public ListView(Context context) {
        super(context);
        onCreate();
    }

    public ListView(Context context, AttributeSet attrs) {
        super(context, attrs);
        onCreate();
    }

    private void onCreate() {
        setRenderMode(RENDERMODE_CONTINUOUSLY);
        mLayerId = Lib.loadListView(getViewId());

        addTvCallback(TV_LOADING_ID, new TvCallback() {
            @Override
            public Bitmap buildBmp(String content, int w, int h) {
                Bitmap bmp = BmpHelper.getBitmapByText(w, h, content, (int) (h * .45), Color.argb(100, 0, 0, 0), Color.argb(0, 0, 0, 0), 0, h / 5, true);
                return bmp;
            }
        });
        mSensorHelper = new SensorHelper((Activity) getContext(), SensorHelper.Type.Rtt);
    }

    public void setAddPageMode(String content, float heightK) {
        Lib.setAddPageMode(getViewId(), mLayerId, content, heightK);
        mHeightK = heightK;
    }

    public void onLoadNextPageData(boolean hasMoreData) {
        Lib.onLoadNextPageData(getViewId(), mLayerId, hasMoreData);
    }

    public void clearListViewData() {
        Lib.clearListViewData(getViewId(), mLayerId);
    }

    public void setDefaultPic(String picUrl) {
        Lib.setListViewDefaultPic(getViewId(), mLayerId, picUrl);
    }

    public void addListViewData(String dataId, String picId, String picUrl, String name) {
        Lib.addListViewData(getViewId(), mLayerId, dataId, picId, picUrl, TV_NAME_ID, name);
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
