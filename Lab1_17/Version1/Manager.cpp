#include "Manager.h"

#include <chrono>
#include <iostream>
#include <numeric>

#include "demofuncs.h"
#include "EventListener.h"

namespace spos::lab1::version1 {
	inline void Manager::StopRunningProcesses()
	{
		std::set<int>& s = running_processes;
		for (int index : s) // send the signals to terminate
			child_processes[index].terminate();
		for (int index : s) // to avoid a zombie process & get the exit code
			child_processes[index].wait();
		s.clear();
	}
	inline void Manager::PrintRunningProcesses()
	{
		if (running_processes.empty())
			return;
		cout << "functions with indexes ";
		std::vector<int> tmp(running_processes.begin(), running_processes.end());
		for (size_t i = 0; i < tmp.size() - 1; ++i)
			cout << i << ", ";
		cout << tmp.back() << " are running\n";
	}
	inline void Manager::DivideTasks(const string& exec_name, int arg)
	{
		for (int i = 0; i < tasks_amount; ++i)
		{
			in_pipes[i] << i << endl;
			in_pipes[i] << arg << endl;
		}
		for (int i = 0; i < tasks_amount; ++i)
			child_processes[i] = bp::child(exec_name, "OPTIONAL", bp::std_in < in_pipes[i], bp::std_out > out_pipes[i], bp::std_err > stderr);
	}
	void Manager::UpdateRunningProcesses()
	{
		std::set<int>& s = running_processes;
		for (auto it = s.begin(); it != s.end() && !stop_job;) {
			std::error_code err;
			int i = *it;
			if (!child_processes[i].running(err) && !err) {
				int tmp_res;
				out_pipes[i] >> tmp_res;

				if (!ProcessComputationalResult(i, tmp_res))
					return;

				res_vec[i] = tmp_res;
				it = s.erase(it);
				child_processes[i].wait();
			}
			else if (err)
				it = s.erase(it);
			else
				it++;
		}
	}
	int Manager::ProcessComputationalResult(int index, int tmp_res)
	{
		//cout << "Function " << index << ", res= " << tmp_res << endl;
		if (tmp_res == 0)
		{
			res = 0;
			StopRunningProcesses();
		}
		return running_processes.size(); //return number of active child processes for which manager should wait
	}
	void Manager::ComputeResult()
	{
		if (res.has_value())
			return;
		res = std::reduce(std::next(res_vec.begin()), res_vec.end(), res_vec.front(), std::move(res_func));
	}
	Manager::Manager() :
		stop_job(false), tasks_amount(0), res(std::nullopt), listener(nullptr)
	{}

	Manager::~Manager()
	{
		delete listener;
	}

	inline bool Manager::isRunning()
	{
		return !stop_job && running_processes.size();
	}

	void Manager::SetUp(int tasks_amount, std::function<int(int, int)>&& res_func)
	{
		this->tasks_amount = tasks_amount;
		in_pipes.resize(tasks_amount);
		out_pipes.resize(tasks_amount);
		child_processes.resize(tasks_amount);
		res_vec.resize(tasks_amount, -1);
		this->res_func = std::move(res_func);

		KeyEventListener *p = new KeyEventListener();
		p->AddHandler(KeyEventListener::KeyCode::ESCAPE, [this](bool pressed) {
			if (pressed)
				stop_job = true;
		});
		listener = p;
	}
	void Manager::RunVersion1(int argc, char** argv)
	{
		cout << "Enter function's argument: ";
		int func_arg;
		std::cin >> func_arg;

		DivideTasks(argv[0], func_arg);

		for (int i = 0; i < tasks_amount; ++i)
			running_processes.insert(i);
		listener->StartAsync();

		while (!stop_job && !running_processes.empty())
		{
			UpdateRunningProcesses();
			this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		listener->StopAsync();

		if (stop_job && !running_processes.empty())
		{
			cout << "Result can't be computed, because ";
			PrintRunningProcesses();
			StopRunningProcesses();
			// significant point: esc make stop_job = true
			// but musn't call StopRunningProcesses()
		}
		else {
			ComputeResult();
			cout << "\nComputations result= " << res.value() << endl;
		}

		system("pause");
	}
	void Manager::RunParrallelFunction()
	{
		namespace testing = spos::lab1::demo;

		// Parrallel processes accepts function number(0,1,2 ... ,n)
		// Currently used to identify whether call f or g, but can be generalized to n functions
		int f_number;
		cin >> f_number;

		int f_arg; 
		cin >> f_arg;

		int res;
		if (f_number & 1)
			res = testing::f_func<testing::INT>(f_arg);
		else
			res = testing::g_func<testing::INT>(f_arg);

		// For n functions external function call should be used
		// CallFunc(function_number, arg, res) or res = CallFunc(function_number, arg)
		cout << res << endl;
	}
}
