#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

class Thread
{
public:
    Thread();
    virtual ~Thread();
    virtual doThread = 0;
    
    void start();
    void terminate();
    void wait(int timeout);
    
private:

    void* threadProc(void* tid);

    Thread(const Thread&);
    Thread& operator = (const Thread&);
    unsigned long __threadId;
    
};

#endif
