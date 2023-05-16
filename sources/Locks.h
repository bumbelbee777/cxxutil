#pragma once

#include <Atomic.h>

namespace Cxxutil {
class Spinlock {
	AtomicFlag Flag;
public:
	Spinlock() = default;

	void Lock() noexcept { while(Flag.TestAndSet()); }
	void Unlock() noexcept { Flag.Clear(); }
	bool TryLock() noexcept { return !Flag.TestAndSet(); }

	bool Locked() const noexcept { return Flag.Test(); }
};

template<class T> class Mutex {
    T Data_;
public:
    void Lock() noexcept { Spinlock_.Lock(); }
    void Unlock() noexcept { Spinlock_.Unlock(); }
	bool Locked() { return Spinlock_.Locked(); }
    T *operator->() noexcept { return &Data_; }
    T &operator*() noexcept { return Data_; }
};
}