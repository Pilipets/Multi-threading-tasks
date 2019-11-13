#include "MyMutex.h"

#include <algorithm>

const int thread_sync::NUM_THREADS = 40;

namespace thread_sync {
	ImprovedBakeryLock::ImprovedBakeryLock() :
		_n(NUM_THREADS), _ticket_counter(1)
	{
		_token = std::make_unique<volatile uint64_t*>(_n);
		memset((void*)_token.get(), 0, _n * sizeof(uint64_t));
	}
	void ImprovedBakeryLock::lock()
	{
		_token[num] = _ticket_counter.fetch_add(1, std::memory_order_relaxed);

		for (int j = 0; j < _n; ++j) {
			while (_token[j] != 0 && _token[j] < _token[num])
				std::this_thread::yield();
		}
	}
	bool ImprovedBakeryLock::try_lock()
	{
		_token[num] = _ticket_counter.fetch_add(1, std::memory_order_relaxed);
		bool acquired = true;
		for (int j = 0; j < _n && acquired; ++j) {
			if (_token[j] != 0 && _token[j] < _token[num]) {
				acquired = false;
				_token[num] = 0;
			}
		}
		return acquired;
	}
	void ImprovedBakeryLock::unlock()
	{
		_token[num] = 0;
	}
}