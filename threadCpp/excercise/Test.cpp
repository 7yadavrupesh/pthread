#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "Thread.h"
#include "Mutex.h"

using namespace std;

class Test : public Thread
{
	char c;
	Mutex &mtx;
protected:
	void run(){
		mtx.lock();
		for(int i=0; i<5; i++){
			cout << c << endl;
			sleep(1);
		}
		mtx.unlock();
	}
public:
	Test(char arg,Mutex &mutex):c(arg),mtx(mutex){}
};

int main(){

	Mutex mutex;
	Test obj1('A',mutex), obj2('B',mutex);

	obj1.start(), obj2.start();
	obj1.join(),  obj2.join();
	return 0;
}
