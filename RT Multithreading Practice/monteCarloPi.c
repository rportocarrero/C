#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <syslog.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS 10
#define DEBUG 1
#define NUM_DARTS 1000

typedef struct{
    int id;
    int rangeLow;
    int rangeHigh;
    int hitsInsideCircle;
    int hitsOutsideCircle;
}threadParams_t; 

pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];
int totalInside, totalOutside=0;
long startTime, stopTime;

void* doWork(void* params){
    threadParams_t* threadp = (threadParams_t*)params;
    int id = threadp->id;
    int rangeLow = threadp->rangeLow;
    int rangeHigh = threadp->rangeHigh;
    if(DEBUG) syslog(LOG_DEBUG,"Thread ID: %d RangeLow: %d RangeHigh: %d",id, rangeLow, rangeHigh);

    // throw darts
    for(int i=rangeLow;i<rangeHigh;i++){
        double x = (double)rand()/(double)RAND_MAX;
        double y = (double)rand()/(double)RAND_MAX;
        double dist = sqrt(pow(x,2)+pow(y,2));

        if(dist < 1){
            threadp->hitsInsideCircle+=1;
        }else {
            threadp->hitsOutsideCircle+=1;
        }
        if(DEBUG) syslog(LOG_DEBUG,"Thread ID: %d, x: %f, y: %f dist: %f",id, x, y, dist);
    }
    if(DEBUG) syslog(LOG_DEBUG,"Thread ID: %d, Inside: %d, Outside: %d",id, threadp->hitsInsideCircle, threadp->hitsOutsideCircle);
    
    return 0;
}

int main(int argc, char* argv[]){
    openlog("MonteCarlo PI",LOG_PERROR,LOG_USER);
    syslog(LOG_INFO,"START");
    syslog(LOG_INFO,"Number of Threads:\t%d",NUM_THREADS);
    syslog(LOG_INFO,"Number of Darts:\t%d",NUM_DARTS);

    int range = NUM_DARTS/NUM_THREADS;

    //create threads
    for(int i=0;i<NUM_THREADS;i++){
        threadParams[i].id=i;
        threadParams[i].rangeLow = i*range;
        threadParams[i].rangeHigh = (i+1)*range;
        pthread_create(&threads[i],NULL, doWork,(void*) &threadParams[i]);
    }

    //join threads
    for(int i=0;i<NUM_THREADS;i++){
        pthread_join(threads[i],NULL);
    }


    for(int i=0;i<NUM_THREADS;i++){
        totalInside+=threadParams[i].hitsInsideCircle;
        totalOutside+=threadParams[i].hitsOutsideCircle;
    }

    if(DEBUG)syslog(LOG_DEBUG,"Total Darts Thrown: %d",totalInside+totalOutside);

    double Pi = (double)totalInside/(double)totalOutside;
    stopTime = clock();
    long totalTime = stopTime/CLOCKS_PER_SEC;
    syslog(LOG_INFO,"Pi is: %f",Pi);
    syslog(LOG_INFO,"STOP");
    return 0;
}