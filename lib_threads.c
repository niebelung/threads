#include "lib_threads.h"

static int thread_cnt = 0;

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
             LIB_THREADS_NAME_LEN, 
             "Thread#%d", 
             ++thread_cnt
             );
    
    a_thread->attr = p_attr;
}

int libThreads_ThreadStart(lib_threads_thread_t * a_thread)
{
    printf("Starting %s\n", a_thread->name);

    if(pthread_create( &a_thread->id,
                        NULL,//&a_thread->attr,
                        a_thread->func,
                        a_thread->data))
    {
        printf( "libThreads_ThreadStart: Failed to create thread!" );
        return -1; 
    }
    printf("Successfully started %s id %u\n", thr->name, thr->id);
}

int libThreads_ThreadStop(lib_threads_thread_t * a_thread)
{
    printf("Joining thread %s id %u\n", a_thread.name, a_thread.id);
    
    if(pthread_join(a_thread.id, NULL))
    {
        printf("libThreads_ThreadStop: Failed to join %s!", a_thread.name);
        return -1; 
    }
    printf("Successfully joined thread %s\n", a_thread.name);
}

