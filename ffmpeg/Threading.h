#ifndef _THREADING_H_
#define _THREADING_H_

#include <pthread.h>

class Thread
{
public:
    Thread();
    virtual ~Thread();
    virtual void doThread() = 0;
    
    void start();
    void terminate();
    void wait(int timeout);
    
private:

    static void* threadProc(void* tid);
    pthread_t __threadId;
    
    Thread(const Thread&);
    Thread& operator = (const Thread&);
    
};

class Mutex
{
	
	friend class Condition;
	
public:
    Mutex();
    ~Mutex();
    
    void lock();
    void unlock();
    bool isLocked();
    
private:
    pthread_mutex_t __mutex;
    bool __isLocked;

    Mutex(const Mutex&);
    Mutex& operator = (Mutex&);
    
};

class Condition
{
public:
    Condition();
    ~Condition();
    
    void wait(int timeout);
    void wait();
    void wake();
    
private:
    pthread_cond_t   __cond;
    pthread_mutex_t __mutex;
};

#endif //_THREADING_H_
