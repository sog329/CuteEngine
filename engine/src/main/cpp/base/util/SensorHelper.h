//
// Created by Jack on 15/11/21.
//

#ifndef BASE_SENSORHELPER_H
#define BASE_SENSORHELPER_H


#include "ThreadLock.h"

class SensorHelper {
private:
    static ThreadLock mLock;
    static float mRotateVectorSensor[4];
    static float mRotateVectorCurrent[4];
    static float mCurrentRotationMatrix44[16];
    static bool mUseVector;
    static float mAryGravitySensor[3];
    static float mAryGravityCurrent[3];
    static float mAryMagneticSensor[3];
    static float mAryMagneticCurrent[3];

public:
    static void saveRotateVector(float x, float y, float z, float w);

    static void saveAryGravity(float *aryGravity);

    static void saveAryMagnetic(float *aryMagnetic);

    static void buildCurrentRotationMatrix44();

    static float *getCurrentRotationMatrix44();

};


#endif //BASE_SENSORHELPER_H
