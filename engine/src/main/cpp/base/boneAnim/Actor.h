//
// Created by Jack on 15/12/4.
//

#ifndef ANDROIDDEMO_ACTOR_H
#define ANDROIDDEMO_ACTOR_H

#include <string>
#include <deque>
#include "Bone.h"
#include "../../app/bone/PgBoneAnim.h"

using std::string;
using std::deque;

class Actor {
private:
    int mDuration;
    deque<Bone *> mLstBone;
public:
    Actor();
    virtual ~Actor();
    void onDraw(float percent, float scale, int left, int top, int w, int h, PgBoneAnim* ptProgram);
    void addBone(Bone *ptBone);

    Bone *getLastBone();
};


#endif //ANDROIDDEMO_ACTOR_H
