/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.callback;

import android.graphics.Bitmap;

/**
 * Created by Jack on 16/1/11.
 */
public interface TvCallback {
    Bitmap buildBmp(String content, int w, int h);
}
