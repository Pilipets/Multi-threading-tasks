#include<iostream>
#include<string>
#include"Timer.h"
using namespace time_measuring;

// The main test only function. Must be removed before using
int main() {
	const std::string prompt_message = "-------User Prompt-------\n"\
		"1. Continue..................\n"\
		"2. Continue without prompt...\n"\
		"3. Cancel....................\n";
	// Instantiate CppTimer
	BaseTimer ctimer;
	// Set the timerout
	ctimer.SetTimeout(std::chrono::milliseconds(2000), [prompt_message]() {
		std::cout << prompt_message << std::endl;
	});
	// Wait for sometime
	std::this_thread::sleep_for(std::chrono::seconds(5));
	// Stop the timer
	ctimer.StopTimer();

	//std::cout << prompt_message << std::endl;
	system("pause");
	return 0;
}