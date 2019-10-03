#include "Manager.h"

#include <chrono>
#include <iostream>
#include <numeric>

#include "Timer.h"

namespace spos::lab1::version2 {
	inline void Manager::StopRunningProcesses()
	{
		std::set<int>& s = running_processes;
		for (int index : s)
			child_processes[index].terminate();
	}
	inline void Manager::DivideTasks(const string& exec_name)
	{
		for (int i = 0; i < tasks_amount; ++i)
			in_pipes[i] << i << endl;
		for (int i = 0; i < tasks_amount; ++i)
			child_processes[i] = bp::child(exec_name, "OPTIONAL", bp::std_in < in_pipes[i], bp::std_out > out_pipes[i], bp::std_err > stderr);
	}
	void Manager::UpdateRunningProcesses()
	{
		std::set<int>& s = running_processes;
		for (auto it = s.begin(); it != s.end() && !stop_job;) {
			int i = *it;
			if (!child_processes[i].running()) {
				int tmp_res;
				out_pipes[i] >> tmp_res;

				if (!ProcessComputationalResult(tmp_res))
					return;

				res_vec[i] = tmp_res;
				it = s.erase(it);
				child_processes[i].wait();
			}
			else
				it++;
		}
	}
	void Manager::ProcessPromptMessage()
	{
		if (!show_prompt)
			return;

		cout << prompt_message << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 2:
			show_prompt = false;
			break;
		case 3:
			stop_job = true;
			break;
		case 1:
			timer->Start([this]() {
				ProcessPromptMessage();
			}, std::chrono::milliseconds(1000), true);
			break;
		default:
			cout << "Unknown message type" << endl;
		}
		system("cls");
	}
	int Manager::ProcessComputationalResult(int tmp_res)
	{
		//cout << "tmp_res= " << tmp_res << endl;
		if (tmp_res == 4)
		{
			res = 0;
			StopRunningProcesses();
			return 0;
		}
		return running_processes.size(); //return number of active child processes for which manager should wait
	}
	void Manager::ComputeResult()
	{
		if (res.has_value())
			return;
		res = std::reduce(res_vec.begin(), res_vec.end(), 0, std::move(res_func));
	}
	Manager::Manager() :
		stop_job(false), show_prompt(true), tasks_amount(0), res(std::nullopt)
	{
		prompt_message = "----Choose your option----\n"
						 "1.Continue................\n"
						 "2.Continue without prompt.\n"
						 "3.Cancel..................\n";
						  "Choose your action: ";
		timer = new SimpleTimer();
	}

	Manager::~Manager()
	{
		in_pipes.clear();
		out_pipes.clear();
		child_processes.clear();
		res_vec.clear();
		running_processes.clear();
	}

	void Manager::SetUp(int tasks_amount, std::function<int(int, int)>&& res_func)
	{
		this->tasks_amount = tasks_amount;
		in_pipes.resize(tasks_amount);
		out_pipes.resize(tasks_amount);
		child_processes.resize(tasks_amount);
		res_vec.resize(tasks_amount, -1);
		this->res_func = std::move(res_func);
	}
	void Manager::RunVersion2(int argc, char** argv)
	{
		DivideTasks(argv[0]);

		for (int i = 0; i < tasks_amount; ++i)
			running_processes.insert(i);
		timer->Start([this]() {
			ProcessPromptMessage();
		}, std::chrono::milliseconds(1000), true);
		while (!stop_job && !running_processes.empty())
		{
			UpdateRunningProcesses();
			this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (stop_job && !running_processes.empty())
		{
			StopRunningProcesses();
			cout << "Result computation has been stopped" << endl;
		}
		else {
			ComputeResult();
			cout << "Res= " << res.value() << endl;
		}

		system("pause");
	}
}
