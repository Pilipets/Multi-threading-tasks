#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>

#include "MyMutex.h"
using namespace thread_sync;

void test1(int n = 20);
void test2(int n = 5);
int main(int argc, char **argv)
{
	test2(30);
	system("pause");
	return 0;
}

void test2(int n) {
	ImprovedBakeryLock lk;

	std::vector<std::thread> workers(n);
	auto func = [&lk](int i) {
		lk.lock(i);

		std::cout << "Number" << i << std::endl;
		lk.unlock(i);
	};

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
}
void test1(int n) {
	BlackWhiteBakeryLock lk;

	std::vector<std::thread> workers(n);
	auto func = [&lk](int i) {
		lk.lock(i);
		std::cout << "Number" << i << std::endl;
		lk.unlock(i);
		//std::this_thread::sleep_for(std::chrono::milliseconds(400));
		lk.lock(i);
		std::cout << "Number" << i << std::endl;
		lk.unlock(i);
		lk.lock(i);
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Number" << i << std::endl;
		lk.unlock(i);
	};

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
}