#include "lib_threads.h"

void *printThreadName(void * ptr);


int main()
{
    int i;

    for(i = 0; i < MAX_THREADS; ++i)
    {
        lib_threads_thread_t thr;
        thr.func = printThreadName;
        
        libThreads_ThreadInit(&thr);

        libThreads_ThreadStart(&thr);

    } 
    
    //sleep(10);

    //for(i=1;i<100;++i)
    //{
        //printf("Thread#MAIN\n");
        //usleep(THR_SLEEP_USEC);
    //}
    
    libThreads_ThreadsStop();
    //while(1);
    return 0;

}

