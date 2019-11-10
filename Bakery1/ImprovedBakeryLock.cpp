#include "MyMutex.h"

#include <algorithm>
#include <memory>
namespace thread_sync {
	int ImprovedBakeryLock::_produce_ticket()
	{
		return 1 + *std::max_element(_number, _number + _n);
	}
	int ImprovedBakeryLock::_get_thread_num(const std::thread::id & cur_id)
	{
		auto it = _map_id.find(cur_id);
		if (it == _map_id.end())
			it = _map_id.emplace(cur_id, _map_id.size()).first;
		return it->second;
	}
	ImprovedBakeryLock::ImprovedBakeryLock(int n)
	{
		_n = n;
		_number = new std::atomic<int>[n];
		for (int i = 0; i < _n; ++i)
			_number[i] = 0;
		_map_id.reserve(n);
	}
	ImprovedBakeryLock::~ImprovedBakeryLock()
	{
		_map_id.clear();
		delete[] _number;
	}
	void ImprovedBakeryLock::lock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_number[num].store(_produce_ticket());

		for (int j = 0; j < _n; ++j) {
			while (_number[j] != 0 && _number[j] < _number[num]) {
				std::this_thread::yield();
			}
		}
	}
	void ImprovedBakeryLock::unlock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_number[num] = 0;
	}
}