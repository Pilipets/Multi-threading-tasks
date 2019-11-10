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
		inline int _produce_ticket();
		int _get_thread_num(const std::thread::id& cur_id);
	public:
		BakeryLock(int n = 40);
		~BakeryLock();
		void lock() override;
		void unlock() override;
	private:
		bool* _choosing;
		volatile int* _number;
		int _n;
		std::unordered_map<std::thread::id, int> _map_id;
	};
	class ImprovedBakeryLock : public BasicLockable {
	private:
		inline int _produce_ticket();
		int _get_thread_num(const std::thread::id& cur_id);
	public:
		ImprovedBakeryLock(int n = 40);
		~ImprovedBakeryLock();
		void lock() override;
		void unlock() override;
	private:
		std::atomic<int> *_number;
		int _n;
		std::unordered_map<std::thread::id, int> _map_id;
	};
}
