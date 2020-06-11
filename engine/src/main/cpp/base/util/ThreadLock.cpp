//
// Created by Jack on 15/11/11.
//

#include "ThreadLock.h"
#include "../platform/PlatformHelper.h"

ThreadLock::ThreadLock() {
    pthread_mutex_init(&mPtLock, NULL);
    mIsLock = false;
}

ThreadLock::~ThreadLock() {
    show("ThreadLock::~ThreadLock()");
    pthread_mutex_destroy(&mPtLock);
    mIsLock = false;
}

void ThreadLock::lock() {
    pthread_mutex_lock(&mPtLock);
    if (mIsLock) {
        show("ThreadLock::lock: cant lock");
    }
    mIsLock = true;
}

void ThreadLock::unlock() {
    pthread_mutex_unlock(&mPtLock);
    mIsLock = false;
}