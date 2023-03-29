#pragma once

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <Function.h>

namespace Cxxutil {
template<class T, std::size_t size>
class Array {
    T Data_[size];
public:
    Array() { std::memset(Data_, 0, size * sizeof(T)); }
    ~Array() {}

    T &operator[](size_t Index) {
        if (Index >= size) {
            throw std::out_of_range("Array index out of range");
        }
        return Data_[Index];
    }

    const T &operator[](size_t Index) const {
        if (Index >= size) {
            throw std::out_of_range("Array index out of range");
        }
        return Data_[Index];
    }

    Array& operator=(const Array& Other) {
        for (std::size_t i = 0; i < size; i++) {
            this->Data_[i] = Other.Data_[i];
        }
        return *this;
    }

    const T* Data() const {
        return &Data_[0];
    }

    std::size_t Size() const {
        return size;
    }

    const T* begin() const {
        return &Data_[0];
    }

    T* begin() {
        return &Data_[0];
    }

    const T* end() const {
        return &Data_[size];
    }

    T* end() {
        return &Data_[size];
    }

    void ForEach(Function<void(T&, int)> Expression) {
        for(int i = 0; i < size; i++) Expression(Data_[i], i);
    }
};
}