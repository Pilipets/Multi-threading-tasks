#pragma once

#include <set>
#include <string>
#include <vector>

#include <boost/process.hpp>

namespace spos::lab1 {
	using namespace std;
	namespace bp = boost::process;
	class Manager
	{
	private:
		void ExitProcesses(const std::set<int> &running_processes);
		void DivideTasks(const string& exec_name);
		void CheckProcessStatus(std::set<int> &running_processes);
		void ComputeResult();
	public:
		Manager();
		~Manager() = default;

		void SetUp(int tasks_amount);
		void Run(int argc, char** argv);
	private:
		bool stop_job;
		int tasks_amount;
		vector<bp::opstream> in_pipes;
		vector<bp::ipstream> out_pipes;
		vector<bp::child> child_processes;
		vector<int> res_vec;
	};
}

