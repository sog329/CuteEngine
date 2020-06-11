//
// Created by Jack on 15/12/24.
//

#ifndef ANDROIDDEMO_LYVRBALL_H
#define ANDROIDDEMO_LYVRBALL_H


#include "../../base/view/ILayer.h"
#include "../../base/program/PgBall.h"
#include <map>

class LyVrBall : public ILayer {
private:
    PgBall mPgBall;
    int mTileLevel;

//    std::map<int, string> mMapUrl;

//    void updateTile(float rotateCenterX, float rotateCenterY);

public:
    LyVrBall(int viewId, int threadNum);

    ~LyVrBall();

    void setTileLevel(int level);

    bool onDraw(long drawTime);

    void onSizeChange(int w, int h);

    void initProgram();

    void updateItem();

    struct Data {
    public:
        string picUrl;
        string picId;
    };

};


#endif //ANDROIDDEMO_LYVRBALL_H
