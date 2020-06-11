//
// Created by Jack on 2015/11/14 0014.
//

#ifndef BASE_PGBALL_H
#define BASE_PGBALL_H

#include "IProgram.h"
#include "../util/BmpHelper.h"
#include "../model/Ball.h"
#include "../util/ThreadLock.h"
#include "../picLoader/Pic.h"

class PgBall : public IProgram {
private:
    float mFovDegreeX;
    float mFovDegreeY;
    float mNear;
    float mRatio;

    GLint mHandlePosition;
    GLint mHandleTexCoord;

    float mMatrixProjection[16];
    GLint mHandleMtProjection;
    GLint mHandleMtCamera;
    GLint mHandleMtCurrent;
    GLint mHandleMtCurrentExtra;
    GLint mHandleAlpha;
    GLint mHandlerTexture;

    void initSelf();

    void resetFov();

public:

    PgBall();

    ~PgBall();

    float getCameraK();

    float getFovDegreeX();

    float getFovDegreeY();

    void setNear(float near);

    void drawSelf(void *obj, long drawTime);

    void onSizeChange(int w, int h);

    const char *getVertexShader();

    const char *getFragmentShader();

    class DrawInfo : public Pic {
    private:
        Ball *mPtBall;
        float mMatrixCamera[16];
        float mMatrixCurrent[16];
        float mMatrixCurrentExtra[16];

        float mVrEyeX;
        float mVrEyeZ;
    public:
        const float BALL_RADIUS = 4;

        /**
         * startX: x轴起始角度：0
         * offsetX: x轴长度：0~360
         * startY: y轴起始角度：90
         * offsetY: y轴长度：0~180
         */
        DrawInfo(PicLoader* ptPicLoader, float startX, float offsetX, float startY, float offsetY);

        ~DrawInfo();

        float *getMatrixCamera();

        float *getMatrixCurrent();

        float *getMatrixCurrentExtra();

        Ball *getBall();

        void prepareDraw(bool isLeft, int width, int height);
    };
};


#endif //BASE_PGBALL_H
