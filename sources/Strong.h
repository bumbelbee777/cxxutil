#pragma once

namespace Cxxutil {
template<class T, class Tag>
class Strong {
    T Value;
public:
    explicit Strong(T const& Value) : Value(Value) {}
    T& Get() { return Value; }
    T const& Get() const { return Value; }

    bool operator==(const Strong<T, Tag> &Other) const {
        return Value == Other.Value;
    }

    bool operator!=(const Strong<T, Tag> &Other) const {
        return !(*this == Other);
    }

    bool operator<(const Strong<T, Tag> &Other) const {
        return Value < Other.Value;
    }

    bool operator>(const Strong<T, Tag> &Other) const {
        return Other < *this;
    }

    bool operator<=(const Strong<T, Tag> &Other) const {
        return !(Other < *this);
    }

    bool operator>=(const Strong<T, Tag> &Other) const {
        return !(*this < Other);
    }

    Strong<T, Tag>& operator+=(const Strong<T, Tag> &Other) {
        Value += Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator-=(const Strong<T, Tag> &Other) {
        Value -= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator*=(const Strong<T, Tag> &other) {
        Value *= other.Value;
        return *this;
    }

    Strong<T, Tag>& operator/=(const Strong<T, Tag> &Other) {
        Value /= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator%=(const Strong<T, Tag> &Other) {
        Value %= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator&=(const Strong<T, Tag> &Other) {
        Value &= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator|=(const Strong<T, Tag> &Other) {
        Value |= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator^=(const Strong<T, Tag> &Other) {
        Value ^= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator<<=(const Strong<T, Tag> &Other) {
        Value <<= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator>>=(const Strong<T, Tag> Other) {
        Value >>= Other.Value;
        return *this;
    }

    Strong<T, Tag>& operator++() {
        Value++;
        return *this;
    }

    Strong<T, Tag> operator++(int) {
        Strong<T, Tag> Result(*this);
        operator++();
        return Result;
    }

    Strong<T, Tag>& operator--() {
        Value--;
        return *this;
    }

    Strong<T, Tag> operator--(int) {
        Strong<T, Tag> Result(*this);
        operator--();
        return Result;
    }
};
}
