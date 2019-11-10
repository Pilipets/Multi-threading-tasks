#pragma once
#include <thread>
#include <unordered_map>

#include "Concepts.h"
namespace thread_sync {
	class BlackWhiteBakeryLock : public BasicLockable {
	private:
		int _get_thread_num(const std::thread::id& cur_id);
	public:
		BlackWhiteBakeryLock(int n = 40);
		~BlackWhiteBakeryLock();
		void lock() override;
		void unlock() override;
	private:
		enum class Color: bool {
			white, black
		};
		Color _shared_color;
		Color *_my_color;
		int* _number;
		const int _n;
		std::unordered_map<std::thread::id, int> _map_id;
	};
}