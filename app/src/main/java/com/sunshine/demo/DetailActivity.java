/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */

package com.sunshine.demo;

import android.app.Activity;
import android.os.Bundle;

import com.sunshine.engine.app.BallView;


public class DetailActivity extends Activity {
    public static final String URL = "url";
    private BallView mView = null;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.activity_main);
        mView = (BallView) findViewById(R.id.ugc_view);

        String url = getIntent().getStringExtra(URL);
        //        if ("accet:p2.jpg".equals(url)) {
        int tileLevel = 4;
        url = "http://pai.baidu.com/?qt=gettiles&pid=55684be0cba709e3763c9b7d_1437028628_48v54kufis&pos=%d_%d&level=%d";
        mView.setTileBallView(tileLevel, "tile", url, 0, 360, 90, 180, "tmpPic", 1600);
        //        } else {
        //            Lib.setBallView(mView.hashCode(), url);
        //        }
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
