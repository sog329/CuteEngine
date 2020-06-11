//
// Created by Jack on 2015/11/13 0013.
//

#include <math.h>
#include "Ball.h"
#include "../platform/PlatformHelper.h"
#include <deque>

// true, 10, 90, -90, 360, 0
Ball::Ball(float r, int span, int startX, int offsetX, int startY, int offsetY) {
    mPtAryModelVertex = NULL;
    mPtAryTextureVertex = NULL;
    resize(r, span, startX, offsetX, startY, offsetY);
}

Ball::Ball() {
    mPtAryModelVertex = NULL;
    mPtAryTextureVertex = NULL;
}

Ball::~Ball() {
    delete[] mPtAryModelVertex;
    mPtAryModelVertex = NULL;
    delete[] mPtAryTextureVertex;
    mPtAryTextureVertex = NULL;
}

void Ball::resize(float r, int span, int startX, int offsetX, int startY, int offsetY) {
    show("startX=%d;   offsetX=%d;   startY=%d;   offsetY=%d", startX, offsetX, startY, offsetY);
    mStartX = startX;
    mOffsetX = offsetX;
    mStartY = startY;
    mOffsetY = offsetY;
    int vFrom = startY;
    int vTo = startY - offsetY;
    int hFrom = startX + offsetX;
    int hTo = startX;
    std::deque<float> lst;
    float n = (float)(M_PI / 180.0f);
    float sRadian = n * span + .000001; // 解决IOS等精度较高的设备上，瓦片直接存在随机缝隙
    for (int vDegree = vFrom; vDegree > vTo; vDegree = vDegree - span) {
        for (int hDegree = hFrom; hDegree > hTo; hDegree = hDegree - span) {
            float vRadian = n * vDegree;
            float hRadian = n * hDegree;
            float xozLength = r * (float)cos(vRadian);
            float x1 = xozLength * (float)cos(hRadian);
            float z1 = xozLength * (float)sin(hRadian);
            float y1 = r * (float)sin(vRadian);
            xozLength = r * (float)cos(vRadian - sRadian);
            float x2 = xozLength * (float)cos(hRadian);
            float z2 = xozLength * (float)sin(hRadian);
            float y2 = r * (float)sin(vRadian - sRadian);
            xozLength = r * (float)cos(vRadian - sRadian);
            float x3 = xozLength * (float)cos(hRadian - sRadian);
            float z3 = xozLength * (float)sin(hRadian - sRadian);
            float y3 = r * (float)sin(vRadian - sRadian);
            xozLength = r * (float)cos(vRadian);
            float x4 = xozLength * (float)cos(hRadian - sRadian);
            float z4 = xozLength * (float)sin(hRadian - sRadian);
            float y4 = r * (float)sin(vRadian);
            lst.push_back(x1);
            lst.push_back(y1);
            lst.push_back(z1);
            lst.push_back(x2);
            lst.push_back(y2);
            lst.push_back(z2);
            lst.push_back(x4);
            lst.push_back(y4);
            lst.push_back(z4);
            lst.push_back(x4);
            lst.push_back(y4);
            lst.push_back(z4);
            lst.push_back(x2);
            lst.push_back(y2);
            lst.push_back(z2);
            lst.push_back(x3);
            lst.push_back(y3);
            lst.push_back(z3);
        }
    }
    delete mPtAryModelVertex;
    mPtAryModelVertex = new float[lst.size()];
    for (int i = 0; i < lst.size(); i++) {
        mPtAryModelVertex[i] = lst[i];
    }
    mVertexNum = (int) (lst.size()) / 3;
    // 纹理坐标
    int bw = (hFrom - hTo) / span;
    int bh = (vFrom - vTo) / span;
    delete mPtAryTextureVertex;
    mPtAryTextureVertex = new float[bw * bh * 6 * 2];
    float sizew = 1.0f / bw;//列数
    float sizeh = 1.0f / bh;//行数
    int c = 0;
    for (int i = 0; i < bh; i++) {
        for (int j = 0; j < bw; j++) {
            //每行列一个矩形，由两个三角形构成，共六个点，12个纹理坐标
            float s = j * sizew;
            float t = i * sizeh;
            mPtAryTextureVertex[c++] = s;
            mPtAryTextureVertex[c++] = t;
            mPtAryTextureVertex[c++] = s;
            mPtAryTextureVertex[c++] = t + sizeh;
            mPtAryTextureVertex[c++] = s + sizew;
            mPtAryTextureVertex[c++] = t;
            mPtAryTextureVertex[c++] = s + sizew;
            mPtAryTextureVertex[c++] = t;
            mPtAryTextureVertex[c++] = s;
            mPtAryTextureVertex[c++] = t + sizeh;
            mPtAryTextureVertex[c++] = s + sizew;
            mPtAryTextureVertex[c++] = t + sizeh;
        }
    }
}

float *Ball::getPtAryModelVertex() {
    return mPtAryModelVertex;
}

float *Ball::getPtAryTextureVertex() {
    return mPtAryTextureVertex;
}

int Ball::getVertexNum() {
    return mVertexNum;
}

int Ball::getStartX() {
    return mStartX;
}

int Ball::getOffsetX() {
    return mOffsetX;
}

int Ball::getStartY() {
    return mStartY;
}

int Ball::getOffsetY() {
    return mOffsetY;
}

void Ball::getTileInfo(int tileLevel, int *ptRow, int *ptColumn) {
    switch (tileLevel) {
        case 5:
            *ptRow = 8;
            *ptColumn = 16;
            break;
        case 4:
            *ptRow = 4;
            *ptColumn = 8;
            break;
        case 3:
            *ptRow = 2;
            *ptColumn = 4;
            break;
        case 2:
            *ptRow = 1;
            *ptColumn = 2;
            break;
        default:
            *ptRow = 1;
            *ptColumn = 1;
            break;
    }
}


string Ball::getTilePath(string url, int row, int column, int tileLevel) {
    char ptChar[128];
    sprintf(ptChar, url.c_str(), row, column, tileLevel);
    return string(ptChar);
}
