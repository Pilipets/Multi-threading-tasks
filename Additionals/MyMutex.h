#pragma once
#include <atomic>
#include <cstdint>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Concepts.h"

namespace thread_sync {
	class TicketLock : public Lockable {
	public:
		TicketLock();
		~TicketLock() = default;
		void lock() override;
		bool try_lock() override;
		void unlock() override;
	private:
		std::atomic<uint64_t> _ticket_counter, _now_serving;
	};
}
