#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>

#include "MyMutex.h"
using namespace thread_sync;
using namespace std;


void test1(int n = 20);
void test2(int n = 5);
void test3(int n);
int main(int argc, char **argv)
{
	test3(5);
	system("pause");
	return 0;
}

void test3(int n) {
	int counter = 0;
	BlackWhiteBakeryLock lk;

	std::vector<std::thread> workers(n);
	auto func = [&lk, &counter](int i) {
		for (int j = 0; j < 100000; ++j)
		{
			lk.lock(i);
			counter++;
			lk.unlock(i);
		}
	};

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}

	cout << "counter= " << counter << endl;
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
	ImprovedBakeryLock lk;

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