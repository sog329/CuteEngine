//
// Created by Jack on 15/12/4.
//

#ifndef ANDROIDDEMO_STAGE_H
#define ANDROIDDEMO_STAGE_H

#include <string>
#include <deque>
#include "Actor.h"

using std::string;
using std::deque;

class Stage {
private:
    static const int LayoutModeMatchY = 4;

    int mActualWidth; // 实际画布的宽
    int mActualHeight; // 实际画布的高
//    int mPaddingLeft;
//    int mPaddingTop;

    int mDesignWidth;
    int mDesignHeight;

    int mLayoutMode;
    float mStageScale;
    int mStageLeft;
    int mStageTop;

    deque<Actor *> mLstActor;

    string mId;

public:
    Stage(string id);

    virtual ~Stage();

    void onViewSizeChange(int w, int h, int left, int top);

    void setDesignSize(int w, int h);

    void resizeStage();

    void onDraw(float percent, PgBoneAnim* ptProgram);

    void addActor(Actor *ptActor);

    Actor *getLastActor();

    string getId();
};


#endif //ANDROIDDEMO_STAGE_H
