//
// Created by Jack on 2015/11/14 0014.
//

#include "PgBall.h"
#include "../util/MatrixHelper.h"
#include "../util/Gl2Helper.h"
#include "../platform/PlatformHelper.h"

using CuteEngine::Gl2Helper;

PgBall::PgBall() {
    mFovDegreeX = 0;
    mFovDegreeY = 0;
    mNear = 3;
    mRatio = 1;
}

PgBall::~PgBall() {
}

void PgBall::initSelf() {
    mHandlePosition = glGetAttribLocation(mPgId, "aPosition");
    Gl2Helper::checkGlError("glGetAttribLocation: aPosition");

    mHandleTexCoord = glGetAttribLocation(mPgId, "aTexCoord");
    Gl2Helper::checkGlError("glGetAttribLocation: aTexCoord");

    mHandleMtProjection = glGetUniformLocation(mPgId, "uMtProjection");
    Gl2Helper::checkGlError("glGetUniformLocation: uMtProjection");

    mHandleMtCamera = glGetUniformLocation(mPgId, "uMtCamera");
    Gl2Helper::checkGlError("glGetUniformLocation: uMtCamera");

    mHandleMtCurrent = glGetUniformLocation(mPgId, "uMtCurrent");
    Gl2Helper::checkGlError("glGetUniformLocation: uMtCurrent");

    mHandleMtCurrentExtra = glGetUniformLocation(mPgId, "uMtCurrentExtra");
    Gl2Helper::checkGlError("glGetUniformLocation: uMtCurrentExtra");

    mHandleAlpha = glGetUniformLocation(mPgId, "alpha");
    Gl2Helper::checkGlError("glGetUniformLocation: alpha");

    mHandlerTexture = glGetUniformLocation(mPgId, "sTexture");
    Gl2Helper::checkGlError("glGetUniformLocation: mHandlerTexture..");
}

void PgBall::drawSelf(void *obj, long drawTime) {
    if (obj != NULL) {
        PgBall::DrawInfo *drawInfo = (DrawInfo *) obj;
        GLuint textureId = drawInfo->getTextureId();
        if (Gl2Helper::isTextureReady(textureId)) {
            // 关闭深度测试
            glDisable(GL_DEPTH_TEST);
            // 只画前面，不画背面
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);

            glUniformMatrix4fv(mHandleMtProjection, 1, GL_FALSE, mMatrixProjection);

            glUniformMatrix4fv(mHandleMtCamera, 1, GL_FALSE, drawInfo->getMatrixCamera());

            glUniformMatrix4fv(mHandleMtCurrentExtra, 1, GL_FALSE, drawInfo->getMatrixCurrentExtra());

            float alpha = 1;
            float scale = 1;
            if (drawInfo->mAnimHelper.run(drawTime)) {
                alpha = drawInfo->mAnimHelper.getAlpha();
                if (alpha < 0 || alpha > 1) {
                    alpha = 1;
                }
                scale = drawInfo->mAnimHelper.getScale();
            }
            if (alpha != 1) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            } else {
                glDisable(GL_BLEND);
            }
            glUniform1f(mHandleAlpha, alpha);
            MatrixHelper::scaleM(drawInfo->getMatrixCurrent(), scale, scale, scale);
            glUniformMatrix4fv(mHandleMtCurrent, 1, GL_FALSE, drawInfo->getMatrixCurrent());

            glVertexAttribPointer(mHandlePosition, 3, GL_FLOAT, GL_FALSE, 12, drawInfo->getBall()->getPtAryModelVertex());
            glEnableVertexAttribArray(mHandlePosition);

            glVertexAttribPointer(mHandleTexCoord, 2, GL_FLOAT, GL_FALSE, 8, drawInfo->getBall()->getPtAryTextureVertex());
            glEnableVertexAttribArray(mHandleTexCoord);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, drawInfo->getTextureId());
            glUniform1i(mHandlerTexture, 0);

            glDrawArrays(GL_TRIANGLES, 0, drawInfo->getBall()->getVertexNum());
//            glDrawArrays(GL_LINES, 0, drawInfo->getBall()->getVertexNum());
            Gl2Helper::checkGlError("glDrawArrays");

            glDisable(GL_DEPTH_TEST);
            glBindTexture(GL_TEXTURE_2D, GL_NONE);
            glDisable(GL_BLEND);
            glDisable(GL_CULL_FACE);
        }
    }
}

void PgBall::onSizeChange(int w, int h) {
    mRatio = (float) w / h;
    resetFov();
}

void PgBall::setNear(float near) {
    mNear = near;
    resetFov();
}

void PgBall::resetFov() {
    MatrixHelper::frustumM(mMatrixProjection, -mRatio, mRatio, -1, 1, mNear, 10);
    mFovDegreeY = 2 * atan(1.0 / mNear) * 180 / M_PI;
    mFovDegreeX = mRatio * mFovDegreeY;
}

const char *PgBall::getVertexShader() {
    return "attribute vec3 aPosition;\n"
            "uniform mat4 uMtProjection;\n"
            "uniform mat4 uMtCamera;\n"
            "uniform mat4 uMtCurrentExtra;\n"
            "uniform mat4 uMtCurrent;\n"
            "attribute vec2 aTexCoord;\n"
            "varying vec2 vTexCoord;\n"
            "void main() {\n"
            "  vec4 tmpPos = uMtProjection*uMtCamera*uMtCurrent*uMtCurrentExtra*vec4(aPosition, 1.0);\n"
            "  gl_Position = tmpPos;\n"
            "  vec2 tmpTex = aTexCoord;\n"
            "  vTexCoord = tmpTex;\n"
            "}\n";
}

const char *PgBall::getFragmentShader() {
    return "precision mediump float;\n"
            "uniform float alpha;\n"
            "uniform sampler2D sTexture;\n"
            "varying vec2 vTexCoord;\n"
            "void main() {\n"
            "  vec2 tmp = vTexCoord;\n"
            "  tmp.x = 1.0 - tmp.x;\n"
            "  vec4 color = texture2D(sTexture, tmp);\n"
            "  color.a = alpha;\n"
            "  gl_FragColor = color;\n"
            "}\n";
}

PgBall::DrawInfo::DrawInfo(PicLoader* ptPicLoader, float startX, float offsetX, float startY, float offsetY) : Pic(ptPicLoader) {
    //    MatrixHelper::setLookAtM(mMatrixCamera, 0, 0, 4, 0, 0, 0, 0, 1, 0);//3
    MatrixHelper::setLookAtM(mMatrixCamera, 0, 0, BALL_RADIUS, 0, 0, 0, 0, 1, 0);//3
    MatrixHelper::setIdentityM(mMatrixCurrent);
    MatrixHelper::setIdentityM(mMatrixCurrentExtra);
    mPtBall = new Ball(BALL_RADIUS, 5, startX, offsetX, startY, offsetY);

    // 两个摄像机角度角度差，即各偏移rotate角度
    float rotate = 1 * M_PI / 180;
    mVrEyeX = BALL_RADIUS * sin(rotate);
    mVrEyeZ = BALL_RADIUS * cos(rotate);
}

PgBall::DrawInfo::~DrawInfo() {
    show("~DrawInfo");
    delete mPtBall;
}

float *PgBall::DrawInfo::getMatrixCamera() {
    return mMatrixCamera;
}

float *PgBall::DrawInfo::getMatrixCurrent() {
    return mMatrixCurrent;
}

float *PgBall::DrawInfo::getMatrixCurrentExtra() {
    return mMatrixCurrentExtra;
}

Ball *PgBall::DrawInfo::getBall() {
    return mPtBall;
}

void PgBall::DrawInfo::prepareDraw(bool isLeft, int width, int height) {
    if (isLeft) {
        glViewport(0, 0, width, height / 2);
        MatrixHelper::setLookAtM(mMatrixCamera, -mVrEyeX, 0, mVrEyeZ, 0, 0, 0, 0, 1, 0);
    } else {
        glViewport(0, height / 2, width, height / 2);
        MatrixHelper::setLookAtM(mMatrixCamera, mVrEyeX, 0, mVrEyeZ, 0, 0, 0, 0, 1, 0);
    }
}

float PgBall::getFovDegreeX() {
    return mFovDegreeX;
}

float PgBall::getFovDegreeY() {
    return mFovDegreeY;
}

float PgBall::getCameraK() {
    return 2; // 2 * BALL_RADIUS / BALL_RADIUS
}