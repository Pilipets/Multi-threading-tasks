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

namespace spos::lab1 {
	using namespace std;
	using namespace key_listeners;
	namespace bp = boost::process;

	class Manager
	{
	private:
		void StopRunningProcesses();
		void DivideTasks(const string& exec_name);
		void UpdateRunningProcesses();
		int ProcessComputationalResult(int tmp_res);
		void ComputeResult();
	public:
		Manager();
		~Manager();

		void SetUp(int tasks_amount, std::function<int(int, int)> &&res_func = std::plus<int>());
		void RunVersion1(int argc, char** argv);
	private:
		bool stop_job;
		int tasks_amount;
		std::optional<int> res;

		vector<bp::opstream> in_pipes;
		vector<bp::ipstream> out_pipes;
		vector<bp::child> child_processes;
		vector<int> res_vec;
		std::set<int> running_processes;
		std::function<int(int, int)> res_func;

		KeyEventListener  *listener;
	};
}

