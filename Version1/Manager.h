#pragma once

#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/process.hpp>

namespace key_listeners {
	class KeyEventListener;
}

namespace spos::lab1::version1 {
	using namespace std;
	using namespace key_listeners;
	namespace bp = boost::process;

	class Manager
	{
	private:
		// Terminates active child processes from running_processes set
		// After this method running_processes set is empty
		// Method is called if one of parrallel tasks returns zero
		// or computations were cancelled by user
		void StopRunningProcesses();

		// Creates child processes with redirecting stdin, stdout to the appropriate
		// unnamed pipes for each of them
		void DivideTasks(const string& exec_name, int arg);

		// Processes the result of finished processes,
		// updates running_processes set
		void UpdateRunningProcesses();

		int ProcessComputationalResult(int tmp_res);

		// Applies res_func to results from parrallel tasks
		// Result is stored in res
		void ComputeResult();
	public:
		Manager();
		~Manager();

		bool isRunning();
		// 
		void SetUp(int tasks_amount, std::function<int(int, int)> &&res_func = [](int a, int b)->int {
			return std::min(a, b);
		});
		void RunVersion1(int argc, char** argv);
		static void RunParrallelFunction();
	private:
		bool stop_job; // is set to true if and only if cancellation was requested by user
		int tasks_amount; // amount of parallel tasks
		std::optional<int> res; // res that is printed to console, can be non-set if computation was cancelled

		vector<bp::opstream> in_pipes;
		vector<bp::ipstream> out_pipes;
		vector<bp::child> child_processes;
		vector<int> res_vec; // vector stores results of parallel tasks
		std::set<int> running_processes; // set that stores indexes of running processes
		std::function<int(int, int)> res_func; // function being applied for the results of parallel tasks

		KeyEventListener  *listener; // Pointer to async listener that will handle console events(Esc, e.g)
	};
}

