#include "Prompt_Manager.h"

#include<iostream>
#include <future>
using namespace std;

namespace lab1_2 {
	const std::string prompt_message = "-------User Prompt-------\n"\
		"1. Continue..................\n"\
		"2. Continue without prompt...\n"\
		"3. Cancel....................\n";

	void Prompt_Manager::DivideTasks()
	{
		running_threads_amount = function_amount;
		for (int i = 0; i < function_amount; ++i) {
			working_threads[i] = std::async(std::launch::async, [this, i]() {
				res_vec[i] = this->compute_functions[i](i * 2 + 1);
				this->NotifyWithResult(res_vec[i]);
			});
		}
	}

	void Prompt_Manager::ComputeResult()
	{
		if (function_amount > 1) {
			cout << "Computing the result" << endl;

			res = res_function(res_vec[0], res_vec[1]);
			for (int i = 2; i < function_amount; ++i)
				res = res_function(res, res_vec[i]);
		}
		else {
			cerr << "Insufficient amount of compute functions" << endl;
		}
	}

	void Prompt_Manager::NotifyWithResult(int val)
	{
		if (stop_job)
			return;

		unique_lock<std::mutex> lk(manager_mutex);
		cout << "Thread " << running_threads_amount << " finished job with result= " << val << endl;

		if (val == 0) {
			res = 0;
			stop_job = true;
		}
		running_threads_amount -= 1;
		if (!running_threads_amount || stop_job)
			ready_result.notify_one();
	}

	void Prompt_Manager::DefaultSetUp()
	{
		function_amount = 2;
		working_threads = vector<future<void>>(2);
		compute_functions = vector<function<int(int)> >(2);

		res_vec = vector<int>(2, -1);
		compute_functions[0] = [this](int x)->int {
			this_thread::sleep_for(3s);
			return x;
		};
		compute_functions[1] = [this](int x)->int {
			this_thread::sleep_for(5s);
			return x;
		};
	}

	Prompt_Manager::Prompt_Manager() :
		function_amount(0), running_threads_amount(0), res(-1), stop_job(false)
	{
		this->DefaultSetUp();
	}

	void Prompt_Manager::Run()
	{
		cout << "Started running main flow" << endl;
		this->DivideTasks();

		//wait until all tasks are finished || res == 0
		{
			std::unique_lock<std::mutex> lk(manager_mutex);
			ready_result.wait(lk, [this]() {
				return this->running_threads_amount == 0 || this->stop_job;
			});
		}

		//if all threads have finished their job
		if (!running_threads_amount && !stop_job) {
			for (int i = 0; i < function_amount; ++i)
				working_threads[i].get();
			this->ComputeResult();
			cout << "Res= " << res << endl;
		}

		//res = 0 || cancellation was requested
		else {
			if (res == 0)
				cout << "Res= " << 0 << endl;
			else
				cerr << "Computation process was stopped" << endl;
		}
		cout << "Finished running main flow" << endl;
	}

	void Prompt_Manager::AddResultFunction(const std::function<int(int, int)>& res_func, const string& description)
	{
		cout << "Added new result function: " << description << endl;
		this->res_function = std::move(res_func);
	}

	void Prompt_Manager::AddComputeFunction(const std::function<int(int)>& func)
	{
		compute_functions.push_back(std::move(func));
		function_amount += 1;
		working_threads.push_back(future<void>());
		res_vec.push_back(-1);
	}
}