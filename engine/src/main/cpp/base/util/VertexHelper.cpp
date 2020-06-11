//
// Created by Jack on 2016/1/2 0002.
//

#include <stddef.h>
#include "VertexHelper.h"

void VertexHelper::setIdentity(float *ptAry) {
    setPosition(ptAry, 0, 0, 1, 1);
}

void VertexHelper::setPosition(float *ptAry, float left, float top, float w, float h) {
    if (ptAry != NULL) {
        float leftGL = -1 + left * 2;
        float rightGL = leftGL + w * 2;
        float topGL = 1 - top * 2;
        float bottomGL = topGL - h * 2;
        // 左上角
        ptAry[0] = rightGL;
        ptAry[1] = topGL;
        ptAry[2] = 0;
        ptAry[3] = leftGL;
        ptAry[4] = topGL;
        ptAry[5] = 0;
        ptAry[6] = leftGL;
        ptAry[7] = bottomGL;
        ptAry[8] = 0;
        ptAry[9] = rightGL;
        ptAry[10] = bottomGL;
        ptAry[11] = 0;
    }
}