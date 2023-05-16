#pragma once

namespace Cxxutil {
enum class StrongOrdering {
	Less = -1,
	Equal = 0,
	Greater = 1
};

enum class WeakOrdering {
	Less = -1,
	Equivalent = 0,
	Greater = 1
};

enum class PartialOrdering {
	Less = -1,
	Equivalent = 0,
	Greater = 1,
	Unordered = 2,
};

template<class T> constexpr StrongOrdering CompareThreeWay(const T &a, const T &b) {
	if(a < b) return StrongOrdering::Less;
	if(b > a) return StrongOrdering::Greater;
	else return StrongOrdering::Equal;
}

template<class T> constexpr WeakOrdering CompareWeakOrdering(const T &a, const T &b) {
	if(a < b) return WeakOrdering::Less;
	else if(a > b) return WeakOrdering::Greater;
	else return WeakOrdering::Equivalent;
}

template<class T> constexpr PartialOrdering ComparePartialOrdering(const T &a, const T &b) {
	if(a < b) return PartialOrdering::Less;
	else if(b > a) return PartialOrdering::Greater;
	else return PartialOrdering::Equivalent;
}

template<class T> constexpr bool operator==(const T &a, const T &b) noexcept {
	return CompareThreeWay(a, b) == StrongOrdering::Equal;
}

template<class T> constexpr bool operator!=(const T &a, const T &b) noexcept {
	return CompareThreeWay(a, b) != StrongOrdering::Equal;
}

template<class T> constexpr bool operator<(const T &a, const T &b) noexcept {
	return CompareThreeWay(a, b) == StrongOrdering::Less;
}

template<class T> constexpr bool operator>(const T &a, const T &b) noexcept {
	return CompareThreeWay(a, b) == StrongOrdering::Greater;
}

template<class T> constexpr bool operator<=(const T &a, const T &b) noexcept {
	return CompareThreeWay(a, b) != StrongOrdering::Greater;
}

template<class T> constexpr bool operator>=(const T &a, const T &b) noexcept {
	return CompareThreeWay(a, b) != StrongOrdering::Less;
}

template<class T> constexpr bool operator==(const WeakOrdering& a, const T& b) noexcept {
	return a == CompareWeakOrdering(a, b);
}

template<class T> constexpr bool operator==(const T& a, const WeakOrdering& b) noexcept {
	return b == CompareWeakOrdering(a, b);
}

template<class T> constexpr bool operator!=(const WeakOrdering& a, const T& b) noexcept {
	return a != CompareWeakOrdering(a, b);
}

template<class T> constexpr bool operator!=(const T& a, const WeakOrdering& b) noexcept {
	return b != CompareWeakOrdering(a, b);
}

template<class T> constexpr bool operator==(const PartialOrdering& a, const T& b) noexcept {
	return a == ComparePartialOrdering(a, b);
}

template<class T> constexpr bool operator==(const T& a, const PartialOrdering& b) noexcept {
	return b == ComparePartialOrdering(a, b);
}

template<class T> constexpr bool operator!=(const PartialOrdering& a, const T& b) noexcept {
	return a != ComparePartialOrdering(a, b);
}

template<class T> constexpr bool operator!=(const T& a, const PartialOrdering& b) noexcept {
	return b != ComparePartialOrdering(a, b);
}

template<class T> constexpr bool operator<(const WeakOrdering& a, const T& b) noexcept {
	return a == WeakOrdering::Less ||
	       (a == WeakOrdering::Equivalent && CompareWeakOrdering(a, b) == WeakOrdering::Less);
}

template<class T> constexpr bool operator<(const T& a, const WeakOrdering& b) noexcept {
	return b == WeakOrdering::Greater ||
	       (b == WeakOrdering::Equivalent && CompareWeakOrdering(a, b) == WeakOrdering::Less);
}

template<class T> constexpr bool operator>(const WeakOrdering& a, const T& b) noexcept {
	return a == WeakOrdering::Greater ||
	       (a == WeakOrdering::Equivalent && CompareWeakOrdering(a, b) == WeakOrdering::Greater);
}

template<class T> constexpr bool operator>(const T& a, const WeakOrdering& b) noexcept {
	return b == WeakOrdering::Less ||
	       (b == WeakOrdering::Equivalent && CompareWeakOrdering(a, b) == WeakOrdering::Greater);
}

template<class T> constexpr bool operator<=(const WeakOrdering& a, const T& b) noexcept {
	return !(a == WeakOrdering::Greater) &&
	       (a == WeakOrdering::Less || CompareWeakOrdering(a, b) == WeakOrdering::Less);
}

template<class T> constexpr bool operator<=(const T& a, const WeakOrdering& b) noexcept {
	return !(b == WeakOrdering::Less) &&
	       (b == WeakOrdering::Greater || CompareWeakOrdering(a, b) == WeakOrdering::Less);
}

template<class T> constexpr bool operator>=(const WeakOrdering& a, const T& b) noexcept {
	return !(a == WeakOrdering::Less) &&
	       (a == WeakOrdering::Greater || CompareWeakOrdering(a, b) == WeakOrdering::Greater);
}

template<class T> constexpr bool operator>=(const T& a, const WeakOrdering& b) noexcept {
	return !(b == WeakOrdering::Greater) &&
	       (b == WeakOrdering::Less || CompareWeakOrdering(a, b) == WeakOrdering::Greater);
}

template<class T> constexpr bool operator<(const PartialOrdering& a, const T& b) noexcept {
	return a == PartialOrdering::Less ||
	       (a == PartialOrdering::Equivalent && ComparePartialOrdering(a, b) == PartialOrdering::Less);
}

template<class T> constexpr bool operator<(const T& a, const PartialOrdering& b) noexcept {
	return b == PartialOrdering::Greater ||
	       (b == PartialOrdering::Equivalent && ComparePartialOrdering(a, b) == PartialOrdering::Less);
}

template<class T> constexpr bool operator>(const PartialOrdering& a, const T& b) noexcept {
	return a == PartialOrdering::Greater ||
	       (a == PartialOrdering::Equivalent && ComparePartialOrdering(a, b) == PartialOrdering::Greater);
}

template<class T> constexpr bool operator>(const T& a, const PartialOrdering& b) noexcept {
	return b == PartialOrdering::Less ||
	       (b == PartialOrdering::Equivalent && ComparePartialOrdering(a, b) == PartialOrdering::Greater);
}

template<class T> constexpr bool operator<=(const PartialOrdering& a, const T& b) noexcept {
	return !(a == PartialOrdering::Greater) && (a == PartialOrdering::Less || ComparePartialOrdering
}
}