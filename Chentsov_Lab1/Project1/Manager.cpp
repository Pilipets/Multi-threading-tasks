#include "Manager.h"

#include <iostream>
#include <string>

namespace spos::lab1 {
	void Manager::DivideTasks(const string& exec_name)
	{
		for (int i = 0; i < tasks_amount; ++i)
			in_pipes[i] << i << endl;
		for (int i = 0; i < tasks_amount; ++i)
			child_processes[i] = bp::child(exec_name, "OPTIONAL", bp::std_in < in_pipes[i], bp::std_out > out_pipes[i], bp::std_err > stderr);
	}
	void Manager::SetUp(int tasks_amount)
	{
		this->tasks_amount = tasks_amount;
		in_pipes.reserve(tasks_amount);
		out_pipes.reserve(tasks_amount);
		child_processes.reserve(tasks_amount);
		res_vec.reserve(tasks_amount);
	}
	void Manager::Run(int argc, char** argv)
	{
		DivideTasks(argv[1]);

		for (int i = 0; i < tasks_amount; ++i)
			child_processes[i].wait();
		for(int i = 0; i < tak)
		if (argc == 1) {
			std::cout << "Main process " << std::endl;

			vector<bp::ipstream> out_pipes(2);
			vector<bp::opstream> in_pipes(2);

			bp::child c(argv[0], "OPTIONAL", bp::std_out > out_pipes[0], bp::std_in < in_pipes[0]),
				c1(argv[0], "OPTIONAL", bp::std_out > out_pipes[1], bp::std_in < in_pipes[1]);

			in_pipes[0] << 1 << endl;
			in_pipes[1] << 2 << endl;

			c.wait(), c1.wait();
			/*vector<int> res(2, -1);
			s_out >> res[1];
			s_out >> res[0];
			cout << "Res1= " << res[0] << endl;
			cout << "Res2= " << res[1] << endl;*/
			vector<int> res(2);
			out_pipes[0] >> res[0];
			out_pipes[1] >> res[1];

			cout << "Res1= " << res[0] << endl;
			cout << "Res2= " << res[1] << endl;
			system("pause");
		}
		else
		{
			int tmp;
			cin >> tmp;
			std::cout << 2 * tmp << endl;
		}
	}
}
