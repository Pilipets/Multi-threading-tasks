#pragma once

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <queue>

namespace spos::lab1::timeutils {
	template <class Clock = std::chrono::system_clock>
	class SimpleTimer {
	private:
		using TimePoint = typename Clock::time_point;
		using Duration = typename Clock::duration;
	public:
		void Start(const Duration &duration) {
			expire_time = Clock::now() + duration;
		}
		bool Finished() {
			return Clock::now() >= expire_time;
		}
	private:
		TimePoint expire_time;
	};

	class CallbackTimer {
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
		CallbackTimer() = default;
		~CallbackTimer(){
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