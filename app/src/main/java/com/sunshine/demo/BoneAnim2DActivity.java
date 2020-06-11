/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.demo;

import android.app.Activity;
import android.os.Bundle;

import com.sunshine.engine.app.bone.BoneView;
import com.sunshine.engine.app.bone.WelcomeScrollView;
import com.sunshine.engine.util.callback.WelcomeOnScrollCallback;


/**
 * Created by Jack on 15/12/7.
 */
public class BoneAnim2DActivity extends Activity {
    private BoneView mView = null;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.welcome_layout_2d);

        mView = (BoneView) findViewById(R.id.welcome_stage_view);
        mView.start("welcome", "welcome/config.xml", "welcome/pic");

        WelcomeScrollView sv = (WelcomeScrollView)findViewById(R.id.welcome_scrollview);
        WelcomeOnScrollCallback listener = new WelcomeOnScrollCallback() {
            @Override
            public void onChanged(float percent) {
                mView.setPercent(percent);
            }
        };
        sv.setOnScrollListener(listener);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mView.stop();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        finish();
    }
}