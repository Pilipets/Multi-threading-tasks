#pragma once

#include <string>
#include <vector>

#include <boost/process.hpp>

namespace spos::lab1 {
	using namespace std;
	namespace bp = boost::process;

	class Manager
	{
	private:
		void DivideTasks(const string& exec_name);
	public:
		Manager() = default;
		~Manager() = default;

		void SetUp(int tasks_amount);
		void Run(int argc, char** argv);
	private:
		int tasks_amount;
		vector<bp::opstream> in_pipes;
		vector<bp::ipstream> out_pipes;
		vector<bp::child> child_processes;
		vector<int> res_vec;
	};
}

