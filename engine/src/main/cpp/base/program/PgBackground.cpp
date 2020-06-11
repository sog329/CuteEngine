//
// Created by Jack on 2015/11/11 0011.
//

#include "PgBackground.h"
#include "../util/Gl2Helper.h"
#include "../picLoader/Pic.h"
#include "../util/VertexHelper.h"

using CuteEngine::Gl2Helper;

GLfloat PgBackground::mAryTexcoord[] = {1, 0, 0, 0, 0, 1, 1, 1,};

PgBackground::PgBackground() {
    mIsAlpha = false;
    VertexHelper::setIdentity(mAryRectVertex);
}

PgBackground::~PgBackground() {

}

void PgBackground::isAlpha(bool isAlpha) {
    mIsAlpha = isAlpha;
}

void PgBackground::setPosition(float left, float top, float w, float h) {
    VertexHelper::setPosition(mAryRectVertex, left, top, w, h);
}

void PgBackground::initSelf() {
    mHandlePosition = glGetAttribLocation(mPgId, "aPosition");
    Gl2Helper::checkGlError("glGetAttribLocation: aPosition");

    mHandleTexCoord = glGetAttribLocation(mPgId, "aTexCoord");
    Gl2Helper::checkGlError("glGetAttribLocation: aTexCoord");
}

void PgBackground::drawSelf(void *obj, long drawTime) {
    if (obj != NULL) {
        Pic *ptPic = (Pic *) obj;
        if (ptPic->getTextureId() != GL_NONE) {
            if (mIsAlpha) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            } else {
                glDisable(GL_BLEND);
            }

            glVertexAttribPointer(mHandlePosition, 3, GL_FLOAT, GL_FALSE, 12, mAryRectVertex);
            Gl2Helper::checkGlError("glVertexAttribPointer: mHandlePosition");
            glEnableVertexAttribArray(mHandlePosition);
            Gl2Helper::checkGlError("glEnableVertexAttribArray");

            glVertexAttribPointer(mHandleTexCoord, 2, GL_FLOAT, GL_FALSE, 8, mAryTexcoord);
            Gl2Helper::checkGlError("glVertexAttribPointer: mHandleTexCoord");
            glEnableVertexAttribArray(mHandleTexCoord);
            Gl2Helper::checkGlError("glEnableVertexAttribArray: mHandleTexCoord");

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ptPic->getTextureId());

            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            Gl2Helper::checkGlError("glDrawArrays");

            glBindTexture(GL_TEXTURE_2D, GL_NONE);
            glDisable(GL_BLEND);
        }
    }
}

void PgBackground::onSizeChange(int w, int h) {

}

const char *PgBackground::getVertexShader() {
    return "attribute vec3 aPosition;\n"
            "attribute vec2 aTexCoord;\n"
            "varying vec2 vTexCoord;\n"
            "void main() {\n"
            "  gl_Position = vec4(aPosition, 1);\n"
            "  vTexCoord = aTexCoord;\n"
            "}\n";
}

const char *PgBackground::getFragmentShader() {
    return "precision mediump float;\n"
            "uniform sampler2D sTexture;\n"
            "varying vec2 vTexCoord;\n"
            "void main() {\n"
            "  gl_FragColor = texture2D(sTexture, vTexCoord);\n"
            "}\n";
}