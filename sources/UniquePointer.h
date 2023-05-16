#pragma once

#include <Utility.h>

namespace Cxxutil {
template<class T> class UniquePointer {
	T *RawPointer;
public:
	UniquePointer() : RawPointer(nullptr) {}
	UniquePointer(T *Pointer) : RawPointer(Pointer) {}
	UniquePointer(UniquePointer &&Other) : RawPointer(Other.RawPointer) {
		Other.RawPointer = nullptr;
	}
	~UniquePointer() { Reset(); }

	UniquePointer &operator=(UniquePointer &&Other) {
		if(this != &Other) {
			Reset();
			RawPointer = Other.RawPointer;
			Other.RawPointer = nullptr;
		}
		return *this;
	}

	UniquePointer(const UniquePointer &Other) = delete;
	UniquePointer &operator=(const UniquePointer &Other) = delete;

	T *Release() {
		T *Result = RawPointer;
		RawPointer = nullptr;
		return Result;
	}

	void Reset(const T *Pointer = nullptr) {
		if(RawPointer) delete RawPointer;
		RawPointer = Pointer;
	}

	void Swap(UniquePointer &Other) { SWAP(RawPointer, Other.RawPointer); }

	T *Get() const { return RawPointer; }

	T *operator->() const { return RawPointer; }
	T &operator*() const { return *RawPointer; }

	explicit operator bool() const { return RawPointer != nullptr; }
};

template<class T, class... Args>
UniquePointer<T> MakeUnique(const Args &...Arguments) {
	return UniquePointer<T>(Forward<Args>(Arguments)...);
}
}