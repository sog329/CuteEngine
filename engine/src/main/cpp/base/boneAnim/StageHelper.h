//
// Created by Jack on 2015/12/5 0005.
//

#ifndef ANDROIDDEMO_STAGEHELPER_H
#define ANDROIDDEMO_STAGEHELPER_H


#include "Stage.h"
#include <string>
#include "map"
#include "../util/ThreadLock.h"

using std::string;

class StageHelper {
private:
    static std::map<string, Stage *> mMapStage;
    static ThreadLock mLock;
    static std::map<string, float> mMapPercent;
public:
    static void buildStage(string id);

    static void setStageSize(string id, int w, int h);

    static void buildActor(string id);

    static void buildBone(string id);

    static void setBonePicInfo(string id, int left, int top, int w, int h, int totalW, int totalH);

    static void buildBoneAnim(string id);

    static void setBoneAnimRunPercent(string id, float startPercent, float endPercent, bool isShow);

    static void setBoneAnimInterpolator(string id, int interpolator);

    static void setBoneAnimRect(
            string id,
            float fromScaleX, float fromScaleY, float toScaleX, float toScaleY,
            int fromCenterX, int fromCenterY, int toCenterX, int toCenterY
    );

    static void setBoneAnimAlpha(string id, int from, int to);

    static void setBoneAnimRotate(string id, float from, float to, int rotateX, int rotateY);

    static void onDraw(string id, float percent);

    static void onViewSizeChange(string id, int w, int h, int left, int top);

    static void stop(string id);

    static Stage *popStage(string id);

    static float getPercent(string id);

    static void setPercent(string id, float percent);

private:
    static void stopWithoutLock(string id);
};


#endif //ANDROIDDEMO_STAGEHELPER_H
