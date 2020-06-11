/*
 * Copyright (C) 2016 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.pic;


import com.sunshine.engine.util.LogTool;

import org.json.JSONObject;

/**
 * Created by Jack on 16/3/3.
 */
public class PicDescTool {
    private static final String SCALE = "scale";

    public static JSONObject getJsonObj(String description) {
        JSONObject obj = null;
        try {
            obj = new JSONObject(description);
        } catch (Exception e) {
            LogTool.show(description + "_" + e.toString());
        }
        return obj;
    }

    public static int getScale(JSONObject obj) {
        int scale = 1;
        try {
            if (obj != null && obj.has(SCALE)) {
                scale = obj.getInt(SCALE);
            }
        } catch (Exception e) {
            LogTool.show(e.toString());
        }
        return scale;
    }
}
