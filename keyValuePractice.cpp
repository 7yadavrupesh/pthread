#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMBEROFTHREADS 5
using namespace std;

pthread_mutex_t mutex;
pthread_key_t	thrKey;
pthread_barrier_t barrier;
static int count =0;

typedef struct{
	int _x;
	int _y;
} globalData;

void DistructorFunc(void *data){
	cout << "in des "<< endl;
	free(data);
}
globalData * getMemory(){
	pthread_mutex_lock(&mutex);
	globalData *gdata = (globalData *)malloc(sizeof(globalData));
	gdata->_x = gdata->_y = count++;
	pthread_mutex_unlock(&mutex);
	return gdata;
}

void foo2(){
	globalData *gdata = (globalData *)pthread_getspecific(thrKey);
	cout << "foo2" << gdata->_x << " " << gdata->_y << endl;	
}

void foo1(){
	globalData *gdata = (globalData *)pthread_getspecific(thrKey);
	cout << "foo1" << gdata->_x << " " << gdata->_y << endl;
	foo2();
}

void *threadFunction(void * arg){
	globalData * gdata = getMemory();
	pthread_setspecific(thrKey,gdata);
	cout << "threadArea";
	pthread_barrier_wait(&barrier);
	foo1();
	return NULL;
}

int main(){
	
	pthread_t thrHandle[NUMBEROFTHREADS];
	int i=0;
	pthread_barrier_init(&barrier,NULL,5);
	pthread_key_create(&thrKey,DistructorFunc);
	for(i=0;i<NUMBEROFTHREADS;i++){
		pthread_create(&thrHandle[i], NULL, threadFunction, NULL);
	}

	for(i=0;i<NUMBEROFTHREADS;i++){
		pthread_join(thrHandle[i],NULL);
	}	
}