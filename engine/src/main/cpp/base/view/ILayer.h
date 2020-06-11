//
// Created by Jack on 2015/11/11 0011.
//

#ifndef BASE_OLD_ISCENE_H
#define BASE_OLD_ISCENE_H


#include "../picLoader/PicLoader.h"
#include "../picLoader/Pic.h"
#include "Item.h"

class ILayer {
private:
    static int mSequence;
    int mLayerId;
protected:
    int mViewId;

    deque<PicLoader*> mLstPicLoader;
    int mWidth;
    int mHeight;
    deque<Item *> mLstItem;
    deque<void *> mLstData;

    // 判断gl线程中是否需要绑定新数据
    deque<void *> mLstAdd;
//    deque<void *> mLstRemove;
//    deque<void *> mLstModify;
    bool mIsDataChange;
public:
    bool mNeedInitProgram;
    bool mIsUseSensor;
    bool mIsTouchalbe;
    bool mIsFling;

    ILayer(int viewId, int threadNum);

    virtual ~ILayer();

    virtual bool onDraw(long drawTime) = 0;

    virtual void onSizeChange(int w, int h);

    virtual void initProgram() = 0;

    int getId();

    PicLoader* getPtPicLoader(int loaderId);

    void releaseThread(int loaderId, int threadIndex);

    virtual bool onItemGetBmp(string itemId, BmpHelper *ptBmpHelper);

    PicLoader::Task *getTask(int loaderId);

    virtual void onResume();

    virtual void onPause(bool inGLThread);

    virtual void updateItem() = 0;

    void clearItem();

    void clearData();

    void addData(void *data);

    virtual void checkDataChange();

    virtual bool judgeTouchEvent();
};


#endif //BASE_OLD_ISCENE_H
