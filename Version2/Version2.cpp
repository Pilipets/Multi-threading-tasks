#include "Manager.h"

using namespace spos::lab1::version2;

int RunManager(int argc, char** argv);

int main(int argc, char **argv) {
	RunManager(argc, argv);
}

int RunManager(int argc, char** argv)
{
	if (argc == 1)
	{
		while (true)
		{
			Manager m;
			m.SetUp(2, std::chrono::milliseconds(1000));
			m.RunVersion2(argc, argv);
			system("cls");
		}
		return 0;
	}
	else if (argc == 2 && std::string(argv[1]) == "OPTIONAL") {
		Manager::RunParrallelFunction();
		return 0;
	}
	return -1;
}