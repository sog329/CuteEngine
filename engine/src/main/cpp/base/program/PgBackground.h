//
// Created by Jack on 2015/11/11 0011.
//

#ifndef BASE_OLD_PGBACKGROUND_H
#define BASE_OLD_PGBACKGROUND_H

#include "IProgram.h"
#include "../util/BmpHelper.h"

class PgBackground : public IProgram {
private:
    bool mIsAlpha;

    GLint mHandlePosition;
    GLint mHandleTexCoord;

    GLfloat mAryRectVertex[12];
    static GLfloat mAryTexcoord[8];

    void initSelf();

    void drawSelf(void *obj, long drawTime);

public:
    PgBackground();

    ~PgBackground();

    void isAlpha(bool isAlpha);

    void setPosition(float left, float top, float w, float h);

    void onSizeChange(int w, int h);

    const char *getVertexShader();

    const char *getFragmentShader();
};


#endif //BASE_OLD_PGBACKGROUND_H
