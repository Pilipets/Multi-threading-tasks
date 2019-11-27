#pragma once
#include <atomic>
#include <cstdint>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Concepts.h"
	
namespace thread_sync {
	class TicketLock : public Lockable {
	private:
		uint64_t _bound_ticket(uint64_t ticket_value);
	public:
		TicketLock(int max_waiting_number = -1);
		~TicketLock() = default;
		void lock() override;
		bool try_lock() override;
		void unlock() override;
	private:
		std::atomic<uint64_t> _ticket_counter, _now_serving;
		int _max_waiting; 
		// when we now the maximum number of threads waiting at the same time
		// for a shared resource, we can bound the ticket value
	};
}
