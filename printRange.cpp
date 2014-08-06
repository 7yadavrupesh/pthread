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

void *thrCall(void * arg){
	pthread_mutex_lock(&mutex);
	numOfThreads++;
	if(numOfThreads == 0)
		cout << "its zero",exit(0);
	cout << numOfThreads << " Reached!" << endl;
	pthread_mutex_unlock(&mutex);
}

void * master(void *arg){
	int allCount = 1;
	pthread_t **thrHandle = (pthread_t **)malloc(sizeof(pthread_t));
	for(;;)
	{
		cout << "calling" << endl;
		if(pthread_create(&*thrHandle[allCount],NULL,thrCall,NULL) != 0){
			cout << "free thread" << endl;
			printf("%s\n",strerror(errno) );
		}
		if(!pthread_join(*thrHandle[allCount],NULL))
		numOfThreads--;
		thrHandle = (pthread_t **)realloc(thrHandle,(sizeof(pthread_t)*allCount));
		printf("%s\n",strerror(errno) );
		cout << sizeof(pthread_t)*allCount;
		allCount++;
	}
}

int main(){
	pthread_t masterThread;
	pthread_create(&masterThread,NULL,master,NULL);
	pthread_join(masterThread,NULL);
}