#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;
pthread_cond_t condition;
pthread_mutex_t mutex;
int ii = 0;
void *producer(void *arg)
{
	for(;;)
	{
		pthread_mutex_lock(&mutex);
		cout << "producer locked" << endl;
		sleep(1);
		if(ii < 5 ){
			cout << "producer waiting" << endl;
			pthread_cond_wait(&condition,&mutex);
		}
		else 
		{
			cout << ii;
			ii++;
		}
		pthread_mutex_unlock(&mutex);
		if(ii >= 10){
			return 0;
		}
	}
}

void * consumer(void *arg){
	
	for(;;)
	{
		pthread_mutex_lock(&mutex);	
		cout << "consumer locked" << endl;
		if(ii >= 5)
		{
			cout << "consumer signal" << endl;
			pthread_cond_signal(&condition);
		}
		else{
			cout << ii;
			ii++;
		}
		
		pthread_mutex_unlock(&mutex);
		sleep(1);
		if(ii >= 10){
			return 0;
		}
	}
}
int main(int argc, char *argv[])
{
	pthread_t proThrHanle, conThrHandle;

	pthread_create(&proThrHanle,NULL,producer,NULL);
	pthread_create(&conThrHandle,NULL, consumer,NULL);

	pthread_join(proThrHanle,NULL);

	pthread_join(conThrHandle,NULL);
}
