#include "lib_workers.h"

void *printThreadName(void * ptr);


int main()
{
    int i;

    for(i = 0; i < LIB_WORKERS_MAX_WORKERS; ++i)
    {
        

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

