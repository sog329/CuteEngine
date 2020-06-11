//
// Created by Jack on 2015/11/17 0017.
//

#ifndef BASE_PICITEM_H
#define BASE_PICITEM_H

#include "../util/BmpHelper.h"
#include "PicLoader.h"
#include "../util/AnimHelper.h"
#include <string>
#include "../platform/PlatformHelper.h"

using std::string;
using CuteEngine::AnimHelper;

class Pic {
private:
    string mId;
    string mUrl;
    int mWidth;
    int mHeight;
    PicLoader* mPtPicLoader;
protected:
    GLuint mTextureId;
    BmpHelper *mPtBmpHelper;
    bool mNeedCheckTexture; // 当onPause后设置为true，需要再次渲染时检查纹理。
public:
    bool mIsTextureReady; // 该纹理是否是当前需要显示的纹理(纹理ID复用)，并且纹理是否准备好
    AnimHelper mAnimHelper;

    Pic(PicLoader* ptPicLoader);

    virtual ~Pic();

    string getId();

    /**
     * 设置图片的url地址，当在构造中未setSize时，不执行内部方法。故在渲染控件onSizeChange中会再次调用updateItem，执行一次setUrl
     */
    bool setUrl(string dataId, string url);

    void setSize(int w, int h);

    void clearUrl();

    void resetUrl(string url);

    string getUrl();

    bool setBmp(string id, BmpHelper *ptBmpHelper);

    void onPause(int viewId, bool inGLThread);

    GLuint getTextureId();

    void setTextureId(GLuint textureId);

    bool initTexture(int viewId, PicLoader *ptPicItem);

};


#endif //BASE_PICITEM_H
