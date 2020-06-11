//
// Created by Jack on 2015/11/10 0010.
//
#include "ILayer.h"
#include <deque>
#include <map>
#include "../util/ThreadLock.h"


#ifndef BASE_OLD_SCENEMANAGER_H
#define BASE_OLD_SCENEMANAGER_H

using std::deque;
using std::map;

class View {
private:
    int mId;
    deque<ILayer *> mLstLayer;
    bool mIsResume;
    float mBgColor[3];
    int mWidth;
    int mHeight;
    bool mIsDirtyRender; // 是否是脏渲染，如果是则每帧通过判断进行回调渲染
    map<GLuint, View *> mMapTextureId;

public:
    void setBgColor(float r, float g, float b);

    void addLayer(ILayer *layer);

    void clear();

    void onDraw(long drawTime);

    void onSizeChange(int w, int h);

    void initProgram();

    void onResume();

    void onPause(bool inGLThread);

    bool isResume();

    View(int id);

    ~View();

    void isDirtyRender(bool isDirtyRender);

    int getId();

    ILayer *getLayer(int id);

    bool addTextureId(GLuint textureId);

    void removeTexureId(GLuint textureId);

    void clearCanvas();
};


#endif //BASE_OLD_SCENEMANAGER_H
