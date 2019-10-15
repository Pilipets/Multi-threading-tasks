#pragma once

#include <chrono>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/process.hpp>

namespace spos::lab1::timeutils {
	template <class Clock = std::chrono::system_clock>
	class SimpleTimer;
}
namespace spos::lab1::version2 {
	using namespace std;
	using namespace spos::lab1::timeutils;
	namespace bp = boost::process;

	class Manager
	{
	private:
		void StopRunningProcesses();
		void DivideTasks(const string& exec_name, int arg);
		void UpdateRunningProcesses();
		void UpdatePromptMessage();
		int ProcessComputationalResult(int tmp_res);
		void ComputeResult();
	public:
		Manager();
		~Manager();

		void SetUp(int tasks_amount, std::chrono::milliseconds&& duration, std::function<int(int, int)> &&res_func = std::plus<int>());
		void RunVersion2(int argc, char** argv);
		static void RunParrallelFunction();
	private:
		bool stop_job, show_prompt;
		int tasks_amount;
		std::optional<int> res;
		std::string prompt_message;
		std::chrono::milliseconds prompt_interval;

		vector<bp::opstream> in_pipes;
		vector<bp::ipstream> out_pipes;
		vector<bp::child> child_processes;
		vector<int> res_vec;
		std::set<int> running_processes;
		std::function<int(int, int)> res_func;

		SimpleTimer<> *timer;
	};
}

