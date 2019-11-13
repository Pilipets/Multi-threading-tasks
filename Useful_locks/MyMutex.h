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
		bool try_lock(int i) override;
		void lock(int i) override;
		void unlock(int i) override;
	private:
		std::atomic<uint64_t> _ticket_counter;
		std::unique_ptr<volatile uint64_t[]> _token;
		const int _n;
	};

	class BlackWhiteBakeryLock : public Lockable {
	private:
		int _produce_ticket(int num);
	public:
		BlackWhiteBakeryLock();
		~BlackWhiteBakeryLock() = default;
		bool try_lock(int i) override;
		void lock(int i) override;
		void unlock(int i) override;
	private:
		volatile bool _shared_color;
		std::unique_ptr<volatile bool[]> _my_color;
		std::unique_ptr<volatile bool[]> _choosing;
		std::unique_ptr<volatile int[]> _number;
		const int _n;
	};
}
