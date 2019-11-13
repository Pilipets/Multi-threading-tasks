#pragma once
#include <atomic>
#include <cstdint>
#include <thread>
#include <memory>

#include "Concepts.h"

namespace thread_sync {

	class ImprovedBakeryLock : public Lockable {
	public:
		ImprovedBakeryLock();
		~ImprovedBakeryLock() = default;
		void lock() override;
		bool try_lock() override;
		void unlock() override;
	private:
		std::atomic<uint64_t> _ticket_counter;
		std::unique_ptr<volatile uint64_t*> _token;
		const int _n;
	};

	class BlackWhiteBakeryLock : public BasicLockable {
	private:
		int _produce_ticket(int num);
	public:
		BlackWhiteBakeryLock();
		~BlackWhiteBakeryLock();
		void lock() override;
		void unlock() override;
	private:
		enum class Color : bool {
			white, black
		};
		volatile Color _shared_color;
		volatile Color *_my_color;
		volatile bool* _choosing;
		volatile int* _number;
		const int _n;
	};
}
