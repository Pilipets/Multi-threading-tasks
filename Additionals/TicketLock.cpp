#include "MyMutex.h"

#include <thread>
#include "debug.h"

#ifdef DEBUG
#include <cassert>
#endif


namespace thread_sync {
	// _max_waiting variable and _bound_ticket() method can 
	// be deleted as in C++ after overflowing unsigned integer turns into a zero
	// But they are left here for consistency
	inline uint32_t TicketLock::_bound_ticket(uint32_t ticket_value)
	{
		// overflow is safe, as long as the number of threads using the lock is less 
		// than or equal to the value range representable by the counter’s underlying integer type
		if (_max_waiting > 0)
			ticket_value %= _max_waiting;
		return ticket_value;
	}
	TicketLock::TicketLock(uint32_t max_waiting) :
		_ticket_counter(0), _now_serving(0), _max_waiting(max_waiting)
	{}

	void TicketLock::lock()
	{
		const auto ticket = _bound_ticket(_ticket_counter.fetch_add(1, std::memory_order_relaxed));
		#ifdef DEBUG
		if(_max_waiting > 0)
			assert(ticket < _max_waiting);
		#endif
		while (_now_serving.load(std::memory_order_acquire) != ticket) {
			std::this_thread::yield();
		}
	}
	bool TicketLock::try_lock()
	{
		bool acquired = false;
		auto cur_ticket = _now_serving.load(std::memory_order_acquire);
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