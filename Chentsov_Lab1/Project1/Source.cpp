#include <iostream>

#include "demofuncs.h"
#include "Manager.h"
using namespace spos::lab1;
using namespace spos::lab1::demo;

int main(int argc, char **argv) {
	if (argc == 1)
	{
		Manager m;
		m.SetUp(4);
		m.Run(argc, argv);
	}
	else if (argc == 2 && std::string(argv[1]) == "OPTIONAL") {
		int var;
		cin >> var;
		this_thread::sleep_for(std::chrono::seconds(var));
		cout << 2 * var << endl;
	}

	return 0;
}