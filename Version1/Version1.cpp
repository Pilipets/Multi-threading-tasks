#include "Manager.h"

int main()
{
	Manager m;
	m.AddResultFunction([](int a, int b) {
		return a - b; 
	}, "- operation");
	m.AddComputeFunction([](int x) {
		std::this_thread::sleep_for(3s);
		return 2*x+5;
	});
	m.AddComputeFunction([](int x) {
		std::this_thread::sleep_for(8s);
		return x*3-5;
	});
	m.Run();

	system("pause");
	return 0;
}