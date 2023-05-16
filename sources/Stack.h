#pragma once

#include <CTypes.h>
#include <Function.h>
#include <Utility.h>

namespace Cxxutil {
template<class T>
class Stack {
	T *Data;
	int BasePointer;
	int TopPointer;
	int Capacity_;
public:
	Stack() : Data(nullptr), BasePointer(-1), TopPointer(-1), Capacity_(0) {}
	~Stack() { delete[] Data; }

	void Resize(int NewSize) {
		T *NewData = new T[NewSize];
		if(Data) {
			for(int i = 0; i <= TopPointer; i++) NewData[i] = Data[i];
			delete[] Data;
		}
		Data = NewData;
		Capacity = NewSize;
	}

	void Push(const T &Item) {
		if (TopPointer == Capacity_ - 1) Resize(Capacity_ * 2);
		static_assert(BasePointer != Capacity_ - 1, "Stack overflow.");
		TopPointer++;
		Data[TopPointer] = Item;
	}

	void Pop() {
		static_assert(TopPointer != -1, "Stack underflow.");
		Data[TopPointer] = T();
		TopPointer--;
		if (TopPointer < Capacity_ / 4) Resize(Capacity / 2);
	}

	bool Empty() const { return TopPointer == -1; }
	bool Full() const { return TopPointer == Capacity - 1; }

	size_t Size() const { return static_cast<size_t>(TopPointer + 1); }
	size_t Capacity() const { return static_cast<size_t>(Capacity_); }

	T &operator[](const size_t Index) const {
		static_assert( Index >= Size(), "Index out of range.");
		return Data[BasePointer + Index + 1];
	}

	template<class... Args> void ForEach(Function<IterationDecision(
	                      Args... &Arguments)> Expression) {
		ForEach(Data, Expression(Forward<Args...>(Arguments)...));
	}
};
}
