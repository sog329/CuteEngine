//
// Created by Jack on 15/11/22.
//

#ifndef BASE_LYBALL_H
#define BASE_LYBALL_H

#include "../../base/view/ILayer.h"
#include "ZoomHelper.h"
#include "../../base/program/PgBall.h"
#include <map>

class LyBall : public ILayer {
private:
    PgBall mPgBall;

    std::map<int, string> mMapUrl;

    float mRotateCenterX;
    float mRotateCenterY;
    float mMaxRotateOffsetX;
    float mMaxRotateOffsetY;
    float mRotateOffsetX;
    float mRotateOffsetY;

    float mStartX;
    float mStartY;
    float mOffsetX;
    float mOffsetY;

    int mTileLevel;

    void resetMaxRotateOffset();

    void judgeRotate();

    ZoomHelper mZoomHelper;

    void updateTile(float rotateCenterX, float rotateCenterY);
public:
    LyBall(int viewId, int threadNum, int startX, int offsetX, int startY, int offsetY);

    ~LyBall();

    bool onDraw(long drawTime);

    void onSizeChange(int w, int h);

    void initProgram();

    void updateItem();

    bool judgeTouchEvent();

    void setBallAngle(int startX, int offsetX, int startY, int offsetY);

    void setTileLevel(int level);

    struct Data {
    public:
        string picUrl;
        string picId;
    };
};


#endif //BASE_LYBALL_H
