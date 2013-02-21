#ifndef _LIB_LHREADS_H_
#define _LIB_TH READS_H_

// INCLUDES

#include <pthread.h>
#include <stdio.h>

// DEFINES

#define LIB_THREADS_MAX_THREADS 5
#define LIB_THREADS_NAME_LEN 16

typedef
void *(* lib_threads_func_t)(void *);

typedef
struct sLibThreadsThread
{
    pthread_t id;
    char name[LIB_THREADS_NAME_LEN];
    pthread_attr_t attr;
    lib_threads_func_t func;
    void * data;
}lib_threads_thread_t;

// PROTOTYPES

extern int libThreads_ThreadInit(lib_threads_thread_t * a_thread);

extern int libThreads_ThreadStart(lib_threads_thread_t * a_thread);

extern int libThreads_ThreadStop(lib_threads_thread_t * a_thread);

#endif