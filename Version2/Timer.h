#pragma once
#include <iostream>
#include <string>
#include <future>
#include <mutex>
#include <chrono>
#include <queue>

namespace spos::lab1::timers {
	class Batcher
	{
	public:
		Batcher()
			: taskDelay(4), closing(false), running(false)
		{}

		void AddTask(const std::string& value)
		{
			std::unique_lock< std::mutex > lock(mutex);
			tasks.push(value);
			// increase the time to process the queue to "now + 4 seconds"
			timeout = std::chrono::steady_clock::now() + taskDelay;
			if (!running)
			{
				// launch a new asynchronous task which will process the queue
				task = std::async(std::launch::async, [this] { processWork(); });
				running = true;
			}
		}

		~Batcher()
		{
			std::unique_lock< std::mutex > lock(mutex);
			// stop processing the queue
			closing = true;
			bool wasRunning = running;
			condition.notify_all();
			lock.unlock();
			if (wasRunning)
			{
				task.wait();
			}
		}

	private:
		std::mutex mutex;
		std::condition_variable condition;
		std::chrono::seconds taskDelay;
		std::chrono::steady_clock::time_point timeout;
		std::queue<std::string> tasks;
		std::future<void> task;
		bool closing;
		bool running;

		void processWork()
		{
			std::unique_lock< std::mutex > lock(mutex);
			// loop until std::chrono::steady_clock::now() > timeout
			auto wait = timeout - std::chrono::steady_clock::now();
			while (!closing && wait > std::chrono::seconds(0))
			{
				condition.wait_for(lock, wait);
				wait = timeout - std::chrono::steady_clock::now();
			}
			if (!closing)
			{
				while (!tasks.empty())
				{
					std::cout << tasks.front() << "\n";
					tasks.pop();
				}
			}
			running = false;
		}
	};

	class SimpleTimer {
	private:
		template<class Function>
		void _Execute(const Function& func)
		{
			std::unique_lock< std::mutex > lk(timer_mutex);
			auto wait = timeout - std::chrono::steady_clock::now();
			while (!stop_job && wait > std::chrono::seconds(0))
			{
				terminated.wait_for(lk, wait);
				wait = timeout - std::chrono::steady_clock::now();
			}
			if (!stop_job)
				func();
			is_running = false;
		}
	public:
		SimpleTimer() = default;
		~SimpleTimer(){
			Stop();
		}
		template <class Callable, class... Arguments>
		void Start(Callable&& f, std::chrono::microseconds&& delay, bool async, Arguments&&... args)
		{
			std::function<typename std::result_of<Callable(Arguments...)>::type()> task(
				std::bind(std::forward<Callable>(f), std::forward<Arguments>(args)...));
			stop_job = false, is_running = true;
			timeout = std::chrono::steady_clock::now() + delay;
			if (async)
				working_future = std::async(std::launch::async, [task, this] { _Execute(task); });
			else
				_Execute(task);
		}
		void Stop()
		{
			std::unique_lock<std::mutex> lk(timer_mutex);
			stop_job = true;
			bool wasRunning = is_running;
			terminated.notify_all();
			lk.unlock();
			if (wasRunning)
			{
				working_future.wait();
			}
		}
	private:
		bool stop_job;
		bool is_running;
		std::mutex timer_mutex;
		std::condition_variable terminated;
		std::chrono::steady_clock::time_point timeout;
		std::future<void> working_future;
	};

}