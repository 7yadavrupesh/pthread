#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

using namespace std;
pthread_cond_t condition;
pthread_mutex_t mutex;
int ii = 0, rc;
int timedWaitApplied =0;
#define WAIT_TIME_SECONDS       5

void *producer(void *arg)
{
	
	for(;;)
	{
		pthread_mutex_lock(&mutex);
		cout << "producer locked" << endl;
		if(ii < 5 ){
			cout << "producer waiting" << endl;
			struct timespec ts;
			struct timeval tp;
			gettimeofday(&tp,NULL);
			cout << tp.tv_sec << endl;
			ts.tv_sec  = tp.tv_sec;
			ts.tv_nsec = tp.tv_usec * 1000;
			ts.tv_sec += WAIT_TIME_SECONDS;
			rc = pthread_cond_timedwait(&condition,&mutex,&ts);
			if (rc == ETIMEDOUT) {
				printf("Wait timed out!\n");
				pthread_mutex_unlock(&mutex);
				pthread_exit(NULL);
			}
			cout << "after waiting" << endl;
		}
		else 
		{
			cout << "P " << ii << endl;
			ii++;
		}
		cout << "producer mutex Unlocking" << endl;
		//sleep(1);
		if(ii >= 10){
			return 0;
		}
	}
	pthread_mutex_unlock(&mutex);
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
			cout <<  "C " <<  ii << endl;
			ii++;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
		cout << "consumer unlocked" << endl;
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
