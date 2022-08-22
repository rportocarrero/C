#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <syslog.h>

#define NUM_THREADS 10000

typedef struct{
    int id;
}threadParams_t; 

pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];

void* doWork(void* params){
    threadParams_t* threadp = (threadParams_t*)params;
    int sum;

    for(int i=0;i<threadp->id;i++){
        sum+=i;
    }

    syslog(LOG_DEBUG,"Thread ID: %d SUM: %d",threadp->id,sum);
    return 0;
}

int main(int argc, char* argv[]){
    openlog("RTTest",LOG_PERROR,LOG_USER);

    //create threads
    for(int i=0;i<NUM_THREADS;i++){
        threadParams[i].id=i;
        pthread_create(&threads[i],NULL, doWork,(void*) &threadParams[i]);
    }

    //join threads
    for(int i=0;i<NUM_THREADS;i++){
        pthread_join(threads[i],NULL);
    }

    return 0;
}