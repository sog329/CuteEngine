/*
 * Copyright (C) 2015 Baidu, Inc. All Rights Reserved.
 */
package com.sunshine.engine.util.sensor.math;

public class Quaternion {
    protected float points[] = {0, 0, 0, 0};

    public void set(Quaternion vec) {
        this.points[0] = vec.points[0];
        this.points[1] = vec.points[1];
        this.points[2] = vec.points[2];
        this.points[3] = vec.points[3];
    }

    public void multiplyByQuat(Quaternion input) {
        Quaternion inputCopy = new Quaternion();
        inputCopy.points[0] = input.points[0];
        inputCopy.points[1] = input.points[1];
        inputCopy.points[2] = input.points[2];
        inputCopy.points[3] = input.points[3];

        input.points[3] = (points[3] * inputCopy.points[3] - points[0] * inputCopy.points[0] - points[1] * inputCopy.points[1] - points[2] * inputCopy.points[2]); //w = w1w2 - x1x2 - y1y2 - z1z2
        input.points[0] = (points[3] * inputCopy.points[0] + points[0] * inputCopy.points[3] + points[1] * inputCopy.points[2] - points[2] * inputCopy.points[1]); //x = w1x2 + x1w2 + y1z2 - z1y2
        input.points[1] = (points[3] * inputCopy.points[1] + points[1] * inputCopy.points[3] + points[2] * inputCopy.points[0] - points[0] * inputCopy.points[2]); //y = w1y2 + y1w2 + z1x2 - x1z2
        input.points[2] = (points[3] * inputCopy.points[2] + points[2] * inputCopy.points[3] + points[0] * inputCopy.points[1] - points[1] * inputCopy.points[0]); //z = w1z2 + z1w2 + x1y2 - y1x2
    }

    public void setX(float x) {
        this.points[0] = x;
    }

    public void setY(float y) {
        this.points[1] = y;
    }

    public void setZ(float z) {
        this.points[2] = z;
    }

    public void setW(float w) {
        this.points[3] = w;
    }

    public float getX() {
        return this.points[0];
    }

    public float getY() {
        return this.points[1];
    }

    public float getZ() {
        return this.points[2];
    }

    public float getW() {
        return this.points[3];
    }

    public void setXYZW(float x, float y, float z, float w) {
        this.points[0] = x;
        this.points[1] = y;
        this.points[2] = z;
        this.points[3] = w;
    }

    public float dotProduct(Quaternion input) {
        return this.points[0] * input.points[0] + this.points[1] * input.points[1] + this.points[2] * input.points[2] + this.points[3] * input.points[3];
    }

    public void slerp(Quaternion input, Quaternion output, float t) {
        Quaternion bufferQuat = null;
        float cosHalftheta = this.dotProduct(input);

        if (cosHalftheta < 0) {
            bufferQuat = new Quaternion();
            cosHalftheta = -cosHalftheta;
            bufferQuat.points[0] = (-input.points[0]);
            bufferQuat.points[1] = (-input.points[1]);
            bufferQuat.points[2] = (-input.points[2]);
            bufferQuat.points[3] = (-input.points[3]);
        } else {
            bufferQuat = input;
        }
        if (Math.abs(cosHalftheta) >= 1.0) {
            output.points[0] = (this.points[0]);
            output.points[1] = (this.points[1]);
            output.points[2] = (this.points[2]);
            output.points[3] = (this.points[3]);
        } else {
            double sinHalfTheta = Math.sqrt(1.0 - cosHalftheta * cosHalftheta);
            double halfTheta = Math.acos(cosHalftheta);

            double ratioA = Math.sin((1 - t) * halfTheta) / sinHalfTheta;
            double ratioB = Math.sin(t * halfTheta) / sinHalfTheta;

            output.points[3] = ((float) (points[3] * ratioA + bufferQuat.points[3] * ratioB));
            output.points[0] = ((float) (this.points[0] * ratioA + bufferQuat.points[0] * ratioB));
            output.points[1] = ((float) (this.points[1] * ratioA + bufferQuat.points[1] * ratioB));
            output.points[2] = ((float) (this.points[2] * ratioA + bufferQuat.points[2] * ratioB));
        }
    }
}
