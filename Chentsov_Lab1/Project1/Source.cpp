#include <iostream>

#include "demofuncs.h"
#include "Manager.h"
using namespace spos::lab1;
using namespace spos::lab1::demo;

int RunLab1(int argc, char** argv);

int main(int argc, char **argv) {
	RunLab1(argc, argv);
}

int RunLab1(int argc, char** argv)
{
	if (argc == 1)
	{
		Manager m;
		m.SetUp(4);
		m.Run(argc, argv);
		return 0;
	}
	else if (argc == 2 && std::string(argv[1]) == "OPTIONAL") {
		int var;
		cin >> var;
		this_thread::sleep_for(std::chrono::seconds(var));
		cout << 2 * var << endl;
		return 0;
	}
	return -1;
}