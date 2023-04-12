#pragma once

#include <atomic>

namespace Cxxutil {
class Spinlock {
    std::atomic_flag Flag;
public:
    Spinlock() : Flag(ATOMIC_FLAG_INIT) {}
    void Lock() noexcept { while(Flag.test_and_set(std::memory_order_acquire)); }
    void Unlock() noexcept { Flag.clear(std::memory_order_release); }
    bool TryLock() noexcept { return !Flag.test_and_set(std::memory_order_acquire); }
    bool IsLocked() const noexcept { return Flag.test(std::memory_order_relaxed); }
};

template<class T> class Mutex {
    T Data_;
    Spinlock Spinlock_;
public:
    void Lock() noexcept { Spinlock_.Lock(); }
    void Unlock() noexcept { Spinlock_.Unlock(); }
    T *operator->() noexcept { return &Data_; }
    T &operator*() noexcept { return Data_; }
};
}