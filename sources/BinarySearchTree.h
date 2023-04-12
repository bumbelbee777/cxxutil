#pragma once

#include <memory>
#include <iostream>
#include <Cxxutil.h>

namespace Cxxutil {
template<class T> class BinarySearchTree {
    struct Node {
        T Data;
        std::unique_ptr<Node> Right, Left;
        Node(const T& Data) : Data{Data}, Left{nullptr}, Right{nullptr} {}
    };

    std::unique_ptr<Node> Root;

    void InsertHelper(const std::unique_ptr<Node> &Node_, const T &Data) {
        if(!Node_) Node_ = std::make_unique<Node>(Data);
        else if(Data < Node_->Data) InsertHelper(Node_->Left, Data);
        else InsertHelper(Node_->Right, Data);
    }

    bool SearchHelper(const std::unique_ptr<Node> &Node_, const T &Data) const {
        if(!Node_) return false;
        else if(Data < Node_->Data) return SearchHelper(Node_->Left, Data);
        else if(Data > Node_->Data) return SearchHelper(Noder_->Right, Data);
        else return true;
    }

    void InOrderHelper(const std::unique_ptr<Node> &Node_, std::ostream &OStream) const {
        if(node) {
            InOrderHelper(Node_->Left, OStream);
            OStream << Node->Data_ << " ";
            InorderHelper(Node_->Right, OStream);
        }
    }

    void PreOrderHelper(const std::unique_ptr<Node> &Node_, std::ostream &OStream) const {
        if(node) {
            OStream << Node->Data_ << " ";
            PreOrderHelper(Node_->Left, OStream);
            PreOrderHelper(Node_->Right, OStream);
        }
    }

    void PostOrderHelper(const std::unique_ptr<Node> &Node_, std::ostream &OStream) const {
        if(node) {
            PostOrderHelper(Node_->Left, OStream);
            PostOrderHelper(Node_->Right, OStream);
            OStream << Node->Data_ << " ";
        }
    }

    std::unique_ptr<Node> RemoveHelper(std::unique_ptr<Node> &Node_, const T &Data) {
        if(!Node_) return nullptr;
        if(Data < Node_->Data) Node_->Left = RemoveHelper(Node_->Left, Data);
        else if(Data > Node_->Data) Node_->Right = RemoveHelper(Node_->Right, Data);
        else {
            if(!Node_->Left && !Node_->Right) return nullptr;
            if(!Node_->Left) return std::move(Node_->Right);
            if(!Node_->Right) return std::move(Node_->Left);
            auto Successor = Node_->Right.get();
            while(Successor->Left) Successor = Successor->Left.get();
            Node_->Data = Successor->Data;
            Node_->Right = RemoveHelper(Node_->Right, Node_->Data);
        }
        return Node_;
    }

    void ForEachHelper(std::unique_ptr<Node>& Node_, FUNCTION(void(T&, int)) Function, int Index) {
        if (!Node_) return;
        Function(Node_->Data, Index++);
        ForEachHelper(Node_->Left, Function);
        ForEachHelper(Node_->Right, Function);
    }

public:
    BinarySearchTree() : Root{nullptr} {}

    void Insert(const T &Data) { InsertHelper(Root, Data); }

    std::unique_ptr<Node> Remove(const T &Data) { return RemoveHelper(Root, Data); }

    bool Search(const T &Data) const noexcept { return SearchHelper(Root, Data); }

    void InOrderTraversal(std::ostream &OStream) { InOrderHelper(Root, OStream); }

    const Node* begin() const noexcept {
        if(!Root) return nullptr;
        Node* LeftMost = Root.get();
        while(LeftMost->Left) LeftMost = LeftMost->Left.get();
        return LeftMost;
    }

    const Node* end() const noexcept { return nullptr; }

    void ForEach(FUNCTION(void(T&, int)) Function) {
        int Index = 0;
        ForEachHelper(Root, Function, Index);
    }
};
}