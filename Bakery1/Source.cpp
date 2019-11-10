#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>

#include "MyMutex.h"
#include "MyImprovedMutex.h"
using namespace thread_sync;

int main(int argc, char **argv)
{
	BlackWhiteBakeryLock lk(80);

	std::vector<std::thread> workers(20);
	auto func = [&lk](int i) {
		lk.lock();
		std::cout << "Number" << i << std::endl;
		lk.unlock();
		lk.lock();
		std::cout << "Number" << i << std::endl;
		lk.unlock();
		lk.lock();
		std::cout << "Number" << i << std::endl;
		lk.unlock();
	};

	for (int i = 0; i < workers.size(); ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < workers.size(); ++i) {
		workers[i].join();
	}
	system("pause");
	return 0;
}