/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */

package com.sunshine.demo;

import android.app.Activity;
import android.os.Bundle;

import com.sunshine.engine.app.VrView;
import com.sunshine.engine.util.pic.SdcardHelper;

public class VrActivity extends Activity {
    public static String URL = "url";
    private VrView mView = null;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.activity_vrview);
        mView = (VrView) findViewById(R.id.ugc_view);

        String url = getIntent().getStringExtra(URL);
        int tileLevel = 4;
        url = "http://pai.baidu.com/?qt=gettiles&pid=55684be0cba709e3763c9b7d_1437028628_48v54kufis&pos=%d_%d&level=%d";
        mView.setVrView(tileLevel, "vr", url, SdcardHelper.getFolderPath("tmpPic"), 16);
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
