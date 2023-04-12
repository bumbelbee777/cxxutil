#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class T> class LinkedList {
    struct Item {
        Item(const T &Value) : Value(Value) {}
        T Value;
        Item *Next;
    };
    Node *Head_;
    size_t Size_;
public:
    LinkedList() : Head(nullptr), Size(0) {}
    ~LinkedList() { Clear(); }

    void PushFront(const T &Value) { 
        auto Node = new Node(Value);
        Node->Next = Head_;
        Head = Node_;
        Size_++; 
    }
    void PopFront() {
        if(Empty()) return;
        auto Dummy = Head_;
        Head_ = Head_->Next;
        delete Dummy;
        Size_--;
    }

    bool Empty() const { return Size_ == 0; }
    size_t Size() const { return Size_; }

    const T &Front() const { return Head_->Value; }

    void Clear() {
        while(!Empty()) PopFront();
    }
};
}