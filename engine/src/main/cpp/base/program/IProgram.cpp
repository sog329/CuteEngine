//
// Created by Jack on 15/11/11.
//

#include "IProgram.h"
#include "../util/Gl2Helper.h"

using CuteEngine::Gl2Helper;

IProgram::IProgram() {
    mPgId = GL_NONE;
    show("IProgram()");
}

IProgram::~IProgram() {
    show("~IProgram()");
}

bool IProgram::isProgramReady() {
    return mPgId != GL_NONE;
}

void IProgram::onDraw(void *obj, long drawTime) {
    if (isProgramReady()) {
        glUseProgram(mPgId);
        Gl2Helper::checkGlError("glUseProgram");
        drawSelf(obj, drawTime);
        glUseProgram(GL_NONE);
    }
}

void IProgram::startDraw(bool start) {
    if (start) {
        if (isProgramReady()) {
            glUseProgram(mPgId);
            Gl2Helper::checkGlError("glUseProgram");
        }
    } else {
        glUseProgram(GL_NONE);
    }
}

void IProgram::init() {
    Gl2Helper::createProgram(&mPgId, getVertexShader(), getFragmentShader());
    initSelf();
}