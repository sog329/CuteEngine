//
// Created by Jack on 2016/2/13 0013.
//

#ifndef ANDROIDDEMO_SPRINGHELPER_H
#define ANDROIDDEMO_SPRINGHELPER_H


class SpringHelper {
private:
    const float SPEED = .0006;

    const float MAX = 9;

    float mSpeedFactor;

    float mOffsetPercent; // 当前弹性系数，[-1, 1], 0为稳定态

    int mMaxOffset;
    int mOffset;

    long mLastTime;

    enum SpringType {
        None, Spring
    };

    SpringType mType;

    // 每帧调用，更新偏移量
    void updateOffset();

public:
    SpringHelper();

    ~SpringHelper();

    void onSizeChange(int w, int h);

    int getOffset();

    // 当没有手势时每帧调用
    void moveToIdle(bool canMove);

    int setScrollY(int scrollFrom, int scrollTo, int maxScrollY, int viewId, int viewHeight);
};


#endif //ANDROIDDEMO_SPRINGHELPER_H
