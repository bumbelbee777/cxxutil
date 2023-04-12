#pragma once

#include <Std.h>

namespace Cxxutil {
template<class T> class Slice {
	T *Data_;
	size_t Size_;
public:
	Slice(T *Data, size_t Size) : Data_(Data), Size_(Size) {}

	T &operator[](size_t Index) {
		return Data_[Index];
	}

	const T &operator[](size_t Index) const {
		return Data_[Index];
	}

	T *begin() const { return Data_; }
	T *end() const { return Data_ + Size_; }

	size_t Size() const { return Size_; }
};
}
