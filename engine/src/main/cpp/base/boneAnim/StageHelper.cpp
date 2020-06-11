//
// Created by Jack on 2015/12/5 0005.
//

#include "StageHelper.h"
#include "../platform/PlatformHelper.h"

std::map<string, Stage *> StageHelper::mMapStage;
std::map<string, float> StageHelper::mMapPercent;
ThreadLock StageHelper::mLock;

void StageHelper::buildStage(string id) {
    mLock.lock();
    stopWithoutLock(id);
    Stage *mPtStage = new Stage(id);
    mMapStage.insert(std::pair<string, Stage *>(id, mPtStage));
    mMapPercent.insert(std::pair<string, float>(id, 0));
    mLock.unlock();
}

void StageHelper::setStageSize(string id, int w, int h) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        it->second->setDesignSize(w, h);
    }
    mLock.unlock();
}

void StageHelper::buildActor(string id) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = new Actor();
        it->second->addActor(ptActor);
    }
    mLock.unlock();
}

void StageHelper::buildBone(string id) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = new Bone();
            ptActor->addBone(ptBone);
        }
    }
    mLock.unlock();
}

void StageHelper::setBonePicInfo(string id, int left, int top, int w, int h, int totalW, int totalH) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                ptBone->setPicInfo(left, top, w, h, totalW, totalH);
            }
        }
    }
    mLock.unlock();
}

void StageHelper::buildBoneAnim(string id) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                BoneAnim *ptBoneAnim = new BoneAnim();
                ptBone->addBoneAnim(ptBoneAnim);
            }
        }
    }
    mLock.unlock();
}

void StageHelper::setBoneAnimRunPercent(string id, float startPercent, float endPercent, bool isShow) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                BoneAnim *ptBoneAnim = ptBone->getLastBoneAnim();
                if (ptBoneAnim != NULL) {
                    ptBoneAnim->setRunPercent(startPercent, endPercent, isShow);
                }
            }
        }
    }
    mLock.unlock();
}

void StageHelper::setBoneAnimInterpolator(string id, int interpolator) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                BoneAnim *ptBoneAnim = ptBone->getLastBoneAnim();
                if (ptBoneAnim != NULL) {
                    ptBoneAnim->setInterpolator(interpolator);
                }
            }
        }
    }
    mLock.unlock();
}

void StageHelper::setBoneAnimRect(string id, float fromScaleX, float fromScaleY, float toScaleX, float toScaleY, int fromCenterX, int fromCenterY, int toCenterX, int toCenterY) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                BoneAnim *ptBoneAnim = ptBone->getLastBoneAnim();
                if (ptBoneAnim != NULL) {
                    int picW = ptBone->getBonePicWidth();
                    int picH = ptBone->getBonePicHeight();
                    ptBoneAnim->setRect(fromScaleX, fromScaleY, toScaleX, toScaleY, fromCenterX, fromCenterY, toCenterX, toCenterY, picW, picH);
                }
            }
        }
    }
    mLock.unlock();
}

void StageHelper::setBoneAnimAlpha(string id, int from, int to) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                BoneAnim *ptBoneAnim = ptBone->getLastBoneAnim();
                if (ptBoneAnim != NULL) {
                    ptBoneAnim->setAlpha(from, to);
                }
            }
        }
    }
    mLock.unlock();
}

void StageHelper::setBoneAnimRotate(string id, float from, float to, int rotateX, int rotateY) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        Actor *ptActor = it->second->getLastActor();
        if (ptActor != NULL) {
            Bone *ptBone = ptActor->getLastBone();
            if (ptBone != NULL) {
                BoneAnim *ptBoneAnim = ptBone->getLastBoneAnim();
                if (ptBoneAnim != NULL) {
                    ptBoneAnim->setRotate(from, to, rotateX, rotateY);
                }
            }
        }
    }
    mLock.unlock();
}

void StageHelper::onDraw(string id, float percent) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        if (it->second != NULL) {
            it->second->onDraw(percent, NULL);
        }
    }
    mLock.unlock();
}

void StageHelper::onViewSizeChange(string id, int w, int h, int left, int top) {
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        if (it->second != NULL) {
            it->second->onViewSizeChange(w, h, left, top);
        }
    }
    mLock.unlock();
}

void StageHelper::stop(string id) {
    mLock.lock();
    stopWithoutLock(id);
    mLock.unlock();
}

void StageHelper::stopWithoutLock(string id) {
    std::map<string, Stage *>::iterator itStage = mMapStage.find(id);
    if (itStage != mMapStage.end()) {
        delete itStage->second;
        mMapStage.erase(itStage);
    }
    std::map<string, float>::iterator itPercent = mMapPercent.find(id);
    if (itPercent != mMapPercent.end()) {
        mMapPercent.erase(itPercent);
    }
}

Stage *StageHelper::popStage(string id) {
    Stage *ptStage = NULL;
    mLock.lock();
    std::map<string, Stage *>::iterator it = mMapStage.find(id);
    if (it != mMapStage.end()) {
        ptStage = it->second;
        mMapStage.erase(it);
    }
    mLock.unlock();
    return ptStage;
}

float StageHelper::getPercent(string id) {
    float percent = 0;
    mLock.lock();
    std::map<string, float>::iterator itPercent = mMapPercent.find(id);
    if (itPercent != mMapPercent.end()) {
        percent = itPercent->second;
    }
    mLock.unlock();
    return percent;
}

void StageHelper::setPercent(string id, float percent) {
    mLock.lock();
    std::map<string, float>::iterator it = mMapPercent.find(id);
    if (it != mMapPercent.end()) {
        mMapPercent.erase(it);
    }
    mMapPercent.insert(std::pair<string, float>(id, percent));
    mLock.unlock();
}