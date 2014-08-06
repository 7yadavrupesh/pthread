#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;
double times[5];
char process[] = {'A', 'B', 'C', 'D', 'E'};
int turn = 0;

void StartNext(int tid)     //choose the next thread to run
{
    int i;
    for(i = (tid + 1) % 5; times[i] == 0; i = (i + 1) % 5)
        if(i == tid)    //if every thread has finished
            return;
    turn = i;
}

void *Run(void *tid)    //the thread function
{
    int *ii = (int*)tid;
    int i = *ii;
    while(times[i] != 0)
    {
        while(turn != i);   //busy waiting till it is its turn
        if(times[i] > 2)
        {
            printf("%c 2\n", process[i]);
            sleep(2);   //sleep is to simulate the actual running time
            times[i] -= 2;
        }
        else if(times[i] > 0 && times[i] <= 2)      //this thread will have finished after this turn
        {
            printf("%c %lf\n", process[i], times[i]);
            sleep(times[i]);
            times[i] = 0;
        }
        StartNext(i);   //choose the next thread to run
    }
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t threads[5];
    int i, status;

    if(argc == 6)
    {cout << "thread";
        for(i = 0; i < 5; i++)
            times[i] = atof(argv[i + 1]);   //input the burst time of each thread
        for(i = 0; i < 5; i++)
        {
            cout << "thread";
            status = pthread_create(&threads[i], NULL, Run, (void *)i);    //Create threads
            if(status != 0)
            {
                printf("While creating thread %d, pthread_create returned error code %d\n", i, status);
                exit(-1);
            }
            pthread_join(threads[i], 0);    //Join threads
        }
    }
    return 0;
}