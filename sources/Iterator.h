#pragma once

class Iterator {
    int CurrentIndex;
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

    T &operator*() const {
        return *Pointer;
    }
    T *operator->() const {
        return Pointer;
    }

    bool operator==(const Iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};