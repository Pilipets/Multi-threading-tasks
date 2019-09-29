#include <iostream>
#include "Manager.h"
using namespace spos::lab1;

int main(int argc, char **argv) {
	std::cout << argc << std::endl;
	Manager m;
	m.Run(argc, argv);

	system("pause");
	return 0;
}