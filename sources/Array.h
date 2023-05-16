#pragma once

#include <TypeInfo.h>
#include <Function.h>
#include <CTypes.h>
#include <random>

namespace Cxxutil {
template<class T, size_t size>
class Array {
    T Data_[size];
public:
    Array() { memset(Data_, 0, size * sizeof(T)); }
    ~Array() {}

    T &operator[](const size_t Index) {
        if (Index >= size) return NULL;
        return Data_[Index];
    }

    const T &operator[](const size_t Index) const {
        if (Index >= size) return NULL;
        return Data_[Index];
    }

    Array& operator=(const Array& Other) {
        for(size_t i = 0; i < size; i++) this->Data_[i] = Other.Data_[i];
        return *this;
    }

    const T* Data() const {
        return &Data_[0];
    }

    size_t Size() const { return size; }

    const T *begin() const { return &Data_[0]; }
    T *begin() { return &Data_[0]; }
    const T *end() const { return &Data_[size]; }
    T *end() { return &Data_[size]; }

	void Shuffle() {
    	std::random_device rd;
    	std::mt19937 gen(rd());
    	for(int i = size - 1; i > 0; i--) {
        	std::uniform_int_distribution<int> dist(0, i);
        	int j = dist(gen);
        	Swap(Data_[i], Data_[j]);
    	}
	}

    void ForEach(Function<void(T&, int)> Expression) { for(int i = 0; i < size; i++) Expression(Data_[i], i); }
};
}
