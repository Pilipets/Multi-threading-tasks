#include "Manager.h"

#include <iostream>

namespace spos::lab1 {
	void Manager::ExitProcesses(const std::set<int>& s)
	{
		for (int index : s)
			child_processes[index].terminate();
	}
	void Manager::DivideTasks(const string& exec_name)
	{
		for (int i = 0; i < tasks_amount; ++i)
			in_pipes[i] << i << endl;
		for (int i = 0; i < tasks_amount; ++i)
			child_processes[i] = bp::child(exec_name, "OPTIONAL", bp::std_in < in_pipes[i], bp::std_out > out_pipes[i], bp::std_err > stderr);
	}
	void Manager::CheckProcessStatus(std::set<int>& s)
	{
		for (auto it = s.begin(); it != s.end();) {
			int i = *it;
			if (!child_processes[i].running()) {
				out_pipes[i] >> res_vec[i];
				if (res_vec[i] == 10) 
				{
					//stop_job = true;
					ExitProcesses(s);
					s.clear();
					return;
				}
				cout << "i= " << i << ", res= " << res_vec[i] << endl;
				child_processes[i].wait();
				it = s.erase(it);
			}
			else
				it++;
		}
	}
	void Manager::ComputeResult()
	{
	}
	Manager::Manager(): stop_job(false), tasks_amount(0)
	{
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

		set<int> s;
		for (int i = 0; i < tasks_amount; ++i)
			s.insert(i);

		while (!stop_job && !s.empty()) 
		{
			CheckProcessStatus(s);
		}

		if (stop_job)
		{
			cout << "Result computation has been stopped" << endl;
		}
		else{
			ComputeResult();
			cout << "Res= " << res << endl;
		}
		
		system("pause");
	}
}
