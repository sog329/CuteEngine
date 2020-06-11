//
// Created by Jack on 15/11/11.
//

#ifndef BASE_IPROGRAM_H
#define BASE_IPROGRAM_H

#include "../platform/PlatformHelper.h"

class IProgram {
protected:
    GLuint mPgId;
public:
    IProgram();

    ~IProgram();

    void init();

    virtual void onSizeChange(int w, int h) = 0;

    virtual const char *getVertexShader() = 0;

    virtual const char *getFragmentShader() = 0;

    void onDraw(void *obj, long drawTime);

    void startDraw(bool start);

private:
    virtual void initSelf() = 0;

    virtual void drawSelf(void *obj, long drawTime) = 0;

    bool isProgramReady();
};


#endif //BASE_IPROGRAM_H
