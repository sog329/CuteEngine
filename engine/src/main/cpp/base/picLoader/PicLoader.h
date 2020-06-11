//
// Created by Jack on 2015/11/17 0017.
//

#ifndef BASE_PICLOADER_H
#define BASE_PICLOADER_H

#include <string>
#include "../util/ThreadLock.h"
#include <deque>

using std::string;
using std::deque;

class PicLoader {

public:
//    const static int PIC_LOADER_ID = 1;
//    const static int TXT_LOADER_ID = 2;

    struct Task {
        string url;
        string itemId;
        int suggestWidth;
        int suggestHeight;
        bool isResume;
    };

    struct ThreadInfo {
        int viewId;
        int layerId;
        int loaderId;
        int threadId;
    };

    void loadPic(string oldDataId, string newDataId, string url, int w, int h);

    void releaseThread(int threadIndex);

    PicLoader(int viewId, int layerId, int threadNum, deque<PicLoader *> *ptLstPicLoader);

    ~PicLoader();

    PicLoader::Task *getTask();

    /**
     * 讲当前数据设置在任务列表顶端，即优先加载
     */
    void sortTask(string dataId);

private:
    deque<bool> mLstThread;

    int mViewId;
    int mLayerId;

    int mId;

    static void *loadPic(void *obj);

    deque<PicLoader::Task *> mLstTask;
};


#endif //BASE_PICLOADER_H
