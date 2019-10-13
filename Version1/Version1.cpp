#include "Manager.h"

using namespace spos::lab1::version1;

int RunManager(int argc, char** argv);

int main(int argc, char **argv) {
	RunManager(argc, argv);
}

int RunManager(int argc, char** argv)
{
	if (argc == 1)
	{
		Manager m;
		m.SetUp(2);
		m.RunVersion1(argc, argv);
		return 0;
	}
	else if (argc == 2 && std::string(argv[1]) == "OPTIONAL") {
		Manager::RunParrallelFunction(2);
		return 0;
	}
	return -1;
}