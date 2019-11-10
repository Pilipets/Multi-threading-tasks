#include "MyImprovedMutex.h"

#include <cassert>
namespace thread_sync {
	int BlackWhiteBakeryLock::_produce_ticket(int i)
	{
		int ticket = 0;
		for (int j = 0; j < _n; ++j) {
			if (_my_color[i] == _my_color[j] &&
				_number[j] > _number[i])
				ticket = _number[j];
		}
		return 1+ticket;
	}
	BlackWhiteBakeryLock::BlackWhiteBakeryLock(int n) :
		_n(n)
	{
		_shared_color = Color::white;
		_my_color = new Color[n];
		_choosing = new bool[n];
		_number = new int[n];
		_map_id.reserve(n);

		memset((void*)_my_color, 0, n);
		memset((void*)_choosing, 0, n);
		memset((void*)_number, 0, n * sizeof(int));
	}
	BlackWhiteBakeryLock::~BlackWhiteBakeryLock()
	{
		delete[] _my_color;
		delete[] _choosing;
		delete[] _number;
		_map_id.clear();
	}
	void BlackWhiteBakeryLock::lock()
	{
		int i = _get_thread_num(std::this_thread::get_id());

		_choosing[i] = true;
		_my_color[i] = _shared_color;
		_number[i] = _produce_ticket(i);
		assert(_number[i] <= _n);
		_choosing[i] = false;

		for (int j = 0; j < _n; ++j) {
			while (_choosing[j]) {
				std::this_thread::yield();
			}
			if (_my_color[j] == _my_color[i]) {
				while (_number[j] != 0 && _my_color[j] == _my_color[i] &&
					(_number[j] < _number[i] || _number[j] == _number[i] && j < i))
					std::this_thread::yield();
			}
			else {
				while (_number[j] != 0 && _my_color[j] != _my_color[i] &&
					_my_color[i] == _shared_color)
					std::this_thread::yield();
			}

		}
	}
	void BlackWhiteBakeryLock::unlock()
	{
		int num = _get_thread_num(std::this_thread::get_id());
		_shared_color = _my_color[num] == Color::black ? Color::white : Color::black;
		_number[num] = 0;
	}
}