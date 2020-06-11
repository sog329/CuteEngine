//
// Created by Jack on 15/11/12.
//

#include <stddef.h>
#include "BmpHelper.h"
#include "Gl2Helper.h"

BmpHelper::BmpHelper() {
    setBmpInfo(GL_RGBA, GL_UNSIGNED_BYTE);
    mPtData = NULL;
    mWidth = 0;
    mHeight = 0;
}

BmpHelper::~BmpHelper() {
    delete mPtData;
    mPtData = NULL;
}

void BmpHelper::setData(void *data) {
    delete mPtData;
    mPtData = (unsigned char *) data;
}

void BmpHelper::setSize(int w, int h) {
    mWidth = w;
    mHeight = h;
}

int BmpHelper::getWidth() {
    return mWidth;
}

int BmpHelper::getHeight() {
    return mHeight;
}

void *BmpHelper::getData() {
    return mPtData;
}

void BmpHelper::setBmpInfo(GLint format, GLint type) {
    mFormat = format;
    mType = type;
}

GLint BmpHelper::getFormat() {
    return mFormat;
}

GLint BmpHelper::getType() {
    return mType;
}