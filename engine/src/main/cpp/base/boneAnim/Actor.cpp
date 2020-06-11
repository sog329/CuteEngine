//
// Created by Jack on 15/12/4.
//

#include "Actor.h"

Actor::Actor() {

}

Actor::~Actor() {
    for (int i = 0; i < mLstBone.size(); i++) {
        delete mLstBone[i];
    }
    mLstBone.clear();
}

void Actor::onDraw(float percent, float scale, int left, int top, int w, int h, PgBoneAnim* ptProgram) {
    for (int i = 0; i < mLstBone.size(); i++) {
        mLstBone[i]->onDraw(percent, scale, left, top, w, h, ptProgram);
    }
}

void Actor::addBone(Bone *ptBone) {
    if (ptBone != NULL) {
        mLstBone.push_back(ptBone);
    }
}

Bone *Actor::getLastBone() {
    Bone *ptBone = NULL;
    if (mLstBone.size() > 0) {
        ptBone = mLstBone.back();
    }
    return ptBone;
}
