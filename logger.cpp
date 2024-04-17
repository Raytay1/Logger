#include <assert.h>
#include <thread>
#include "LoggerPriority.h"

using namespace std;

void log_test(int n)
{
    Logger::Info("%d", n);
}

int main()
{
	const char* name = "User";
	Logger::Debug("Hello %s", name);

	Logger::Info("OH NO!", name);

	Logger::Error("Hello %d %d", 15, 28);

    thread threads[10];
    
	for (int i=0; i<10; i++)
		threads[i] = thread(log_test, i);

	for (int i=0; i<10; i++)
		threads[i].join();
	
	return 0;
}