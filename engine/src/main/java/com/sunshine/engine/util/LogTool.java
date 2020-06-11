/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util;


import com.sunshine.engine.util.callback.LogCalllback;

/**
 * Created by Jack on 15/11/20.
 */
public class LogTool {

    private static LogCalllback mCallback = null;

    public static void addLogCallback(LogCalllback callback) {
        mCallback = callback;
    }

    public static void show(String str) {
        if (mCallback != null) {
            mCallback.show(str);
        }
    }
}
