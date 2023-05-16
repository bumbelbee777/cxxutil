#pragma once

#include <CTypes.h>
#include <Utility.h>

namespace Cxxutil {
template<class... T>
class Tuple {
	T Data[sizeof...(T)];

	template <size_t I = 0> auto Begin() -> decltype(auto) {
		if constexpr (I == sizeof...(T)) return &Data[sizeof...(T)];
		else return &Data[I];
	}

	template <size_t I = 0> auto End() -> decltype(auto) {
		if constexpr(I == sizeof...(T)) return &Data[sizeof...(T)];
		else return End<I + 1>();
	}
public:
	Tuple() = default;
	Tuple(const Tuple& other) {
		((void)(Data[Index] = other.Data[Index]), ...);
	}
	Tuple(Tuple&& other) {
		((void)(Data[Index] = Move(other.Data[Index])), ...);
	}

	template<size_t Index> auto &Get() { return Data[Index]; }

	friend bool operator==(const Tuple &lhs, const Tuple &rhs) {
		return Equal(Begin(lhs.Data), End(lhs.Data), Begin(rhs.Data), End(rhs.Data));
	}

	friend bool operator!=(const Tuple &lhs, const Tuple &rhs) {
		return lhs != rhs;
	}

	friend bool operator<(const Tuple &lhs, const Tuple &rhs) {
		return LexicographicalCompare(Begin(lhs.Data), End(lhs.Data), Begin(rhs.Data), End(rhs.Data));
	}

	friend bool operator<=(const Tuple &lhs, const Tuple &rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>(const Tuple &lhs, const Tuple &rhs) {
		return rhs < lhs;
	}

	friend bool operator>=(const Tuple &lhs, const Tuple &rhs) {
		return !(lhs < rhs);
	}
};
}