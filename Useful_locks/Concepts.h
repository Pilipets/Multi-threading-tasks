#pragma once

#include <atomic>
namespace thread_sync {
	const int NUM_THREADS = 40;
	class BasicLockable {
	public:
		virtual void lock(int i) = 0;
		virtual void unlock(int i) = 0;
	};

	class Lockable : public BasicLockable {
	public:
		virtual bool try_lock(int i) = 0;
	};
}