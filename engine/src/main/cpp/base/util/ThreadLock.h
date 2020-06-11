//
// Created by Jack on 15/11/11.
//

#ifndef BASE_THREADLOCK_H
#define BASE_THREADLOCK_H


#include <pthread.h>

class ThreadLock {
private:
    pthread_mutex_t mPtLock;
    bool mIsLock;
public:
    ThreadLock();

    ~ThreadLock();

    void lock();

    void unlock();
};


#endif //BASE_THREADLOCK_H
