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
#define WAIT_TIME_SECONDS       3

int main(int argc, char *argv[])
{
	pthread_t proThrHanle, conThrHandle;

	pthread_create(&proThrHanle,NULL,producer,NULL);
	pthread_create(&conThrHandle,NULL, consumer,NULL);

	pthread_join(proThrHanle,NULL);
	pthread_join(conThrHandle,NULL);
}
