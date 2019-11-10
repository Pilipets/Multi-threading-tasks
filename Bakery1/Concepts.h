#pragma once
namespace thread_sync {
	class BasicLockable {
	public:
		virtual void lock() = 0;
		virtual void unlock() = 0;
	};

	class Lockable : public BasicLockable {
	public:
		virtual void try_lock() = 0;
	};
}