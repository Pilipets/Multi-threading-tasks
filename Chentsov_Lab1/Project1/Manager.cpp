#include "Manager.h"
#include <boost/process.hpp>
#include <iostream>
namespace bp = boost::process;
namespace spos::lab1 {
	void Manager::Run(int argc, char ** argv)
	{
		if (argc == 1) {
			std::cout << "Main process " << std::endl;
			bp::opstream in;
			bp::child c("Project1.exe", "OPTIONAL", bp::std_in < in);
			in << 5 << std::endl;

			c.wait();
		}
		else //
		{
			int x = -1;
			std::cin >> x;
			std::cout << x << "Separate process" << std::endl;
		}
	}
}
