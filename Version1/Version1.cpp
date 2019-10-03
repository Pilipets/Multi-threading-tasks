#include <iostream>

#include "demofuncs.h"
#include "Manager.h"
using namespace spos::lab1;
using namespace spos::lab1::demo;

int RunLab1(int argc, char** argv);
void ExecuteFunc(int index, int &res);

int main(int argc, char **argv) {
	//RunLab1(argc, argv);
	if (argc == 1) {

		bp::pstream pipe;
		bp::child c(argv[0], "tmp", bp::std_in < pipe, bp::std_out > pipe, bp::std_err > stderr);
		pipe << "Message from main process" << endl;
		c.wait();
		string res;
		std::getline(pipe, res);
		cout << res << endl;
		system("pause");
	}
	else {
		string x;
		std::getline(cin, x);
		//cin.ignore('\n');
		cout << "Received " + x << endl;
	}
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
		cerr << "index= " << index << endl;
		int res;
		ExecuteFunc(index, res);
		cerr << "Res= " << res << endl;
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
