#include <iostream>

#include "demofuncs.h"
#include "Manager.h"
using namespace spos::lab1;
using namespace spos::lab1::demo;

int RunLab1(int argc, char** argv);
void ExecuteFunc(int index, int &res);

int main(int argc, char **argv) {
	RunLab1(argc, argv);
}

int RunLab1(int argc, char** argv)
{
	if (argc == 1)
	{
		Manager m;
		m.SetUp(2);
		m.Run(argc, argv);
		return 0;
	}
	else if (argc == 2 && std::string(argv[1]) == "OPTIONAL") {
		int index;
		cin >> index;
		int res;
		ExecuteFunc(index, res);
		cout << res << endl;
		return 0;
	}
	return -1;
}

void ExecuteFunc(int index, int& res)
{
	namespace testing = spos::lab1::demo;
	if (index & 1)
		res = testing::f_func<testing::INT>(2);
	else
		res = testing::g_func<testing::INT>(2);
}
