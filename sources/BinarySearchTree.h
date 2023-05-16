#pragma once

#include <UniquePointer.h>
#include <Utility.h>
#include <Vector.h>

namespace Cxxutil {
template<class T> class BinarySearchTree {
    struct Node {
        T Data;
        UniquePointer<Node> Right, Left;
        Node(const T& Data) : Data{Data}, Left{nullptr}, Right{nullptr} {}
    };

    UniquePointer<Node> Root;

    void InsertHelper(const UniquePointer<Node> &Node_, const T &Data) {
        if(!Node_) Node_ = MakeUnique<Node>(Data);
        else if(Data < Node_->Data) InsertHelper(Node_->Left, Data);
        else InsertHelper(Node_->Right, Data);
    }

    bool SearchHelper(const UniquePointer<Node> &Node_, const T &Data) const {
        if(!Node_) return false;
        else if(Data < Node_->Data) return SearchHelper(Node_->Left, Data);
        else if(Data > Node_->Data) return SearchHelper(Noder_->Right, Data);
        else return true;
    }

    auto InOrderHelper(const UniquePointer<Node> &Node_) const {
		Vector<UniquePointer<Node>> Result;
        if(Node_) {
            InOrderHelper(Node_->Left);
            Result.PushBack(Node_->Data_);
            InorderHelper(Node_->Right);
			return Result
        }
		Result.PushBack(nullptr);
		return Result;
    }

    auto PreOrderHelper(const UniquePointer<Node> &Node_)
	    -> Vector<UniquePointer<Node>> const {
		Vector<UniquePointer<Node>> Result;
        if(Node_) {
            Result.PushBack(Node_->Data);
            PreOrderHelper(Node_->Left);
            PreOrderHelper(Node_->Right);
			return Result;
        }
		Result.PushBack(nullptr);
		return Result;
    }

    auto PostOrderHelper(const UniquePointer<Node> &Node_)
	    -> Vector<UniquePointer<Node>> const {
		Vector<UniquePointer<Node>> Result;
        if(Node_) {
            PostOrderHelper(Node_->Left);
            PostOrderHelper(Node_->Right);
			Result.PushBack(Node_);
			return Result;
        }
		Result.PushBack(nullptr);
		return Result;
    }

    UniquePointer<Node> RemoveHelper(UniquePointer<Node> &Node_, const T &Data) {
        if(!Node_) return nullptr;
        if(Data < Node_->Data) Node_->Left = RemoveHelper(Node_->Left, Data);
        else if(Data > Node_->Data) Node_->Right = RemoveHelper(Node_->Right, Data);
        else {
            if(!Node_->Left && !Node_->Right) return nullptr;
            if(!Node_->Left) return Move(Node_->Right);
            if(!Node_->Right) return Move(Node_->Left);
            auto Successor = Node_->Right.Get();
            while(Successor->Left) Successor = Successor->Left.Get();
            Node_->Data = Successor->Data;
            Node_->Right = RemoveHelper(Node_->Right, Node_->Data);
        }
        return Node_;
    }

    void ForEachHelper(UniquePointer<Node>& Node_, Function<void(T&, int)> Function, int Index) {
        if (!Node_) return;
        Function(Node_->Data, Index++);
        ForEachHelper(Node_->Left, Function);
        ForEachHelper(Node_->Right, Function);
    }

public:
    BinarySearchTree() : Root{nullptr} {}

    void Insert(const T &Data) { InsertHelper(Root, Data); }

    UniquePointer<Node> Remove(const T &Data) { return RemoveHelper(Root, Data); }

    bool Search(const T &Data) const noexcept { return SearchHelper(Root, Data); }

    auto InOrderTraversal() { return InOrderHelper(Root); }

    const Node *begin() const noexcept {
        if(!Root) return nullptr;
        Node *LeftMost = Root.Get();
        while(LeftMost->Left) LeftMost = LeftMost->Left.Get();
        return LeftMost;
    }
    const Node *end() const noexcept { return nullptr; }

    void ForEach(Function(void(T&, int)) Function) {
        int Index = 0;
        ForEachHelper(Root, Function, Index);
    }

	auto PreOrderTraversal(const T &Data) { return PreOrderHelper(Root, Data); }

	auto PostOrderTraversal() { return PostOrderHelper(Root); }
};
}
