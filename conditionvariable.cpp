#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
 
int main(int argc, char *argv[])
{
	pthread_t proThrHanle, conThrHandle;

	pthread_create(&proThrHanle,NULL,producer,NULL);
	pthread_create(&conThrHandle,NULL, consumer,NULL);

	pthread_join(conThrHandle,NULL);
	pthread_join(conThrHandle,NULL);
}
