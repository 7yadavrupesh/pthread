#include "Thread.h"

using namespace std;

void * Thread::dispatch(void * arg){
	static_cast<Thread*> (arg)->run();
}

void Thread::start(){
	pthread_create(&thread_handle,NULL,dispatch,this);
}

void Thread::join(){
	pthread_join(thread_handle,NULL);
}