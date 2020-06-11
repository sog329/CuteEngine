//
// Created by Jack on 2015/11/14 0014.
//

#ifndef BASE_SCBALL_H
#define BASE_SCBALL_H


#include "../../base/util/ThreadLock.h"
#include "../../base/util/BmpHelper.h"
#include "../../base/view/ILayer.h"
#include "../../base/view/ILyListView.h"
#include "../../base/program/PgRect.h"
#include "../../base/program/PgBackground.h"
#include "../../base/program/PgBall.h"
#include <deque>

class LyListBall : public ILyListView {
private:
    PgBall mPgBall;
//    PgRect mPgRect;
    PgBackground mPgText;
public:
    LyListBall(int viewId, int threadNum);

    ~LyListBall();

    bool onDraw(long drawTime);

    void onSizeChange(int w, int h);

    void initProgram();

    void updateItem();

    string getDataId(int index);

    bool onItemGetBmp(string itemId, BmpHelper *ptBmpHelper);

    struct Data {
    public:
        string mDataId;
        string mPicId;
        string mPicUrl;
        string mNameStr;
        string mNameTvId;
    };

private:
    Item *getItemObject();
};


#endif //BASE_SCBALL_H
