//
// Created by Jack on 15/11/12.
//

#ifndef BASE_BMPHELPER_H
#define BASE_BMPHELPER_H

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#else
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif

class BmpHelper {
private:
    unsigned char *mPtData;
    int mWidth;
    int mHeight;
    GLint mFormat;
    GLint mType;
public:
    BmpHelper();

    ~BmpHelper();

    void setData(void *data);

    void setSize(int w, int h);

    int getWidth();

    int getHeight();

    void *getData();

    void setBmpInfo(GLint format, GLint type);

    GLint getFormat();

    GLint getType();
};


#endif //BASE_BMPHELPER_H
