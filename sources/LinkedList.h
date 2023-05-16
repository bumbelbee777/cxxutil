#pragma once

#include <CTypes.h>

namespace Cxxutil {
template<class T>
template<class T>
class LinkedList {
	struct Item {
		Item(const T &Value) : Value(Value) {}
		T Value;
		Item *Next;
	};
	Item *Head_;
	Item *Tail_; // New tail pointer
	size_t Size_;
public:
	LinkedList() : Head_(nullptr), Tail_(nullptr), Size_(0) {}
	~LinkedList() { Clear(); }

	void PushFront(const T &Value) {
		auto Node = new Item(Value);
		Node->Next = Head_;
		Head_ = Node;
		if (Size_ == 0) Tail_ = Head_;
		Size_++;
	}

	void PopFront() {
		if(Empty()) return;
		auto Dummy = Head_;
		Head_ = Head_->Next;
		if(Size_ == 1) Tail_ = nullptr;
		delete Dummy;
		Size_--;
	}

	void PushBack(const T &Value) {
		auto Node = new Item(Value);
		Node->Next = nullptr;
		if(Size_ == 0) {
			Head_ = Tail_ = Node;
		} else {
			Tail_->Next = Node;
			Tail_ = Node;
		}
		Size_++;
	}

	void PopBack() {
		if(Empty()) return;
		if(Size_ == 1) {
			delete Head_;
			Head_ = Tail_ = nullptr;
		} else {
			auto Current = Head_;
			while (Current->Next != Tail_) {
				Current = Current->Next;
			}
			delete Tail_;
			Tail_ = Current;
			Tail_->Next = nullptr;
		}
		Size_--;
	}

	bool Empty() const { return Size_ == 0; }
	size_t Size() const { return Size_; }

	const T &Front() const { return Head_->Value; }
	const T &Back() const { return Tail_->Value; }

	void Clear() { while (!Empty()) PopFront(); }

	T& operator[](const size_t Index) const {
		static_assert(Index < Size_, "Index out of range.");
		auto Current = Head_;
		for(size_t i = 0; i < Index; i++) Current = Current->Next;
		return Current->Value;
	}
};
}