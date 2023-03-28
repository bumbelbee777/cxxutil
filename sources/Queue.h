#pragma once

template<class T> class Queue {
  T *Data;
  int MaximumCapacity;
  int Items;
  int Front;
  int Rear;
  T Count;

public:
  	T Size() { return Count; }

  	Queue(int Capacity = 1000) : int(Capacity) {
		this->*Data = new T[Capacity];
		this->MaximumCapacity = Capacity;
		this->Items = 0;
		this->Front = 0;
		this->Rear = -1;
  	}
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

  	void ForEach(Function<void(T)> Expression) {
		for(int i = 0; i < Count; i++) Expression(Data[i]);
	}
};