//
// Created by Jack on 15/11/21.
//

#ifndef BASE_TOUCHHELPER_H
#define BASE_TOUCHHELPER_H


#include "ThreadLock.h"
#include <string>

using std::string;

class TouchHelper {
public:
    static const int NONE = -1;

    struct Result {
        Result() {
            viewId = NONE;
            disX = 0;
            disY = 0;
            isFling = false;
            clickX = NONE;
            clickY = NONE;
            isDoubleClick = false;
            scale = NONE;
        }

        int viewId;
        int disX;
        int disY;
        bool isFling;
        int clickX;
        int clickY;
        bool isDoubleClick;
        float scale;
        float speedX;
        float speedY;
    };

private:
    static int mId;
    static int mDisX;
    static int mDisY;
    static float mSpeedX;
    static float mSpeedY;
    static long mSpeedRecordTime;
    static ThreadLock mTouchLock;
    static float mAcceleration;
    static Result mResult;
    static int mClickX;
    static int mClickY;
    static bool mIsDoubleClick;
    static float mScale;

    static float getNewSpeed(float speed, int runTime);

public:
    static void onDown(int id, bool isDown);

    static void onClick(int id, int x, int y);

    static void onDoubleClick(int id);

    static void onZoom(int id, float scale);

    static void onScroll(int id, int disX, int disY);

    static void onFling(int id, float speedX, float speedY);

    static void stopFling(int id);

    static void buildTouchResult(int scendId);

    static Result *getPtResult(int scendId);

    struct ClickInfo {
    public:
        int viewId;
        int dataIndex;
        string dataId;
    };

    static void performClick(int viewId, int dataIndex, string dataId);

    static void *performClickInThread(void *obj);
};


#endif //BASE_TOUCHHELPER_H
