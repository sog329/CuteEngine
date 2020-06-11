//
// Created by Jack on 2015/12/11 0011.
//

#include "SlerpHelper.h"
#include <math.h>


const float SlerpHelper::ERROR_RANGE = 0.02;
float SlerpHelper::mQuaternionFactor = .8;

void SlerpHelper::buildStandardVector(float *ptVector) {
    float m = 0;
    for (int i = 0; i < 4; i++) {
        m += ptVector[i] * ptVector[i];
    }
    if (fabsf(1 - m) > ERROR_RANGE) {
        float c2 = ptVector[3] * ptVector[3];
        float s2 = 1 - c2;
        float n = (float) sqrt((m - c2) / s2);
        if (n != 0) {
            for (int i = 0; i < 3; i++) {
                ptVector[i] /= n;
            }
        }
    }
}

void SlerpHelper::slerpQuaternion(float *ptVectorCurrent, float *ptVectorActual) {
    float cosOmega = 0;
    for (int i = 0; i < 4; i++) {
        cosOmega += ptVectorActual[i] * ptVectorCurrent[i];
    }
    if (cosOmega < 0.0) {
        for (int i = 0; i < 4; i++) {
            ptVectorCurrent[i] = -ptVectorCurrent[i];
        }
        cosOmega = -cosOmega;
    }
    float kSensor = 1.0 - mQuaternionFactor;
    float kTemp = mQuaternionFactor;
    if (cosOmega <= .9999) {
        float sinOmega = sqrt(1.0 - cosOmega * cosOmega);
        float omega = atan2(sinOmega, cosOmega);
        float oneOverSinOmega = 1.0 / sinOmega;
        kSensor = sin((1.0 - mQuaternionFactor) * omega) * oneOverSinOmega;
        kTemp = sin(mQuaternionFactor * omega) * oneOverSinOmega;
    }
    for (int i = 0; i < 4; i++) {
        ptVectorCurrent[i] = kSensor * ptVectorActual[i] + kTemp * ptVectorCurrent[i];
    }
}

void SlerpHelper::slerpAry(float *ptAryCurrent, float *ptArySensor, float distance, float factor) {
    if (factor > 1 || factor < 0) {
        factor = 0;
    }
    distance = fabsf(distance);
    float kCurrent = factor;
    for (int i = 0; i < 3; i++) {
        if (distance > 0) {
            float dis = fabsf(ptAryCurrent[i] - ptArySensor[i]);
            if (dis < distance) {
                float x = 1 - dis / distance;
                kCurrent = factor + (1 - factor) * x * x * x;
            }
        }
        float kSensor = 1 - kCurrent;
        ptAryCurrent[i] = ptAryCurrent[i] * kCurrent + ptArySensor[i] * kSensor;
    }
}