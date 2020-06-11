//
// Created by Jack on 15/11/22.
//

#ifndef BASE_PGRECT_H
#define BASE_PGRECT_H


#include "IProgram.h"

class PgRect : public IProgram {
private:
    GLuint mTextureId;
    GLint mHandlePosition;

    GLint mHandleColorR;
    GLint mHandleColorG;
    GLint mHandleColorB;
    GLint mHandleColorA;

    float mColorRGBA[4];

    void initSelf();

public:
    PgRect();

    ~PgRect();

    void drawSelf(void *obj, long drawTime);

    void setColor(float r, float g, float b, float a);

    void onSizeChange(int w, int h);

    const char *getVertexShader();

    const char *getFragmentShader();
};


#endif //BASE_PGRECT_H
