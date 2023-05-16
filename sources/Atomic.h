#pragma once

namespace Cxxutil {
enum class MemoryOrdering {
	Release,
	Acquire,
	Relaxed,
	Consume,
	AcquireRelease
};

template<class T> class Atomic {
	T Value;
public:
	Atomic() : Value() {}
	explicit Atomic(T Value) : Value(Value) {}

	void Store(T Value_, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				__atomic_store_n(&Value, Value_, __ATOMIC_RELEASE);
				break;
			case MemoryOrdering::Acquire:
				__atomic_store_n(&Value, Value_, __ATOMIC_ACQUIRE);
				break;
			case MemoryOrdering::Relaxed:
				__atomic_store_n(&Value, Value_, __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::Consume:
				__atomic_store_n(&Value, Value_, __ATOMIC_CONSUME);
				break;
			case MemoryOrdering::AcquireRelease:
				__atomic_store_n(&Value, Value_, __ATOMIC_ACQ_REL);
				break;
		}
	}

	T Load(MemoryOrdering Order = MemoryOrdering::Relaxed) const {
		T Result;
		switch(Order) {
			case MemoryOrdering::Release:
				Result = __atomic_load_n(&Value, __ATOMIC_RELEASE);
				break;
			case MemoryOrdering::Acquire:
				Result = __atomic_load_n(&Value, __ATOMIC_ACQUIRE);
				break;
			case MemoryOrdering::Relaxed:
				Result = __atomic_load_n(&Value, __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::Consume:
				Result = __atomic_load_n(&Value, __ATOMIC_CONSUME);
				break;
			case MemoryOrdering::AcquireRelease:
				Result = __atomic_load_n(&Value, __ATOMIC_ACQ_REL);
				break;
		}
		return Result;
	}

	T Exchange(T value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		T OldValue;
		switch(Order) {
			case MemoryOrdering::Release:
				__atomic_exchange(&Value, &Value, &OldValue, __ATOMIC_RELEASE);
				break;
			case MemoryOrdering::Acquire:
				__atomic_exchange(&Value, &Value, &OldValue, __ATOMIC_ACQUIRE);
				break;
			case MemoryOrdering::Relaxed:
				__atomic_exchange(&Value, &Value, &OldValue, __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::Consume:
				__atomic_exchange(&Value, &Value, &OldValue, __ATOMIC_CONSUME);
				break;
			case MemoryOrdering::AcquireRelease:
				__atomic_exchange(&Value, &Value, &OldValue, __ATOMIC_ACQ_REL);
				break;
		}
		return OldValue;
	}

	bool CompareExchange(T Expected, T Desired, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		bool Success;
		switch(Order) {
			case MemoryOrdering::Release:
				Success = __atomic_compare_exchange_n(&Value, &Expected, Desired, false, __ATOMIC_RELEASE, __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::Acquire:
				Success = __atomic_compare_exchange_n(&Value, &Expected, Desired, false, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::Relaxed:
				Success = __atomic_compare_exchange_n(&Value, &Expected, Desired, false, __ATOMIC_RELAXED, __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::Consume:
				Success = __atomic_compare_exchange_n(&Value, &Expected, Desired, false, __ATOMIC_CONSUME. __ATOMIC_RELAXED);
				break;
			case MemoryOrdering::AcquireRelease:
				Success = __atomic_compare_exchange_n(&Value, &Expected, Desired, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
				break;
		}
		return Success;
	}

	T FetchAdd(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_fetch_add(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_fetch_add(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_fetch_add(&Value, Value, __ATOMIC_RELAXED);
			case MemoryOrdering::Consume:
				return __atomic_fetch_add(&Value, Value, __ATOMIC_CONSUME);
			case MemoryOrdering::AcquireRelease:
				return __atomic_fetch_add(&Value, Value, __ATOMIC_ACQ_REL);
		}
	}

	T FetchSub(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_fetch_sub(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_fetch_sub(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_fetch_sub(&Value, Value, __ATOMIC_RELAXED);
			case MemoryOrdering::Consume:
				return __atomic_fetch_sub(&Value, Value, __ATOMIC_CONSUME);
			case MemoryOrdering::AcquireRelease:
				return __atomic_fetch_sub(&Value, Value, __ATOMIC_ACQ_REL);
		}
	}

	T FetchAnd(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_fetch_and(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_fetch_and(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_fetch_and(&Value, Value, __ATOMIC_RELAXED);
			case MemoryOrdering::Consume:
				return __atomic_fetch_and(&Value, Value, __ATOMIC_CONSUME);
			case MemoryOrdering::AcquireRelease:
				return __atomic_fetch_and(&Value, Value, __ATOMIC_ACQ_REL);
		}
	}

	T FetchOr(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_fetch_or(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_fetch_or(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_fetch_or(&Value, Value, __ATOMIC_RELAXED);
			case MemoryOrdering::Consume:
				return __atomic_fetch_or(&Value, Value, __ATOMIC_CONSUME);
			case MemoryOrdering::AcquireRelease:
				return __atomic_fetch_or(&Value, Value, __ATOMIC_ACQ_REL);
		}
	}

	T FetchXor(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_fetch_xor(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_fetch_xor(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_fetch_xor(&Value, Value, __ATOMIC_RELAXED);
		}
	}

	T AddAndFetch(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_add_fetch(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_add_fetch(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_add_fetch(&Value, Value, __ATOMIC_RELAXED);
		}
	}

	T SubAndFetch(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_sub_fetch(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_sub_fetch(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_sub_fetch(&Value, Value, __ATOMIC_RELAXED);
		}
	}

	T AndAndFetch(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_and_fetch(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_and_fetch(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_and_fetch(&Value, Value, __ATOMIC_RELAXED);
		}
	}

	T OrAndFetch(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_or_fetch(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_or_fetch(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_or_fetch(&Value, Value, __ATOMIC_RELAXED);
		}
	}

	T XorAndFetch(T Value, MemoryOrdering Order = MemoryOrdering::Relaxed) {
		switch(Order) {
			case MemoryOrdering::Release:
				return __atomic_xor_fetch(&Value, Value, __ATOMIC_RELEASE);
			case MemoryOrdering::Acquire:
				return __atomic_xor_fetch(&Value, Value, __ATOMIC_ACQUIRE);
			case MemoryOrdering::Relaxed:
				return __atomic_xor_fetch(&Value, Value, __ATOMIC_ACQUIRE);
		}
	}

	[[nodiscard]] bool IsLockFree() const { return __atomic_is_lock_free(sizeof(T), &Value); }

	void WaitForValue(T Value_) const {
		while(Load() != Value_) asm volatile("pause");
	}

	template<typename Predicate>
	void WaitForPredicate(Predicate pred) const {
		while(!pred(Load())) __asm__ __volatile__("pause");
	}

	T operator++(int) { return FetchAdd(1); }
	T operator--(int) { return FetchSub(1); }

	T operator++() { return FetchAdd(1) + 1; }
	T operator--() { return FetchSub(1) - 1; }

	T operator+=(T Value) { return FetchAdd(Value) + Value; }
	T operator-=(T Value) { return FetchSub(Value) - Value; }

	T operator&=(T Value) { return FetchAnd(Value) & Value; }
	T operator|=(T Value) { return FetchOr(Value) | Value; }
	T operator^=(T Value) { return FetchXor(Value) ^ Value; }

	bool operator==(T Value) const { return Load() == Value; }
	bool operator!=(T Value) const { return Load() != Value; }
};

class AtomicFlag {
	bool Flag;
public:
	AtomicFlag() : Flag(false) {}

	void Clear() { Flag = false; }

	bool TestAndSet() {
		bool OldValue = Flag;
		Flag = true;
		return OldValue;
	}

	void WaitAndSet() {
		while(TestAndSet()) {
#ifdef __X86_64__
			asm("pause");
#elifdef __aarch64__
			asm("yield");
		}
#endif
	}

	bool Test() const { return Flag; }

	operator bool() const { return Flag; }

	bool Exchange(bool DesiredValue) {
		bool OldValue = Flag;
		Flag = DesiredValue;
		return OldValue;
	}

	void WaitForClear() {
		while(Test()) {
#ifdef __X86_64__
    		asm("pause");
#elifdef __aarch64__
			asm("yield");
#endif
		}
	}
};
}
} // namespace Cxxutil
