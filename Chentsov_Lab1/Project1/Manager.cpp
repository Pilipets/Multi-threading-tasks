#include "Manager.h"

#include <chrono>
#include <iostream>
#include <numeric>

#include "EventListener.h"

namespace spos::lab1 {
	inline void Manager::ExitProcesses(const std::set<int>& s)
	{
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
	void Manager::UpdateProcessStatus(std::set<int>& s)
	{
		for (auto it = s.begin(); it != s.end() && !stop_job;) {
			int i = *it;
			if (!child_processes[i].running()) {
				int tmp_res;
				out_pipes[i] >> tmp_res;

				if (!ProcessComputationalResult(tmp_res, s))
					return;

				res_vec[i] = tmp_res;
				cout << "i= " << i << ", res= " << res_vec[i] << endl;
				it = s.erase(it);
				child_processes[i].wait(); // we do not need to wait actually here...
			}
			else
				it++;
		}
	}
	int Manager::ProcessComputationalResult(int tmp_res, set<int> &s)
	{
		if (tmp_res == 4)
		{
			res = 0;
			ExitProcesses(s);
			s.clear();
		}
		return s.size(); //return number of active child processes for which manager should wait
	}
	void Manager::ComputeResult()
	{
		if (res.has_value())
			return;
		res = std::reduce(res_vec.begin(), res_vec.end(), 0, std::move(res_func));
	}
	Manager::Manager() :
		stop_job(false), tasks_amount(0), res(std::nullopt), listener(nullptr)
	{}

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
	void Manager::Run(int argc, char** argv)
	{
		DivideTasks(argv[0]);
		listener->StartAsync();
		set<int> s;
		for (int i = 0; i < tasks_amount; ++i)
			s.insert(i);

		while (!stop_job && !s.empty())
		{
			UpdateProcessStatus(s);
			this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		listener->StopAsync();

		if (stop_job)
		{
			cout << "Result computation has been stopped" << endl;
		}
		else {
			ComputeResult();
			cout << "Res= " << res.value() << endl;
		}

		system("pause");
	}
}
