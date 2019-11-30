#include <chrono>
#include <iostream>
#include <mutex>
#include <functional>
#include <vector>

#include "MyMutex.h"
using namespace thread_sync;
using namespace std::chrono_literals;

template <class Fn>
void RunTest(int n, Fn&& func, Lockable* lk);
void test1(int n);
void test2(int n);
void test3(int n);
int main(int argc, char **argv)
{
	test3(30);
	system("pause");
	return 0;
}

void test3(int n) {
	TicketLock lk1(n);
	TicketLock lk2;

	int var = 0;
	auto func = [&var](Lockable*lk, int i) {
		for (int i = 0; i < 500; ++i) {
			if (lk->try_lock()) {
				var++;
				lk->unlock();
			}
			else {
				lk->lock();
				var++;
				lk->unlock();
			}
		}
	};

	RunTest(n, func, &lk1);
	std::cout << var << std::endl;
	var = 0;
	RunTest(n, func, &lk2);
	std::cout << var << std::endl;
}
void test2(int n) {
	TicketLock lk1(n);
	TicketLock lk2;

	auto func = [](Lockable *lk, int i) {
		if (lk->try_lock()){
			std::cout << "Try_Lock_Number" << i << std::endl;
			lk->unlock();
			std::this_thread::sleep_for(i * 3ms);
		}
		else {
			std::this_thread::sleep_for(i*2ms);
			lk->lock();
			std::cout << "Lock_Number" << i << std::endl;
			lk->unlock();
		}
		std::this_thread::sleep_for(i * 1ms);
		lk->lock();
		std::cout << "After" << i << std::endl;
		lk->unlock();
	};
	RunTest(n, func, &lk1);
	RunTest(n, func, &lk2);
}

void test1(int n) {
	TicketLock lk1(n);
	TicketLock lk2;

	std::vector<std::thread> workers(n);
	auto func = [](Lockable* lk, int i) {
		lk->lock();
		std::cout << "Number" << i << std::endl;
		lk->unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		lk->lock();
		std::cout << "Number" << i << std::endl;
		lk->unlock();
		lk->lock();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Number" << i << std::endl;
		lk->unlock();
	};
	RunTest(n, func, &lk1);
	RunTest(n, func, &lk2);
}

template <class Fn>
void RunTest(int n, Fn&& func, Lockable* lk)
{
	std::vector<std::thread> workers(n);
	for (int i = 0; i < n; ++i) {
		workers[i] = std::thread(func, lk, i);
	}

	for (int i = 0; i < n; ++i) {
		workers[i].join();
	}
}