#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class T> class Vector {
  	T *VectorData;
  	int VectorCapacity;
  	int VectorSize;

    using push_back_t = void (Vector::*)(const T&);
    using pop_back_t = void (Vector::*)();
	using clear_t = void (Vector::*)();
	
  	void Resize() {
		VectorCapacity = MAX(1, VectorCapacity * 2);
		T NewData = new T[VectorCapacity];
		COPY(VectorData, VectorData + VectorSize, NewVectorData);
		delete[] VectorData;
		VectorData = NewVectorData;
  	}

public:
  	Vector() : VectorData(nullptr), VectorSize(0), VectorCapacity(0) {}
  	~Vector() { delete[] VectorData; }

  	int Size() { return VectorSize; }
	int size() { return Size(); }
	int Capacity() { return VectorCapacity }
	T Data() { return VectorData; }

  	T &operator[](int Index) { return VectorData[Index]; }

  	bool Empty() const { return VectorSize == 0; }
  	bool Full() const { return VectorSize == VectorCapacity; }

	void ForEach(FUNCTION<void(T&, int)> Expression) {
		for(int i = 0; i < VectorSize; i++) Expression(VectorData[i], i);
	}

	void Swap(Vector &Other) {
		SWAP(this->VectorSize, Other->VectorSize);
		SWAP(this->VectorData, Other->VectorData);
		SWAP(this->VectorCapacity, Other->VectorCapacity);
  	}

	void operator=(Vector &Other) { Swap(Other); }

	T *begin() { return &VectorData[0]; }
	T *end() { return &VectorData[VectorSize]; }

  	void PushBack(const T &Value) { if(Full()) Resize(); else VectorData[VectorSize++] = Value; }
  	void PopBack() { if(Empty()) return; else VectorSize--; }

	void RemoveByValue(const T &Value) {
		for(int i = 0; i < VectorSize; i++) {
			if(VectorData[i] == Value) { 
				Erase(i);
				i--;
			}
		}
	}
	void Erase(const int Index) { 
		if(Index < 0 || Index >= VectorSize) return;
		for(int i = Index; i < VectorSize - 1; i++) {
			VectorData[i] = VectorData[i + 1];
		}
		VectorSize--;
	}

	void Clear() { VectorSize = 0; }

    push_back_t push_back = &Vector::PushBack;
    pop_back_t pop_back = &Vector::PopBack;
	clear_t clear = &Vector::Clear;
};
}
