/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.sensor;


import com.sunshine.engine.base.Lib;

/**
 * Created by Jack on 15/12/28.
 */
public class RttHelper {
    public static void setAryRotation(float[] ary) {
        if (ary.length >= 3) {
            float x = ary[0];
            float y = ary[1];
            float z = ary[2];
            float w = 0;
            if (ary.length == 4) {
                w = ary[3];
            } else {
                w = 1 - x * x - y * y - z * z;
                w = (w > 0) ? (float) Math.sqrt(w) : 0;
            }
            Lib.setRotateVector(x, y, z, w);
        }
    }
}
