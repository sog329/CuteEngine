//
// Created by Jack on 15/11/26.
//

#ifndef __ANDROID__


#ifndef ANDROIDDEMO_OCHELPER_H
#define ANDROIDDEMO_OCHELPER_H

#include "IosInterface.h"
#include "../util/ThreadLock.h"

class OcHelper {
private:
    static IosInterface *mPtCallback;
    static ThreadLock mLock;
    static int mUsingCount;
public:
    static void setIosCallback(IosInterface* ptCallback);

    static void requestBmp(int viewId, int layerId, const char *itemId, const char *url, int w, int h);
    
    static void onLoadNextPageData(int viewId, int layerId);

    static void onClick(int viewId, int dataIndex, const char *dataId);

};

#endif //ANDROIDDEMO_OCHELPER_H

#endif