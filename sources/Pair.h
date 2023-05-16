#pragma once

namespace Cxxutil {
template<class T, class U> struct Pair {
    T1 First;
    U Second;
	using first = First;
	using second = Second;

    Pair() : First(), Second() {}

    Pair(const T1 &First, const U &Second) : First(First), Second(Second) {}

    template<typename U1, typename U2>
    Pair(const Pair<U1, U2> &Other) : First(Other.First), Second(Other.Second) {}

    Pair(const Pair &Other) = default;

    Pair &operator=(const Pair &Other) = default;

    Pair(Pair &&Other) = default;

    Pair &operator=(Pair &&Other) = default;

    ~Pair() = default;

    bool operator==(const Pair &Other) const {
        return First == Other.First && Second == Other.Second;
    }
    bool operator!=(const Pair &Other) const { return *this != Other; }

    bool operator<(const Pair &Other) const {
        return First < Other.First || (!(Other.First < First) && Second < Other.Second);
    }
    bool operator>(const Pair &Other) const { return Other < *this; }

    bool operator<=(const Pair &Other) const { return !(Other < *this); }
    bool operator>=(const Pair &Other) const { return !(*this < Other); }
};

template<typename T, typename U>
Pair<T, TU> MakePair(const T &First, const U &Second) {
    return Pair<T, U>(First, Second);
}
}
