#pragma once

#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/process.hpp>

namespace key_listeners {
	class BaseEventListener;
}

namespace spos::lab1 {
	using namespace std;
	using namespace key_listeners;
	namespace bp = boost::process;

	class Manager
	{
	private:
		void ExitProcesses(const std::set<int> &running_processes);
		void DivideTasks(const string& exec_name);
		void UpdateProcessStatus(std::set<int> &running_processes);
		int ProcessComputationalResult(int tmp_res, std::set<int> &running_processes);
		void ComputeResult();
	public:
		Manager();
		~Manager() = default;

		void SetUp(int tasks_amount, std::function<int(int, int)> &&res_func = std::plus<int>());
		void Run(int argc, char** argv);
	private:
		bool stop_job;
		int tasks_amount;
		std::optional<int> res;

		vector<bp::opstream> in_pipes;
		vector<bp::ipstream> out_pipes;
		vector<bp::child> child_processes;
		vector<int> res_vec;
		std::function<int(int, int)> res_func;
		BaseEventListener* listener;
	};
}

