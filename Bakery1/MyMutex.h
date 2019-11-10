#pragma once
#include <cstdint>
#include <thread>
#include <unordered_map>

#include "Concepts.h"

namespace thread_sync {
	class BakeryLock : public BasicLockable{
	private:
		int _produce_ticket();
		int _get_thread_num(const std::thread::id& cur_id);
	public:
		BakeryLock(int n = 15);
		void lock() override;
		void unlock() override;
	private:
		bool* _choosing;
		int* _number;
		int _n;
		std::unordered_map<std::thread::id, int> _map_id;
	};
}
