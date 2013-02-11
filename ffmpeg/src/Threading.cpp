#include <sys/time.h>
#include "Threading.h"

Thread::Thread()
    : __threadId(0)
{
    
}

Thread::~Thread()
{
    
}

void Thread::start()
{
    pthread_create(&__threadId, 0, threadProc, (void*)this);
}

void Thread::terminate()
{
    
}

void* Thread::threadProc(void* arg)
{
    Thread* thread = reinterpret_cast<Thread*>(arg);
    thread->doThread();
    pthread_exit(0);
    
    return 0;
}

void Thread::wait(int timeout)
{
    
}

Mutex::Mutex()
	: __isLocked(false)
{
    pthread_mutex_init(&__mutex, 0);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&__mutex);
}

void Mutex::lock()
{
	__isLocked = true;
    pthread_mutex_lock(&__mutex);
}

void Mutex::unlock()
{
	__isLocked = false;
    pthread_mutex_unlock(&__mutex);
}

bool Mutex::isLocked()
{
	return __isLocked;
}



Condition::Condition()
{
    pthread_cond_init(&__cond, 0);
    pthread_mutex_init(&__mutex, 0);
}

Condition::~Condition()
{
    pthread_cond_destroy(&__cond);
    pthread_mutex_destroy(&__mutex);
}

void Condition::wait(int timeout)
{
    pthread_mutex_lock(&__mutex);

    if (timeout <= 0)
    {
        pthread_cond_wait(&__cond, &__mutex);
    }
    else
    {
        struct timeval now;
        struct timespec timeToWait;
        gettimeofday(&now, 0);

        timeToWait.tv_nsec = (now.tv_usec + (timeout % 1000) * 1000) * 1000;
        timeToWait.tv_sec = now.tv_sec + (timeout / 1000) + (timeToWait.tv_nsec / 1000000000);
        timeToWait.tv_nsec %= 1000000000;

        pthread_cond_timedwait(&__cond, &__mutex, &timeToWait);
    }

    pthread_mutex_unlock(&__mutex);
}

void Condition::wait()
{
	pthread_mutex_lock(&__mutex);
	pthread_cond_wait(&__cond, &__mutex);
	pthread_mutex_unlock(&__mutex);
}

void Condition::wake()
{
	pthread_mutex_lock(&__mutex);
	pthread_cond_signal(&__cond);
	pthread_mutex_unlock(&__mutex);
}
