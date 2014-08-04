#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define NTHREADS 4
#define N 1000
#define MEGEXTRA 1000000
 
using namespace std;
pthread_attr_t attr;
 
void *dowork(void *threadid)
{
   for(;;){
      cout << "thread running";
   }
}
 
int main(int argc, char *argv[])
{
   pthread_t thread1;
   pthread_attr_t thr_attr;
   pthread_attr_init(&thr_attr);

   pthread_create(&thread1,&thr_attr,dowork,(void *)NULL);
   pthread_join(thread1,NULL);
   pthread_exit(NULL);
}
