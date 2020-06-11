//
// Created by Jack on 15/12/7.
//

#include "PgBoneAnim.h"

#include "../../base/util/Gl2Helper.h"
#include "../../base/util/MatrixHelper.h"

using CuteEngine::Gl2Helper;

static const GLfloat mAryRectVertex[] = {1, 1, 0, -1, 1, 0, -1, -1, 0, 1, -1, 0,};
static const GLfloat mAryTexcoord[] = {1, 0, 0, 0, 0, 1, 1, 1,};

PgBoneAnim::PgBoneAnim() {
    MatrixHelper::setIdentityM(mMatrixCurrent);
    mPtDrawInfo = NULL;
    setAlpha(1.0);
    setRotate(0, 0, 0);
    setTexPosition(0, 0, 0, 0);
    setVerPosition(0, 0, 0, 0);
}

PgBoneAnim::~PgBoneAnim() {

}

void PgBoneAnim::initSelf() {
    mHandlePosition = glGetAttribLocation(mPgId, "aPosition");
    Gl2Helper::checkGlError("glGetAttribLocation: aPosition");

    mHandleTexCoord = glGetAttribLocation(mPgId, "aTexCoord");
    Gl2Helper::checkGlError("glGetAttribLocation: aTexCoord");

    mHandleAryTexPosition = glGetAttribLocation(mPgId, "aAryTexPosition");
    Gl2Helper::checkGlError("glGetUniformLocation: aAryTexPosition");

    mHandleMtCurrent = glGetUniformLocation(mPgId, "uMtCurrent");
    Gl2Helper::checkGlError("glGetUniformLocation: uMtCurrent");

    mHandleAlpha = glGetUniformLocation(mPgId, "uAlpha");
    Gl2Helper::checkGlError("glGetUniformLocation: uAlpha");
}

void PgBoneAnim::drawSelf(void *obj, long drawTime) {
    if (mPtDrawInfo != NULL && mAlpha > 0) {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glVertexAttribPointer(mHandlePosition, 3, GL_FLOAT, GL_FALSE, 12, mAryRectVertex);
        Gl2Helper::checkGlError("glVertexAttribPointer: mHandlePosition");
        glEnableVertexAttribArray(mHandlePosition);
        Gl2Helper::checkGlError("glEnableVertexAttribArray");

        glVertexAttribPointer(mHandleTexCoord, 2, GL_FLOAT, GL_FALSE, 8, mAryTexcoord);
        Gl2Helper::checkGlError("glVertexAttribPointer: mHandleTexCoord");
        glEnableVertexAttribArray(mHandleTexCoord);
        Gl2Helper::checkGlError("glEnableVertexAttribArray: mHandleTexCoord");

        glVertexAttrib4f(mHandleAryTexPosition, mAryTexPosition[0], mAryTexPosition[1], mAryTexPosition[2], mAryTexPosition[3]);
        Gl2Helper::checkGlError("glUniform4f: mHandleAryTexPosition");

        MatrixHelper::setIdentityM(mMatrixCurrent);
        MatrixHelper::translateM(mMatrixCurrent, mCenterX, mCenterY, 0);
        MatrixHelper::scaleM(mMatrixCurrent, mScaleX, mScaleY, 1);
        if (mRotate != 0) {
            float dX = (mRotateX - mCenterX)/mScaleX;
            float dY = (mRotateY - mCenterY)/mScaleY;
            MatrixHelper::translateM(mMatrixCurrent, dX, dY, 0);
            MatrixHelper::rotateM(mMatrixCurrent, -mRotate, 0, 0, 1);
            MatrixHelper::translateM(mMatrixCurrent, -dX, -dY, 0);
        }
        glUniformMatrix4fv(mHandleMtCurrent, 1, GL_FALSE, mMatrixCurrent);

        glUniform1f(mHandleAlpha, mAlpha);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mPtDrawInfo->getTextureId());
        Gl2Helper::checkGlError("glBindTexture: mPtDrawInfo->getTextureId()");

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        Gl2Helper::checkGlError("glDrawArrays");
        glDisable(GL_BLEND);
    }
}

void PgBoneAnim::onSizeChange(int w, int h) {
}

const char *PgBoneAnim::getVertexShader() {
    return "uniform mat4 uMtCurrent;\n"
            "attribute vec4 aAryTexPosition;\n"
            "varying vec4 vAryTexPosition;\n"
            "attribute vec3 aPosition;\n"
            "attribute vec2 aTexCoord;\n"
            "varying vec2 vTexCoord;\n"
            "void main() {\n"
            "  gl_Position = uMtCurrent*vec4(aPosition, 1);\n"
            "  vTexCoord = aTexCoord;\n"
            "  vAryTexPosition = aAryTexPosition;\n"
            "}\n";
}

const char *PgBoneAnim::getFragmentShader() {
    return "precision mediump float;\n"
            "varying vec4 vAryTexPosition;\n"
            "uniform sampler2D sTexture;\n"
            "varying vec2 vTexCoord;\n"
            "uniform float uAlpha;"
            "void main() {\n"
            "  float x = vAryTexPosition[0] + vAryTexPosition[1]*vTexCoord.x;\n"
            "  float y = vAryTexPosition[2] + vAryTexPosition[3]*vTexCoord.y;\n"
            "  vec2 tc = vec2(x, y);\n"
            "  vec4 color = texture2D(sTexture, tc);\n"
            "  color.r = color.r*uAlpha;\n"
            "  color.g = color.g*uAlpha;\n"
            "  color.b = color.b*uAlpha;\n"
            "  color.a = color.a*uAlpha;\n"
            "  gl_FragColor = color;\n"
            "}\n";
}

PgBoneAnim::DrawInfo::DrawInfo(PicLoader* ptPicLoader) : Pic(ptPicLoader) {
    mTextureId = GL_NONE;
}

PgBoneAnim::DrawInfo::~DrawInfo() {
    show("~DrawInfo");
}

void PgBoneAnim::setTexPosition(float left, float width, float top, float height) {
    mAryTexPosition[0] = left;
    mAryTexPosition[1] = width;
    mAryTexPosition[2] = top;
    mAryTexPosition[3] = height;
}

void PgBoneAnim::setVerPosition(float centerX, float centerY, float scaleX, float scaleY) {
    mCenterX = centerX;
    mCenterY = centerY;
    mScaleX = scaleX;
    mScaleY = scaleY;
}

void PgBoneAnim::setDrawInfo(DrawInfo *ptDrawInfo) {
    mPtDrawInfo = ptDrawInfo;
}

void PgBoneAnim::setAlpha(float alpha) {
    mAlpha = alpha;
}

void PgBoneAnim::setRotate(float rotate, float rotateX, float rotateY) {
    mRotate = rotate;
    mRotateX = rotateX;
    mRotateY = rotateY;
}