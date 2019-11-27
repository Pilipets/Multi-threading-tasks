#include "MyMutex.h"

#include "debug.h"

#ifdef DEBUG
#include <cassert>
#endif

namespace thread_sync {
	inline uint64_t TicketLock::_bound_ticket(uint64_t ticket_value)
	{
		if (_max_waiting > 0)
			ticket_value %= _max_waiting;
		return ticket_value;
	}
	TicketLock::TicketLock(int max_waiting) :
		_ticket_counter(0), _now_serving(0), _max_waiting(max_waiting)
	{}

	void TicketLock::lock()
	{
		const auto ticket = _bound_ticket(_ticket_counter.fetch_add(1, std::memory_order_relaxed));
		#ifdef DEBUG
		if(_max_waiting != -1)
			assert(ticket < _max_waiting);
		#endif
		while (_now_serving.load(std::memory_order_acquire) != ticket) {
			std::this_thread::yield();
		}
	}
	bool TicketLock::try_lock()
	{
		auto cur_ticket = _now_serving.load(std::memory_order_acquire);
		bool acquired = false;
		if (_ticket_counter.compare_exchange_weak(cur_ticket, _bound_ticket(cur_ticket + 1), std::memory_order_release, std::memory_order_relaxed))
			acquired = true;

		return acquired;
	}
	void TicketLock::unlock()
	{
		const auto successor = _now_serving.load(std::memory_order_relaxed) + 1;
		_now_serving.store(_bound_ticket(successor), std::memory_order_release);
	}
}