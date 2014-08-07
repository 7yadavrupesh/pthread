#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

#define NUMBEROFTHREAD 100

pthread_mutex_t mutex;
pthread_cond_t condition;

static int buffer[NUMBEROFTHREAD];
static int top = 0;
int ii  =0;
void *producer(void * thrNum){
	pthread_mutex_lock(&mutex);
		if(top == NUMBEROFTHREAD)
			pthread_cond_wait(&condition,&mutex);
		else
			buffer[top] = *(int*)thrNum;
	pthread_mutex_unlock(&mutex);
}

void *consumer(void *){
	pthread_mutex_lock(&mutex);

}

int main(){

	int *i = (int *)malloc(sizeof(int));
	*i = 0;
	pthread_t proHandle[NUMBEROFTHREAD];
	pthread_t conHandle[NUMBEROFTHREAD];

	for(*i; *i<NUMBEROFTHREAD; *i++){
		pthread_create(&proHandle[*i], NULL, producer, (void *)i);
		pthread_create(&conHandle[*i], NULL, consumer, static_cast<void*>(i));
	}
}