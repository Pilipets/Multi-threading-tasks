#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>

#include "MyMutex.h"
#include "MyMutex.h"
using namespace thread_sync;

void test1(int n = 20);
void test2(int n = 5);
void test3(int n);
int main(int argc, char **argv)
{
	test3(30);
	system("pause");
	return 0;
}

void test3(int n) {
	TicketLock lk(40);

	int var = 0;
	std::vector<std::thread> workers(n);
	auto func = [&lk,&var](int i) {
		for (int i = 0; i < 500; ++i) {
			if (lk.try_lock()) {
				var++;
				lk.unlock();
			}
			else {
				lk.lock();
				var++;
				lk.unlock();
			}
		}
		/*lk.lock();
		std::cout << "Lock_Number" << i << std::endl;
		lk.unlock();*/
	};

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
	std::cout << var << std::endl;
}
void test2(int n) {
	TicketLock lk;

	std::vector<std::thread> workers(n);
	auto func = [&lk](int i) {
		if (lk.try_lock()){
			std::cout << "Try_Lock_Number" << i << std::endl;
			lk.unlock();
		}
		else {
			lk.lock();
			std::cout << "Lock_Number" << i << std::endl;
			lk.unlock();
		}
		/*lk.lock();
		std::cout << "Lock_Number" << i << std::endl;
		lk.unlock();*/
	};

	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
}
void test1(int n) {
	TicketLock lk;

	std::vector<std::thread> workers(n);
	auto func = [&lk](int i) {
		lk.lock();
		std::cout << "Number" << i << std::endl;
		lk.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		lk.lock();
		std::cout << "Number" << i << std::endl;
		lk.unlock();
		lk.lock();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
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