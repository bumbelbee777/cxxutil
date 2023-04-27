#pragma once

#include <Cxxutil.h>

template<class T> class UniquePointer {
public:
	UniquePointer() : RawPointer(nullptr) {}
	UniquePointer(T *Pointer) : RawPointer(Pointer) {}
	UniquePointer(UniquePointer &&Other) : RawPointer(Other.RawPointer) { Other.RawPointer = nullptr; }
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

	void Reset(T *Pointer = nullptr) {
		if(RawPointer) delete RawPointer;
		RawPointer = Pointer;
	}

	void Swap(UniquePointer &Other) { SWAP(RawPointer, Other.RawPointer); }

	T *Get() const { return RawPointer; }

	T *operator->() const { return RawPointer; }

	T &operator*() const { return *RawPointer; }

	explicit operator bool() const { return RawPointer != nullptr; }

private:
	T *RawPointer;
};