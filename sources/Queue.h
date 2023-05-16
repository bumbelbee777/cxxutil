#pragma once

#include <Function.h>

namespace Cxxutil {
template<class T> class Queue {
  	T *Data;
  	int Capacity;
  	int Items;
  	int Front;
  	int Rear;
public:
    Queue(int Capacity = 1000) : Capacity(Capacity), Data(new T[Capacity]), Items(0), Front(0), Rear(-1) {}
	Queue(Queue &Other) : Data(Other.Data), Capacity(Other.Capacity), Front(Other.Front), Items(Other.Items), Rear(Other.Rear) {}

    ~Queue() { delete[] Data; }

    bool Empty() const { return Items == 0; }
    bool Full() const { return Items == Capacity; }

    int Size() const { return Items; }

    void Enqueue(const T& Item) {
        if (Full()) return;
        Rear = (Rear + 1) % Capacity;
        Data[Rear] = Item;
        Items++;
    }

    void Dequeue() {
        if(Empty()) return;
        Front = (Front + 1) % Capacity;
        Items--;
    }

    const T &Peek() const {
        if(Empty()) return NULL;
        return Data[Front];
    }

    void Clear() {
        Front = 0;
        Rear = -1;
        Items = 0;
    }

	bool Remove(const T Item) {
		bool Found = false;
		for(int i = Front_; i <= Rear_; i++) {
			if(Data[i] == Item) {
				for (int j = i; j < Rear_; j++) Data[j] = Data[j + 1];
				Rear_--;
				Items--;
				Found = true;
				break;
			}
		}
		return Found;
	}

    void ForEach(Function(void(const T&, int)) Expression) const {
        for(int i = 0; i < Items; i++) {
            int Index = (Front + i) % Capacity;
            Expression(Data[index], Index);
        }
    }
};
}
