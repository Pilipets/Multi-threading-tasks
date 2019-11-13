#include "MyMutex.h"

namespace thread_sync {
	TicketLock::TicketLock() :
		_ticket_counter(0), _now_serving(0)
	{}

	void TicketLock::lock()
	{
		const auto ticket = _ticket_counter.fetch_add(1, std::memory_order_relaxed);
		while (_now_serving.load(std::memory_order_acquire) != ticket) {
			std::this_thread::yield();
		}
	}
	void TicketLock::unlock()
	{
		const auto successor = _now_serving.load(std::memory_order_relaxed) + 1;
		_now_serving.store(successor, std::memory_order_release);
	}
}