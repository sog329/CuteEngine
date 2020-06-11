//
// Created by Jack on 2016/1/3 0003.
//

#ifndef ANDROIDDEMO_LYBONEANIM2_H
#define ANDROIDDEMO_LYBONEANIM2_H


#include "../../base/view/ILayer.h"
#include "PgBoneAnim.h"
#include "../../base/boneAnim/Stage.h"

class LyBoneAnim : public ILayer {
private:
    PgBoneAnim mPgBoneAnim;
    Stage *mPtStage;
public:
    LyBoneAnim(int viewId);

    ~LyBoneAnim();

    bool onDraw(long drawTime);

    void onSizeChange(int w, int h);

    void initProgram();

    void checkDataChange();

    void updateItem();

    bool onItemGetBmp(string itemId, BmpHelper *ptBmpHelper);

    struct Data {
    public:
        string id;
        string xmlUrl;
        string picUrl;
    };
};


#endif //ANDROIDDEMO_LYBONEANIM2_H
