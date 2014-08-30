#include <iostream>
#include <unistd.h>
#include "Thread.h"

class Test : public Thread
{
	private:
		std::string id;
	protected:
		virtual void run();
	public:
		Test(std::string id) : id(id) {}
};

void Test::run()
{
	for (int i = 0; i < 5; ++i)
	{
		std::cout << id << std::endl;
		usleep(100);
	}
}

int main(void)
{
	Test a("A"), b("B");
	a.start();   b.start();
	a.join();    b.join();
	return 0;
}