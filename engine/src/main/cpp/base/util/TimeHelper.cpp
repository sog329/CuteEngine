//
// Created by Jack on 2015/11/15 0015.
//

#include "TimeHelper.h"

long TimeHelper::getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}