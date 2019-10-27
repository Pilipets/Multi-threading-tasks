#include<iostream>
#include<string>
#include"Timer.h"
using namespace time_measuring;

int main() {
	const std::string prompt_message = "-------User Prompt-------\n"\
		"1. Continue..................\n"\
		"2. Continue without prompt...\n"\
		"3. Cancel....................\n";

	/*BaseTimer ctimer;

	ctimer.SetTimeout(std::chrono::milliseconds(2000), [prompt_message]() {
		std::cout << prompt_message << std::endl;
	});

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	ctimer.StopTimer();*/

	CallBackTimer ctimer;

	ctimer.start(2000, [prompt_message]() {
		std::cout << prompt_message << std::endl;
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	ctimer.stop();
	//std::cout << prompt_message << std::endl;
	system("pause");
	return 0;
}