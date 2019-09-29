#include <iostream>
#include "Manager.h"
using namespace spos::lab1;

int main(int argc, char **argv) {
	if (argc == 1)
	{
		Manager m;
		m.SetUp(2); //do to tasks in pararrel
		m.Run();
	}
	else if (argc == 2 && std::string(argv[1]) == "OPTIONAL") {

	}

	return 0;
}