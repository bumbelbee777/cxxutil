#pragma once

#include <Function.h>
#include <algorithm>

template<class T> class Vector {
  	T *VectorData;
  	int VectorCapacity;
  	int VectorSize;

  	void Resize() {
		VectorCapacity = std::max(1, VectorCapacity * 2);
		T NewData = new T[VectorCapacity];
		std::copy(VectorData, VectorData + VectorSize, NewVectorData);
		delete[] VectorData;
		VectorData = NewVectorData;
  	}

public:
  	Vector() : VectorData(nullptr), VectorSize(0), VectorCapacity(0) {}
  	~Vector() { delete[] VectorData; }

  	int Size() { return VectorSize; }
	int Capacity() { return VectorCapacity }
	T Data() { return VectorData; }

  	T &operator[](int Index) { return VectorData[Index]; }

  	bool Empty() { return VectorSize == 0; }
  	bool Full() { return VectorSize == VectorCapacity; }

	void ForEach(Function<void(T&, int)> Expression) {
		for(int i = 0; i < VectorSize; i++) 
			Expression(VectorData[i], i);
	}

	void Swap(Vector &Other) {
		VectorSize = Other.Size();
		VectorCapacity = Other.Capacity();
		VectorData = Other.VectorData;
  	}

	void operator=(Vector &Other) { Swap(Other); }

	T begin() { return VectorData[0]; }
	T end() { return VectorData[VectorSize]; }

  	void PushBack(const T &Value) { if(Full()) return; else VectorData[VectorSize++] = Value; }
  	void PopBack() { if(Empty()) return; else VectorSize--; }
};