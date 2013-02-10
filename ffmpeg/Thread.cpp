#include "Thread.h"

Thread::Thread()
    : __threadId(0)
{
    
}

Thread::~Thread()
{
    
}

void Thread::start()
{
    pthread_create(&__threadId, 0, threadProc, 0);
}

void Thread::terminate()
{
    
}

void* Thread::threadProc(void* tid)
{
    doThread();
    pthread_exit(0);
    
    return 0;
}

void Thread::wait(int timeout)
{
    
}
