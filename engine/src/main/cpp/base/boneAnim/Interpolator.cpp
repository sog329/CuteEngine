//
// Created by Jack on 15/12/4.
//

#include "Interpolator.h"

float Interpolator::getPercent(int interpolator, float percent) {
    if (interpolator == Accelerate) {
        percent = percent * percent;
    } else if (interpolator == Decelerate) {
        percent = 1 - (1 - percent) * (1 - percent);
    }
    return percent;
}