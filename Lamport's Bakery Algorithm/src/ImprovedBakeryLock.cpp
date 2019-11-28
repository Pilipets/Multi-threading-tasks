#include "MyMutex.h"

#include <algorithm>

namespace thread_sync {
	ImprovedBakeryLock::ImprovedBakeryLock() :
		_n(NUM_THREADS), _ticket_counter(1)
	{
		_token = new uint64_t[_n];
		_choosing = new bool[_n];

		memset((void*)_token, 0, _n * sizeof(uint64_t));
		memset((void*)_choosing, 0, _n);
	}
	ImprovedBakeryLock::~ImprovedBakeryLock()
	{
		delete[] _choosing;
		delete[] _token;
	}
	bool ImprovedBakeryLock::try_lock(int num)
	{
		_choosing[num] = true;
		_token[num] = _ticket_counter.fetch_add(1, std::memory_order_relaxed);
		_choosing[num] = false;

		bool acquired = true;
		for (int j = 0; j < _n; ++j) {
			if (_choosing[j]) {
				acquired = false; break;
			}
			if (_token[j] != 0 && _token[j] < _token[num]) {
				acquired = false; break;
			}
		}
		if (!acquired)
			unlock(num);
		return acquired;
	}
	void ImprovedBakeryLock::lock(int num)
	{
		_choosing[num] = true;
		_token[num] = _ticket_counter.fetch_add(1, std::memory_order_relaxed);
		_choosing[num] = false;

		for (int j = 0; j < _n; ++j) {
			while (_choosing[j]) {
				std::this_thread::yield();
			}
			while (_token[j] != 0 && _token[j] < _token[num])
				std::this_thread::yield();
		}
	}
	void ImprovedBakeryLock::unlock(int num)
	{
		_token[num] = 0;
	}
}