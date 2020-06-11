//
// Created by Jack on 2015/12/11 0011.
//

#ifndef ANDROIDDEMO_VECTORHELPER_H
#define ANDROIDDEMO_VECTORHELPER_H


class SlerpHelper {
public:
    static const float ERROR_RANGE; // 允许的标准四元数模的误差
    static float mQuaternionFactor;

    static void buildStandardVector(float *ptVector);

    static void slerpQuaternion(float *ptVectorCurrent, float *ptVectorActual);

    static void slerpAry(float *ptAryCurrent, float *ptArySensor, float distance, float factor);
};


#endif //ANDROIDDEMO_VECTORHELPER_H
