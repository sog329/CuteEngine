//
// Created by Jack on 15/11/21.
//

#include "SensorHelper.h"
#include "MatrixHelper.h"
#include "SlerpHelper.h"

float SensorHelper::mCurrentRotationMatrix44[16]{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,};
float SensorHelper::mRotateVectorSensor[4]{0, 0, 0, 1};
float SensorHelper::mRotateVectorCurrent[4]{0, 0, 0, 1};
float SensorHelper::mAryGravitySensor[3]{0, 0, 0};
float SensorHelper::mAryGravityCurrent[3]{0, 0, 0};
float SensorHelper::mAryMagneticSensor[3]{0, 0, 0};
float SensorHelper::mAryMagneticCurrent[3]{0, 0, 0};
bool SensorHelper::mUseVector = true;

ThreadLock SensorHelper::mLock;

void SensorHelper::saveRotateVector(float x, float y, float z, float w) {
    mLock.lock();
    mUseVector = true;
    mRotateVectorSensor[0] = x;
    mRotateVectorSensor[1] = y;
    mRotateVectorSensor[2] = z;
    mRotateVectorSensor[3] = w;
    mLock.unlock();
}

void SensorHelper::buildCurrentRotationMatrix44() {
    mLock.lock();
    if (mUseVector) {
        SlerpHelper::buildStandardVector(mRotateVectorSensor);
        SlerpHelper::slerpQuaternion(mRotateVectorCurrent, mRotateVectorSensor);
        MatrixHelper::getRotationMatrixFromVector(mCurrentRotationMatrix44, mRotateVectorCurrent);
    } else {
        SlerpHelper::slerpAry(mAryGravityCurrent, mAryGravitySensor, 1, .8);
        SlerpHelper::slerpAry(mAryMagneticCurrent, mAryMagneticSensor, 10, .9);
        MatrixHelper::getRotationMatrix(mCurrentRotationMatrix44, mAryGravityCurrent, mAryMagneticCurrent);
    }
    mLock.unlock();
}

void SensorHelper::saveAryGravity(float *aryGravity) {
    mLock.lock();
    mUseVector = false;
    if (aryGravity != NULL) {
        mAryGravitySensor[0] = aryGravity[0];
        mAryGravitySensor[1] = aryGravity[1];
        mAryGravitySensor[2] = aryGravity[2];
        delete aryGravity;
    }
    mLock.unlock();
}

void SensorHelper::saveAryMagnetic(float *aryMagnetic) {
    mLock.lock();
    mUseVector = false;
    if (aryMagnetic != NULL) {
        mAryMagneticSensor[0] = aryMagnetic[0];
        mAryMagneticSensor[1] = aryMagnetic[1];
        mAryMagneticSensor[2] = aryMagnetic[2];
        delete aryMagnetic;
    }
    mLock.unlock();
}

float *SensorHelper::getCurrentRotationMatrix44() {
    return mCurrentRotationMatrix44;
}
