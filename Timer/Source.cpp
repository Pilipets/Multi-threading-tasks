#include<iostream>

#include"Timer.h"
using namespace time_measuring;

// The main test only function. Must be removed before using
int main() {
	// Instantiate CppTimer
	BaseTimer ctimer;
	// Set the timerout
	ctimer.SetTimeout(std::chrono::milliseconds(2000), [](BaseTimer::TimeOutReason) {
		std::cout << "Interesting job" << std::endl;
	});
	// Wait for sometime
	std::this_thread::sleep_for(std::chrono::seconds(5));
	// Stop the timer
	ctimer.StopTimer();
	system("pause");
	return 0;
}