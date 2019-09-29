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
		in_pipes.resize(tasks_amount);
		out_pipes.resize(tasks_amount);
		child_processes.resize(tasks_amount);
		res_vec.resize(tasks_amount);
	}
	void Manager::Run(int argc, char** argv)
	{
		DivideTasks(argv[0]);

		for (int i = 0; i < tasks_amount; ++i)
			child_processes[i].wait();
		for (int i = 0; i < tasks_amount; ++i)
		{
			out_pipes[i] >> res_vec[i];
			cout << "i= " << i << ", res= " << res_vec[i] << endl;
		}
		system("pause");
	}
}
