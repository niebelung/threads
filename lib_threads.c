#include "lib_threads.h"


static lib_threads_thread_queue_t threadQueue = 
{
    -1,
     0   
 };

static int libThreads_ListPush(lib_threads_thread_t * a_thread)
{
    if(threadQueue.cap < MAX_THREADS)
    {
        threadQueue.list[++threadQueue.cnt] = *a_thread;
        ++threadQueue.cap;
        return threadQueue.cnt;
    }
    else
    {
        printf("libThreads_ListPushBack: Max threads number reached!");
        return -1;
    }
}

static int libThreads_ListPop(void)
{
    if(threadQueue.cnt < 0)
    {
        printf("libThreads_ListPop: No list items to clear!");
        return -1;
    };
    --threadQueue.cnt;
    --threadQueue.cap;
    return threadQueue.cap;
}

static int libThreads_GetListCapacity(void)
{
    int retVal = threadQueue.cap;
    
    return retVal;
}

int libThreads_ThreadInit( lib_threads_thread_t * a_thread )
{

    pthread_attr_t p_attr;
    int sz;
    
    if(pthread_attr_init( &p_attr))
    {
        printf("libThreads_ThreadInit: Failed to init thread attributes!" );
        return -1; 
    }
    if(pthread_attr_setdetachstate( &p_attr, PTHREAD_CREATE_JOINABLE))    
    {
        printf("libThreads_ThreadInit: Failed to set thread detach state!" );
        return -1; 
    }
    if(pthread_attr_setinheritsched( &p_attr, PTHREAD_INHERIT_SCHED))
    {
        printf("libThreads_ThreadInit: Failed to set thread inherit sched!" );
        return -1; 
    }
    
    snprintf(a_thread->name, 
             THREAD_NAME_LEN, 
             "Thread#%d", 
             libThreads_GetListCapacity()
             );
    
    a_thread->attr = p_attr;
}

int libThreads_ThreadStart(lib_threads_thread_t * a_thread)
{
    int idx;
    printf("Starting %s\n", a_thread->name);
    idx = libThreads_ListPush(a_thread);
    if(idx > -1)
    {
        lib_threads_thread_t * thr = &(threadQueue.list[idx]);
    
        if(pthread_create( &thr->id,
                           NULL,//&a_thread->attr,
                           thr->func,
                           (void *)thr ))
        {
            printf( "libThreads_ThreadStart: Failed to create thread!" );
            return -1; 
        }
        printf("Successfully started %s id %u\n", thr->name, thr->id);
    }
    else
    {
        printf( "libThreads_ThreadStart: Failed to create thread!" );
        return -1;
    }
}

int libThreads_ThreadsStop(void)
{
    int numThreads = libThreads_GetListCapacity();
    int i;
    printf("Joining threads\nThreads to join %d\n",numThreads);
    
    for(i=0;i<numThreads;++i)
    {
        int idx = libThreads_ListPop();
        
        lib_threads_thread_t thr = threadQueue.list[idx];
        printf("Joining thread %s id %u idx %d\n", thr.name, thr.id, idx);
        
        if(pthread_join(thr.id, NULL))
        {
            printf("libThreads_ThreadStop: Failed to join %s!", thr.name);
            return -1; 
        }
        printf("Successfully joined thread %s idx %d\n", thr.name,idx);
    }
    printf("All threads successfully stopped!");
    return 0;
}
