#pragma once

namespace Cxxutil {
template<typename T1, typename T2>
class Pair {
public:
    using FirstType = T1;
    using SecondType = T2;

    T1 First;
    T2 Second;

    Pair() : First(), Second() {}

    Pair(const T1 &First, const T2 &Second) : First(First), Second(Second) {}

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

    bool operator!=(const Pair &Other) const {
        return !(*this == Other);
    }

    bool operator<(const Pair &Other) const {
        return First < Other.First || (!(Other.First < First) && Second < Other.Second);
    }

    bool operator>(const Pair &Other) const {
        return Other < *this;
    }

    bool operator<=(const Pair &Other) const {
        return !(Other < *this);
    }

    bool operator>=(const Pair &Other) const {
        return !(*this < Other);
    }
};

template<typename T1, typename T2>
Pair<T1, T2> MakePair(const T1 &First, const T2 &Second) {
    return Pair<T1, T2>(First, Second);
}
}
