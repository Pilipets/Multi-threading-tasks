#include "MyMutex.h"

#include <algorithm>
#include <memory>

namespace thread_sync {
	ImprovedBakeryLock::ImprovedBakeryLock(int n) :
		_n(n), _ticket_counter(0)
	{
		_choosing = new bool[n];
		_number = new uint64_t[n];
		_map_id.reserve(n);

		memset((void*)_choosing, 0, n);
		memset((void*)_number, 0, n * sizeof(uint64_t));
	}
	ImprovedBakeryLock::~ImprovedBakeryLock()
	{
		delete[] _choosing;
		delete[] _number;
		_map_id.clear();
	}
	void ImprovedBakeryLock::lock()
	{
		int num = _get_thread_num(std::this_thread::get_id());

		_choosing[num] = true;
		_number[num] = _ticket_counter.fetch_add(1, std::memory_order_relaxed);
		_choosing[num] = false;

		for (int j = 0; j < _n; ++j) {
			while (_choosing[j]) {
				std::this_thread::yield();
			}
			while (_number[j] != 0 && _number[j] < _number[num])
				std::this_thread::yield();
		}
	}
	void ImprovedBakeryLock::unlock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_number[num] = 0;
	}
}