#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>

#include "MyMutex.h"
#include "MyImprovedMutex.h"
using namespace thread_sync;

void test1();

int main(int argc, char **argv)
{
	int n = 5;
	BlackWhiteBakeryLock lk(n);

	std::vector<std::thread> workers(n);
	auto func = [&lk](int i) {
		lk.lock();

		std::cout << "Number" << i << std::endl;
		lk.unlock();
	};

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
	system("pause");
	return 0;
}

void test1() {
	int n = 20;
	BlackWhiteBakeryLock lk(n);

	std::vector<std::thread> workers(n);
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

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
}