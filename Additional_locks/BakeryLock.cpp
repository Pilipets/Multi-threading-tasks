#include "MyMutex.h"

#include <algorithm>
#include <string.h>

namespace thread_sync {
	uint64_t BakeryLock::_produce_ticket()
	{
		return 1 + *std::max_element(_number, _number + _n);
	}
	BakeryLock::BakeryLock(int n):
		_n(n)
	{
		_choosing = new bool[n];
		_number = new uint64_t[n];
		_map_id.reserve(n);

		memset((void*)_choosing, 0, n);
		memset((void*)_number, 0, n * sizeof(uint64_t));
	}
	BakeryLock::~BakeryLock()
	{
		delete[] _choosing;
		delete[] _number;
		_map_id.clear();
	}
	void BakeryLock::lock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_choosing[num] = true;
		_number[num] = _produce_ticket();
		_choosing[num] = false;

		for (int j = 0; j < _n; ++j) {
			while (_choosing[j]) {
				std::this_thread::yield();
			}
			while (_number[j] != 0 && (_number[j] < _number[num] ||
				_number[j] == _number[num] && j < num))
				std::this_thread::yield();
		}
	}
	void BakeryLock::unlock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_number[num] = 0;
	}
}