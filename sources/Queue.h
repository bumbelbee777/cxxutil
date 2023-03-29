#pragma once

#include <Function.h>

namespace Cxxutil {
template<class T> class Queue {
  	T *Data;
  	int MaximumCapacity;
  	int Items;
  	int Front;
  	int Rear;
  	int Count;

public:
  	T Size() { return Count; }

  	Queue(int Capacity = 1000) : MaximumCapacity(Capacity), Data(new T[Capacity]), Items(0), Front(0), Rear(-1) {}
  	~Queue() { delete[] * Data; }

  	bool Empty() { return (Size() == 0); }
  	bool Full() { return (Size() == MaximumCapacity); }

  	void Dequeue(T Item) {
		if(Empty) return;
		Front = (Front++) % Capacity;
		this->Items--;
  	}
  	void Enqueue(T Item) {
		if(Full) return;
		Rear = (Rear++) % Capacity;
		this->Items++;
  	}

  	auto Peek() { return *Data[Front]; }

	void ForEach(Function<void(T&, int)> Expression) {
		for(int i = 0; i < MaximumCapacity; i++) Expression(Data[i], i);
	}
};
}