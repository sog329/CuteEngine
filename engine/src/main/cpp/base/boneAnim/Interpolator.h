//
// Created by Jack on 15/12/4.
//

#ifndef ANDROIDDEMO_INTERPOLATOR_H
#define ANDROIDDEMO_INTERPOLATOR_H


class Interpolator {
public:
    static const int Normal = 0;
    static const int Accelerate = 1;
    static const int Decelerate = -1;
    static float getPercent(int interpolator, float percent);
};


#endif //ANDROIDDEMO_INTERPOLATOR_H
