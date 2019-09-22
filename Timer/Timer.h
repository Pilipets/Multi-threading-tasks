#pragma once

#include<chrono>
#include<utility>
#include<mutex>

namespace time_measuring {
	class BaseTimer {
	public:
		enum class TimeOutReason {
			TIMER_EXPIRED,
			SIGNAL_RECEIVED
		};
		void SetTimeout(const std::chrono::milliseconds & ms, std::function<void(TimeOutReason)> callBack);
		void StopTimer();
	private:
		std::mutex timerMutex;
		std::condition_variable condTimer;
		std::cv_status retStatus;
		std::thread timeoutThread;
	};
}