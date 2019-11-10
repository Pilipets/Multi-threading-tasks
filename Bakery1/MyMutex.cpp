#include "MyMutex.h"

#include <string.h>

namespace thread_sync {
	int BakeryLock::_produce_ticket()
	{
		int *vals = new int[_n];
		memcpy(vals, _number, sizeof(int)*_n);
		int ticket = vals[0];

		for (int i = 0; i < _n; ++i)
			if (vals[i] > ticket)
				ticket = vals[i];
		return ticket;
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
		memset(_number, 0, n * sizeof(int));
	}
	void BakeryLock::lock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_choosing[num] = true;
		_number[num] = 1 + _produce_ticket();
		_choosing[num] = false;

		for (int j = 0; j < _n; ++j) {
			while (_choosing[j]);
			while (_number[j] != 0 && (_number[j] < _number[num] || 
				_number[j] == _number[num] && j < num));
		}
	}
	void BakeryLock::unlock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_number[num] = 0;
	}
}