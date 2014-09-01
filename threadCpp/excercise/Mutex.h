#ifndef __mutex_h__
#define __mutex_h__

#include <iostream>
#include <pthread.h>

using namespace std;

class Mutex{
private:
	pthread_mutex_t mutex;
public:
	Mutex(){
		pthread_mutex_init(&mutex,NULL);
		cout << "mutex init" << endl;
	}
	virtual ~Mutex(){
		pthread_mutex_destroy(&mutex);
		cout << "mutex destroyed" << endl;
	}
	void lock(){
		pthread_mutex_lock(&mutex);
		cout << "lock Aquired" << endl;
	}
	void unlock(){
		pthread_mutex_unlock(&mutex);
		cout << "lock released" << endl;
	}
	bool trylock(){
		return (pthread_mutex_trylock(&mutex) ==0);
	}

};

#endif
