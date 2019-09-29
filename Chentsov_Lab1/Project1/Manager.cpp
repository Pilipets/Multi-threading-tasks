#include "Manager.h"
#include <boost/process.hpp>
#include <iostream>
#include <string>
using namespace std;
namespace bp = boost::process;
namespace spos::lab1 {
	void Manager::Run(int argc, char **argv)
	{
		if (argc == 1) {
			std::cout << "Main process " << std::endl;

			bp::ipstream s_out;
			bp::child c("Project1.exe", "OPTIONAL", bp::std_out > s_out);

			string line;
			while (c.running() && std::getline(s_out, line) && !line.empty())
				cout << line << endl;

			c.wait();
		}
		else
		{
			int x = -1;
			//std::cin >> x;
			std::cout << x << "Separate process" << std::endl;
		}
	}
}
