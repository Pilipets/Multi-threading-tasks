#pragma once
#include <atomic>
#include <cstdint>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Concepts.h"

namespace thread_sync {
	class BakeryLock : public BasicLockable{
	private:
		inline uint64_t _produce_ticket();
		int _get_thread_num(const std::thread::id& cur_id);
	public:
		BakeryLock(int n = 40);
		~BakeryLock();
		void lock() override;
		void unlock() override;
	private:
		volatile bool* _choosing;
		volatile uint64_t* _number;
		const int _n;
		std::unordered_map<std::thread::id, int> _map_id;
	};

	class ImprovedBakeryLock : public BasicLockable {
	private:
		int _get_thread_num(const std::thread::id& cur_id);
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
		std::unordered_map<std::thread::id, int> _map_id;
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
