#include <pthread.h>

using namespace std;

class Thread{

private:
	pthread_t thread_handle;
	static void* dispatch(void *);

protected:
	virtual void run() = 0;

public:
	void start();
	void join();

};