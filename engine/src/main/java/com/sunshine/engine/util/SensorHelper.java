/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import com.sunshine.engine.util.sensor.GraMagHelper;
import com.sunshine.engine.util.sensor.GyrRttHelper;
import com.sunshine.engine.util.sensor.RttHelper;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Jack on 15/11/1.
 */
public class SensorHelper implements SensorEventListener {
    private SensorManager mSensorManager = null;
    private List<Sensor> mLstSensor = new ArrayList<Sensor>();
    private boolean mHasRegister = false;

    private Type mType = Type.Rtt;

    public enum Type {
        Rtt, GyrRtt, GraMag, NONE
    }

    public SensorHelper(Activity activity, Type sensorType) {
        mType = sensorType;
        mSensorManager = (SensorManager) activity.getSystemService(Context.SENSOR_SERVICE);
        if (sensorType == Type.GraMag) {
            mLstSensor.add(mSensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY));
            mLstSensor.add(mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD));
        } else if (sensorType == Type.GyrRtt) {
            mLstSensor.add(mSensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR));
            mLstSensor.add(mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE));
        } else if (sensorType == Type.Rtt) {
            mLstSensor.add(mSensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR));
        }
    }

    public void onResume() {
        if (!mHasRegister && mLstSensor.size() > 0) {
            for (int i = 0; i < mLstSensor.size(); i++) {
                mHasRegister = mSensorManager.registerListener(this, mLstSensor.get(i), SensorManager.SENSOR_DELAY_GAME);
            }
            if (mType == Type.GyrRtt) {
                GyrRttHelper.reset();
            }
        }
    }

    public void onPause() {
        if (mHasRegister) {
            for (int i = 0; i < mLstSensor.size(); i++) {
                mSensorManager.unregisterListener(this, mLstSensor.get(i));
            }
            mHasRegister = false;
            if (mType == Type.GyrRtt) {
                GyrRttHelper.reset();
            }
        }
    }

    @Override
    public void onSensorChanged(SensorEvent e) {
        if (e != null) {
            int sensorType = e.sensor.getType();
            switch (sensorType) {
                case Sensor.TYPE_ROTATION_VECTOR:
                    if (mType == Type.Rtt) {
                        RttHelper.setAryRotation(e.values);
                    } else if (mType == Type.GyrRtt) {
                        GyrRttHelper.setAryRotation(e.values);
                    }
                    break;
                case Sensor.TYPE_GRAVITY:
                    GraMagHelper.setAryGravity(e.values);
                    break;
                case Sensor.TYPE_MAGNETIC_FIELD:
                    GraMagHelper.setAryMagnetic(e.values);
                    break;
                case Sensor.TYPE_GYROSCOPE:
                    //                    if (mType == Type.GyrRtt) {
                    GyrRttHelper.setAryGyroscope(e.values, e.timestamp);
                    //                    }
                    break;
                default:
                    break;
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
        int sensorType = sensor.getType();
        switch (sensorType) {
            case Sensor.TYPE_ROTATION_VECTOR:
                LogTool.show("onAccuracyChanged.TYPE_ROTATION_VECTOR: " + i);
                break;
            case Sensor.TYPE_GRAVITY:
                LogTool.show("onAccuracyChanged.TYPE_GRAVITY: " + i);
                break;
            case Sensor.TYPE_MAGNETIC_FIELD:
                LogTool.show("onAccuracyChanged.TYPE_MAGNETIC_FIELD: " + i);
                break;
            case Sensor.TYPE_GYROSCOPE:
                LogTool.show("onAccuracyChanged.TYPE_GYROSCOPE: " + i);
                break;
            default:
                break;
        }
    }
}
