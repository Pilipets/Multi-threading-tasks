#pragma once
#include<vector>
#include<thread>
#include<functional>
#include <mutex>
#include <condition_variable>
#include <string>
#include<chrono>
#include<future>

#include "../Timer/Timer.h"

using namespace std::chrono_literals;
using namespace time_measuring;

namespace lab1_2 {
	extern const std::string prompt_message;
	class Prompt_Manager {
	private:
		void DivideTasks();
		void ComputeResult();
		void NotifyWithResult(int val);
		void DefaultSetUp();
	public:
		Prompt_Manager();
		void Run();
		void AddResultFunction(const std::function<int(int, int)> &, const std::string &description);
		void AddComputeFunction(const std::function<int(int)> &);
	private:
		std::vector<std::future<void> > working_threads;
		std::vector<std::function<int(int)> > compute_functions;
		std::vector<int> res_vec;
		int running_threads_amount;
		int function_amount;
		bool stop_job;
		int res;
		mutable std::mutex manager_mutex;
		mutable std::condition_variable ready_result;
		std::function<int(int, int) > res_function;
		BaseTimer timer;
	};
}