#ifndef _LIB_LHREADS_H_
#define _LIB_TH READS_H_

// INCLUDES

#include <pthread.h>
#include <stdio.h>

// DEFINES

#define MAX_THREADS 5
#define THREAD_NAME_LEN 16

typedef
void *(* lib_threads_func_t)(void *);

typedef
struct sLibThreadsThread
{
    pthread_t id;
    char name[THREAD_NAME_LEN];
    pthread_attr_t attr;
    lib_threads_func_t func;
}lib_threads_thread_t;

typedef
struct sThreadQueue
{
    int cnt; 
    int cap; 
    struct sLibThreadsThread list[MAX_THREADS];
} lib_threads_thread_queue_t;

// PROTOTYPES

extern int libThreads_ThreadInit(lib_threads_thread_t * a_thread);

extern int libThreads_ThreadStart(lib_threads_thread_t * a_thread);

extern int libThreads_ThreadsStop(void);



#endif