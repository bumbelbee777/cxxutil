#pragma once

#include <Cxxutil.h>

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

    bool IsEmpty() const { return Items == 0; }

    bool IsFull() const { return Items == Capacity; }

    int GetSize() const { return Items; }

    void Enqueue(const T& Item) {
        if (IsFull()) return;
        Rear = (Rear + 1) % Capacity;
        Data[Rear] = Item;
        Items++;
    }

    T Dequeue() {
        if (IsEmpty()) return NULL;
        T item = Data[Front];
        Front = (Front + 1) % Capacity;
        Items--;
        return item;
    }

    const T &Peek() const {
        if (IsEmpty()) return NULL;
        return Data[Front];
    }

    void Clear() {
        Front = 0;
        Rear = -1;
        Items = 0;
    }

    void ForEach(FUNCTION(void(const T&, int)) Expression) const {
        for(int i = 0; i < Items; i++) {
            int Index = (Front + i) % Capacity;
            Expression(Data[index], Index);
        }
    }
};
}
