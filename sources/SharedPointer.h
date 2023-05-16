#pragma once

namespace Cxxutil {
template<class T> class SharedPointer {
	T *Pointer;
	size_t *ReferenceCount;
public:
	SharedPointer()
	    : Pointer(nullptr), ReferenceCount(nullptr) {}
	explicit SharedPointer(T *Pointer_)
	    : Pointer(Pointer_), ReferenceCount(new size_t(1)) {}
	SharedPointer(const SharedPointer &Other)
	    : Pointer(Other.Pointer), ReferenceCount(Other.ReferenceCount) {
		if(ReferenceCount) (*ReferenceCount)++;
	}

	SharedPointer(SharedPointer &&Other) noexcept
	    : Pointer(Other.Pointer), ReferenceCount(Other.ReferenceCount) {
		Other.Pointer = nullptr;
		Other.ReferenceCount = nullptr;
	}

	SharedPointer &operator=(const SharedPointer &Other) {
		if(Pointer == Other.Pointer) return *this;

		if(ReferenceCount && (*ReferenceCount)-- == 0) {
			delete Pointer;
			delete ReferenceCount;
		}
		Pointer = Other.Pointer;
		ReferenceCount = Other.ReferenceCount;
		if(ReferenceCount) (*ReferenceCount)++;
		return *this;
	}

	SharedPointer &operator=(SharedPointer &&Other) noexcept {
		std::swap(Pointer, Other.Pointer);
		std::swap(ReferenceCount, Other.ReferenceCount);
		return *this;
	}

	~SharedPointer() {
		if(ReferenceCount && --(*ReferenceCount) == 0) {
			delete Pointer;
			delete ReferenceCount;
		}
	}

	T &operator*() const { return *Pointer; }
	T *operator->() const { return Pointer; }

	T *Get() const { return Pointer; }

	explicit operator bool() const { return Pointer != nullptr; }

	size_t UseCount() const { return ReferenceCount ? *ReferenceCount : 0; }
};
}
