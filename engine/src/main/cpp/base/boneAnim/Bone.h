//
// Created by Jack on 15/12/4.
//

#ifndef ANDROIDDEMO_BONE_H
#define ANDROIDDEMO_BONE_H

#include <string>
#include <deque>
#include "BoneAnim.h"
#include "../../app/bone/PgBoneAnim.h"

using std::string;
using std::deque;

class Bone {
private:
    int mPicLeft;
    int mPicTop;
    int mPicRight;
    int mPicBottom;
    float mTextureLeft;
    float mTextureTop;
    float mTextureWidth;
    float mTextureHeight;

    int mAlpha;

    float mRotateDegree;
    int mDesignRotateX;
    int mDesignRotateY;
    int mActualRotateX;
    int mActualRotateY;

    int mDesignLeft;
    int mDesignRight;
    int mDesignTop;
    int mDesignBottom;

    int mActualLeft;
    int mActualRight;
    int mActualTop;
    int mActualBottom;

    deque<BoneAnim *> mLstBoneAnim;

    BoneAnim *getBoneAnim(float percent);

    void buildActualCoordinate(float scale, int top, int left);

    float getGlCoordinateX(int screenX, int screenW);

    float getGlCoordinateY(int screenY, int screenH);

public:
    Bone();

    virtual ~Bone();

    void setPicInfo(int left, int top, int w, int h, int totalW, int totalH);

    void onDraw(float percent, float scale, int left, int top, int w, int h, PgBoneAnim *ptProgram);

    void setRect(int left, int top, int right, int bottom);

    void setAlpha(int alpha);

    void setRotate(float rotate, int x, int y);

    void addBoneAnim(BoneAnim *ptBoneAnim);

    BoneAnim *getLastBoneAnim();

    int getBonePicWidth();

    int getBonePicHeight();
};

#endif //ANDROIDDEMO_BONE_H
