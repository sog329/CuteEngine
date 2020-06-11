/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.demo;

import android.app.Activity;
import android.os.Bundle;

import com.sunshine.engine.app.bone.BoneViewGL;
import com.sunshine.engine.app.bone.WelcomeScrollView;
import com.sunshine.engine.util.callback.WelcomeOnScrollCallback;

/**
 * Created by Jack on 15/12/7.
 */
public class BoneAnim3DActivity extends Activity {
    private BoneViewGL mView = null;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.welcome_layout_3d);

        mView = (BoneViewGL) findViewById(R.id.welcome_stage_view);
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
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mView.onDestroy();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        finish();
    }
}