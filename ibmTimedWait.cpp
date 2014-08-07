#define _MULTI_THREADED
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define checkResults(str,rc) \
if(rc)  \
{  \
  printf("problem in %s\n", str);  \
  exit(1);  \
} \

/* For safe condition variable usage, must use a boolean predicate and  */
/* a mutex with the condition.                                          */
int                 workToDo = 0;
pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

#define NTHREADS                3
#define WAIT_TIME_SECONDS       3

void *threadfunc(void *parm)
{
  int               rc;
  struct timespec   ts;
  struct timeval    tp;

  rc = pthread_mutex_lock(&mutex);

  /* Usually worker threads will loop on these operations */
  while (1) {
    rc =  gettimeofday(&tp, NULL);

    /* Convert from timeval to timespec */
    ts.tv_sec  = tp.tv_sec;
    ts.tv_nsec = tp.tv_usec * 1000;
    ts.tv_sec += WAIT_TIME_SECONDS;

    while (!workToDo) {
      printf("Thread blocked\n");
      rc = pthread_cond_timedwait(&cond, &mutex, &ts);
      printf("after waiting applied\n");
      /* If the wait timed out, in this example, the work is complete, and   */
      /* the thread will end.                                                */
      /* In reality, a timeout must be accompanied by some sort of checking  */
      /* to see if the work is REALLY all complete. In the simple example    */
      /* we will just go belly up when we time out.                          */
      if (rc == ETIMEDOUT) {
        printf("Wait timed out!\n");
        rc = pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
      }
      cout << "thread blocked 2" << endl;
    }

    printf("Thread consumes work here\n");
    workToDo = 0;
  }

  rc = pthread_mutex_unlock(&mutex);  
  return NULL;
}

int main(int argc, char **argv)
{
  int                   rc=0;
  int                   i;
  pthread_t             threadid[NTHREADS];

  printf("Enter Testcase - %s\n", argv[0]);

  printf("Create %d threads\n", NTHREADS);
  for(i=0; i<NTHREADS; ++i) {
    rc = pthread_create(&threadid[i], NULL, threadfunc, NULL);
  }
  sleep(1);
  rc = pthread_mutex_lock(&mutex);

  printf("One work item to give to a thread\n");
  workToDo = 1;
  rc = pthread_cond_signal(&cond);


  rc = pthread_mutex_unlock(&mutex);


  printf("Wait for threads and cleanup\n");
  for (i=0; i<NTHREADS; ++i) {
    rc = pthread_join(threadid[i], NULL);
  }

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
  printf("Main completed\n");
  return 0;
}