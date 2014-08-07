#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>


using namespace std;
static int numOfThreads = 0;
pthread_mutex_t mutex;
#define NUMBEROFTHREADS 5

int critical;
void * master(void *arg){
		
		int val = *(int*)arg;
		int result = pthread_mutex_lock(&mutex);
		if(result == 0 )
		{
			cout << "entered";
			fflush(stdout);
			sleep(2);
			critical = val;
			pthread_mutex_unlock(&mutex);
			cout << "out";
		}else
		cout << "ebusy";
}

int main(){
	pthread_t masterThread[NUMBEROFTHREADS];
	int *i = (int*)malloc(sizeof(int));
	
	for(*i =0; *i<NUMBEROFTHREADS; *i++)
		pthread_create(&masterThread[*i],NULL,master,(void *)i);

	for(*i =0; *i<NUMBEROFTHREADS; *i++)
		pthread_join(masterThread[*i],NULL);
}