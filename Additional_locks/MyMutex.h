#pragma once
#include <atomic>
#include <cstdint>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Concepts.h"

namespace thread_sync {
	class BakeryLock : public BasicLockable, public ThreadMapping {
	private:
		inline uint64_t _produce_ticket();
	public:
		BakeryLock(int n = 40);
		~BakeryLock();
		void lock() override;
		void unlock() override;
	private:
		volatile bool* _choosing;
		volatile uint64_t* _number;
		const int _n;
	};

	class ImprovedBakeryLock : public BasicLockable, public ThreadMapping {
	public:
		ImprovedBakeryLock(int n = 40);
		~ImprovedBakeryLock();
		void lock() override;
		void unlock() override;
	private:
		std::atomic<uint64_t> _ticket_counter;
		volatile bool* _choosing;
		volatile uint64_t* _number;
		const int _n;
	};

	class TicketLock : public BasicLockable {
	public:
		TicketLock();
		~TicketLock() = default;
		void lock() override;
		void unlock() override;
	private:
		std::atomic<uint64_t> _ticket_counter, _now_serving;
	};
}
