#include "MyMutex.h"

#include <cassert>
namespace thread_sync {
	int BlackWhiteBakeryLock::_produce_ticket(int i)
	{
		int ticket = 0;
		for (int j = 0; j < _n; ++j) {
			Color color = _my_color[j];
			int var = _number[j];
			if (_my_color[i] == color &&
				var > _number[i])
				ticket = var;
		}
		return 1 + ticket;
	}
	BlackWhiteBakeryLock::BlackWhiteBakeryLock() :
		_n(NUM_THREADS)
	{
		_shared_color = Color::white;
		_my_color = new Color[_n];
		_choosing = new bool[_n];
		_number = new int[_n];

		memset((void*)_my_color, 0, _n);
		memset((void*)_choosing, 0, _n);
		memset((void*)_number, 0, _n * sizeof(int));
	}
	BlackWhiteBakeryLock::~BlackWhiteBakeryLock()
	{
		delete[] _my_color;
		delete[] _choosing;
		delete[] _number;
	}
	void BlackWhiteBakeryLock::lock()
	{
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
		_shared_color = _my_color[num] == Color::black ? Color::white : Color::black;
		_number[num] = 0;
	}
}