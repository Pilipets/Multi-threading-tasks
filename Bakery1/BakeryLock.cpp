#include "MyMutex.h"

#include <algorithm>
#include <string.h>

namespace thread_sync {
	int BakeryLock::_produce_ticket()
	{
		return 1 + *std::max_element(_number, _number + _n);
	}
	int BakeryLock::_get_thread_num(const std::thread::id & cur_id)
	{
		auto it = _map_id.find(cur_id);
		if (it == _map_id.end())
			it = _map_id.emplace(cur_id, _map_id.size()).first;
		return it->second;
	}
	BakeryLock::BakeryLock(int n)
	{
		_n = n;
		_choosing = new bool[n];
		_number = new int[n];
		_map_id.reserve(n);

		memset(_choosing, 0, n);
		memset((void*)_number, 0, n * sizeof(int));
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
		_number[num] = 1 + _produce_ticket();
		_choosing[num] = false;

		for (int j = 0; j < _n; ++j) {
			while (_choosing[j]) {
				std::this_thread::yield();
			}
			while (_number[j] != 0 && (_number[j] < _number[num] ||
				_number[j] == _number[num] && j < num)) {
				std::this_thread::yield();
			}
		}
	}
	void BakeryLock::unlock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_number[num] = 0;
	}
}