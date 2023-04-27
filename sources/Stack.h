#pragma once

#include <Std.h>

namespace Cxxutil {
template<class T> class Stack {
	T *Data;
	int BasePointer;
	int TopPointer;
	int Capacity;
public:
	Stack() : Data(new T[Capacity]), BasePointer(0), TopPointer(sizeof(Data)), Capacity(0) {}

	void Push(const T &Item) {
		Data[TopPointer + 1] = Item;
		TopPointer++;
	}
	void Pop() {
		Data[TopPointer] = nullptr;
		TopPointer--;
	}

	bool Empty() { return !Capacity; }
	bool Full() { return TopPointer == Capacity - 1; }

	size_t Size() const { return static_cast<size_t>(TopPointer - BasePointer + 1); }

    size_t Capacity() const { return static_cast<size_t>(Capacity); }
};
}
