#pragma once

namespace Cxxutil {
class Iterator {
    T *Pointer;
public:
    Iterator(T *Pointer) : Pointer(Pointer) {}

    Iterator &operator++() {
        Pointer++;
        return *this;
    }
    Iterator operator++(int) {
        Iterator Result(*this);
        Pointer++;
        return Result;
    }

    Iterator &operator--() {
        Pointer--;
        return *this;
    }
    Iterator operator--(int) {
        Iterator Result(*this);
        Pointer--;
        return Result;
    }

    T &operator*() const {
        return *Pointer;
    }
    T *operator->() const {
        return Pointer;
    }

    bool operator==(const Iterator& Other) const {
        return Pointer == Other.Pointer;
    }
    bool operator!=(const Iterator& Other) const {
        return !(*this == Other);
    }

    friend Iterator &operator+=(ptrdiff_t n) {
        Pointer += n;
        return *this;
    }
    friend Iterator &operator-=(ptrdiff_t n) {
        Pointer -= n;
        return *this;
    }

    friend Iterator operator+(Iterator LHS, const ptrdiff_t RHS) {
        LHS += RHS;
        return LHS;
    }
    friend Iterator operator+(const ptrdiff_t &LHS, Iterator RHS) {
        RHS += LHS;
        return RHS;
    }

    friend Iterator operator-(Iterator LHS, const ptrdiff_t RHS) {
        LHS -= RHS;
        return LHS;
    }
    friend Iterator operator-(const ptrdiff_t &LHS, Iterator RHS) {
        RHS -= LHS;
        return RHS;
    }
};
}