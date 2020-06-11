/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.sensor;

import android.hardware.SensorManager;

import com.sunshine.engine.base.Lib;
import com.sunshine.engine.util.LogTool;
import com.sunshine.engine.util.sensor.math.Quaternion;


/**
 * Created by Jack on 15/12/28.
 */
public class GyrRttHelper {
    private static final float NS2S = 1.0f / 1000000000.0f;
    private static final Quaternion deltaQuaternion = new Quaternion();
    private static Quaternion quaternionGyroscope = new Quaternion();
    private static Quaternion quaternionRotationVector = new Quaternion();
    private static long mTimestamp = 0;
    private static final double EPSILON = 0.1f;
    private static double gyroscopeRotationVelocity = 0;
    private static boolean positionInitialised = false;
    private static final float INDIRECT_INTERPOLATION_WEIGHT = 0.01f;
    private static final float OUTLIER_THRESHOLD = 0.85f;

    public static void reset() {
        mTimestamp = 0;
        positionInitialised = false;
    }

    public static void setAryRotation(float[] ary) {
        float[] q = new float[4];
        SensorManager.getQuaternionFromVector(q, ary);
        quaternionRotationVector.setXYZW(q[1], q[2], q[3], -q[0]);
        if (!positionInitialised) {
            quaternionGyroscope.set(quaternionRotationVector);
            positionInitialised = true;
        }
    }

    public static void setAryGyroscope(float[] ary, long timestamp) {
        if (mTimestamp != 0 && positionInitialised) {
            final float dT = (timestamp - mTimestamp) * NS2S;
            float axisX = ary[0];
            float axisY = ary[1];
            float axisZ = ary[2];
            gyroscopeRotationVelocity = Math.sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
            if (gyroscopeRotationVelocity > EPSILON) {
                axisX /= gyroscopeRotationVelocity;
                axisY /= gyroscopeRotationVelocity;
                axisZ /= gyroscopeRotationVelocity;
            }
            double thetaOverTwo = gyroscopeRotationVelocity * dT / 2.0f;
            double sinThetaOverTwo = Math.sin(thetaOverTwo);
            double cosThetaOverTwo = Math.cos(thetaOverTwo);
            deltaQuaternion.setX((float) (sinThetaOverTwo * axisX));
            deltaQuaternion.setY((float) (sinThetaOverTwo * axisY));
            deltaQuaternion.setZ((float) (sinThetaOverTwo * axisZ));
            deltaQuaternion.setW((float) -cosThetaOverTwo);

            deltaQuaternion.multiplyByQuat(quaternionGyroscope);

            float dotProd = quaternionGyroscope.dotProduct(quaternionRotationVector);
            if (Math.abs(dotProd) < OUTLIER_THRESHOLD) {
                LogTool.show("GyrRttHelper: data isn't correct!");
                quaternionGyroscope.set(quaternionRotationVector);
            } else {
                quaternionGyroscope.slerp(quaternionRotationVector, deltaQuaternion, (float) (INDIRECT_INTERPOLATION_WEIGHT * gyroscopeRotationVelocity));
                quaternionGyroscope.set(deltaQuaternion);
            }
            Lib.setRotateVector(quaternionGyroscope.getX(), quaternionGyroscope.getY(), quaternionGyroscope.getZ(), -quaternionGyroscope.getW());
        }
        mTimestamp = timestamp;
    }
}
