#include "Timer.h"

void time_measuring::BaseTimer::SetTimeout(const std::chrono::milliseconds & ms, std::function<void(TimeOutReason)> callBack)
{
	timeoutThread = std::thread([=]()
	{
		std::unique_lock<std::mutex> lock(timerMutex);
		retStatus = condTimer.wait_for(lock, ms);
		TimeOutReason tReason;
		if (std::cv_status::timeout == retStatus) {
			tReason = TimeOutReason::TIMER_EXPIRED;
		}
		else {
		   tReason = TimeOutReason::SIGNAL_RECEIVED;
		}
		callBack(tReason);
	});
}

void time_measuring::BaseTimer::StopTimer()
{
	condTimer.notify_one();
	timeoutThread.join();
}
