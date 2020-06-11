//
// Created by Jack on 15/12/4.
//

#ifndef ANDROIDDEMO_BONEANIM_H
#define ANDROIDDEMO_BONEANIM_H

class BoneAnim {
private:
    float mStartPercent;
    float mEndPercent;
    float mDurationPercent;

    bool mIsShow;

    int mInterpolator;

    int mLeftFrom;
    int mLeftChange;
    int mTopFrom;
    int mTopChange;
    int mRightFrom;
    int mRightChange;
    int mBottomFrom;
    int mBottomChange;

    float mRotateFrom;
    float mRotateChange;
    int mRotateX;
    int mRotateY;

    int mAlphaFrom;
    int mAlphaChange;

public:
    BoneAnim();
    virtual ~BoneAnim();
    void setRunPercent(float startPercent, float endPercent, bool isShow);
    bool isShow();
    void setInterpolator(int interpolator);
    void setRect(
            float fromScaleX, float fromScaleY, float toScaleX, float toScaleY,
            int fromCenterX, int fromCenterY, int toCenterX, int toCenterY,
            int picW, int picH
    );
    void setAlpha(int from, int to);
    void setRotate(float from, float to, int rotateX, int rotateY);

    void run2d(void *ptBone, float percent);
    bool isInAnim(float percent, bool isLast);
};


#endif //ANDROIDDEMO_BONEANIM_H
