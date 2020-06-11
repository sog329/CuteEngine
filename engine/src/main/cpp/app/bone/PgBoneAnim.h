//
// Created by Jack on 15/12/7.
//

#ifndef ANDROIDDEMO_PGBONEANIM_H
#define ANDROIDDEMO_PGBONEANIM_H


#include "../../base/program/IProgram.h"
#include "../../base/picLoader/Pic.h"

class PgBoneAnim : public IProgram {
public:
    class DrawInfo : public Pic {
    public:
        DrawInfo(PicLoader* ptPicLoader);

        ~DrawInfo();

    };

private:
    GLint mHandlePosition;
    GLint mHandleTexCoord;
    GLint mHandleAryTexPosition;
    GLint mHandleMtCurrent;
    float mMatrixCurrent[16];
    GLint mHandleAlpha;

    void initSelf();

    float mAryTexPosition[4]; // left, w, top, h

    float mScaleX;
    float mScaleY;
    float mCenterX;
    float mCenterY;

    float mRotateX;
    float mRotateY;
    float mRotate;

    float mAlpha;

    DrawInfo *mPtDrawInfo;

public:
    PgBoneAnim();

    ~PgBoneAnim();

    void drawSelf(void *obj, long drawTime);

    void setTexPosition(float left, float width, float top, float height);

    void setVerPosition(float centerX, float centerY, float scaleX, float scaleY);

    void setRotate(float rotate, float rotateX, float rotateY);

    void setDrawInfo(DrawInfo *ptDrawInfo);

    void onSizeChange(int w, int h);

    void setAlpha(float alpha);

    const char *getVertexShader();

    const char *getFragmentShader();
};


#endif //ANDROIDDEMO_PGBONEANIM_H
