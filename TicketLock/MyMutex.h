#pragma once
#include <atomic>
#include <cstdint>

#include "Concepts.h"
	
namespace thread_sync {
	class TicketLock : public Lockable {
	private:
		uint32_t _bound_ticket(uint32_t ticket_value) const;
	public:
		TicketLock(uint32_t max_waiting_number = 0);
		~TicketLock() = default;
		void lock() override;
		bool try_lock() override;
		void unlock() override;
	private:
		std::atomic<uint32_t> _ticket_counter, _now_serving;
		const uint32_t _max_waiting; 
		// when we now the maximum number of threads waiting at the same time
		// for a shared resource, we can bound the ticket value
	};
}
