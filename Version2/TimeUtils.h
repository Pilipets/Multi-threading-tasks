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
}