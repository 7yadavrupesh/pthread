#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
 
void foo(void);  /* Functions that use the threadSpecific data */
void bar(void);
void dataDestructor(void *data);
 
#define checkResults(string, val) {             \
 if (val) {                                     \
   printf("Failed with %d at %s", val, string); \
   exit(1);                                     \
 }                                              \
}
 
typedef struct {
  int          threadSpecific1;
  int          threadSpecific2;
} threadSpecific_data_t;
 
#define                 NUMTHREADS   5
pthread_key_t           threadSpecificKey;
pthread_mutex_t			mutex;
static int count = 0;
threadSpecific_data_t * getMemory(){
	pthread_mutex_lock(&mutex);
	//threadSpecific_data_t * memory = (threadSpecific_data_t *)malloc(sizeof(8));
  threadSpecific_data_t * memory = (threadSpecific_data_t *)malloc(sizeof(threadSpecific_data_t));
	memory->threadSpecific2 = memory->threadSpecific1 = count++;
	pthread_mutex_unlock(&mutex);
	return memory;
}

void *theThread(void *parm)
{
   int  rc;
   threadSpecific_data_t    *gData;
   gData = getMemory();
   printf("Thread %.8ld: Entered\n", pthread_self());
   rc = pthread_setspecific(threadSpecificKey, gData);
   checkResults("pthread_setspecific()\n", rc);
   foo();
   return NULL;
}
 
void foo() {
   threadSpecific_data_t *gData = (threadSpecific_data_t *)pthread_getspecific(threadSpecificKey);
   printf("Thread %.8ld: foo(), threadSpecific data=%d %d\n", pthread_self(), gData->threadSpecific1, gData->threadSpecific2);
   bar();
}
 
void bar() {
   threadSpecific_data_t *gData = (threadSpecific_data_t*)pthread_getspecific(threadSpecificKey);
   printf("Thread %.8ld: bar(), threadSpecific data=%d %d\n",
          pthread_self(), gData->threadSpecific1, gData->threadSpecific2);
   return;
}
 
void dataDestructor(void *data) {

   printf("Thread %.8ld: Free data\n", pthread_self());
   threadSpecific_data_t* gData = (threadSpecific_data_t*)data;
   printf("Thread %.8ld: bar(), threadSpecific data=%d %d **********************************\n", pthread_self(), gData->threadSpecific1, gData->threadSpecific2);
   pthread_setspecific(threadSpecificKey, NULL);
   free(data);
   malloc(1);
}
  
int main(int argc, char **argv)
{
  pthread_t             thread[NUMTHREADS];
  int                   rc=0;
  int                   i;
  threadSpecific_data_t        *gData;
 
  printf("Enter Testcase - %s\n", argv[0]);
  rc = pthread_key_create(&threadSpecificKey, dataDestructor);
  checkResults("pthread_key_create()\n", rc);
 
  printf("Create/start threads\n");
  for (i=0; i <NUMTHREADS; ++i) {
       /* Create per-thread threadSpecific data and pass it to the thread */
     rc = pthread_create(&thread[i], NULL, theThread, NULL);
     checkResults("pthread_create()\n", rc);
  }
 
  printf("Wait for the threads to complete, and release their resources\n");
  for (i=0; i <NUMTHREADS; ++i) {
  rc = pthread_join(thread[i], NULL);
     checkResults("pthread_join()\n", rc);
  }
 
  pthread_key_delete(threadSpecificKey);
  printf("Main completed\n");
  return 0;
}