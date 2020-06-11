//
// Created by Jack on 2015/11/18 0018.
//

#ifndef BASE_ENGINE_H
#define BASE_ENGINE_H


#include "../picLoader/PicLoader.h"
#include "View.h"

class ViewManager {
private:
    static deque<int> mLstDrawTime;
    static long mLastDrawTime;
    static bool mShowFps;
    static ThreadLock mLock;

public:
    static PicLoader::Task *getTask(PicLoader::ThreadInfo *ptThreadInfo);

    static void releaseThread(int viewId, int layerId, int loaderId, int threadIndex);

    static void onCreate(int viewId);

    static void onResume(int viewId);

    static void onPause(int viewId, bool inGLThread);

    static void onDestroy(int viewId);

    static void onSurfaceCreated(int id);

    static void onSurfaceChanged(int id, int w, int h);

    static void onDrawFrame(int id);

    static void onItemGetBmp(int viewId, int layerId, string itemId, BmpHelper *ptBmpHelper);

    static void lock(bool lock);

    static View *getView(int viewId);

};


#endif //BASE_ENGINE_H
