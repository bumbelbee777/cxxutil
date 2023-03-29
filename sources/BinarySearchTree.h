#pragma once

#include <memory>
#include <iostream>

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

    void InOrderHelper(const std::unique_ptr<Node>& Node_, std::ostream& OStream) const {
        if(node) {
            InOrderHelper(Node_->Left, OStream);
            OStream << Node->Data_ << " ";
            InorderHelper(Node_->Right, OStream);
        }
    }

public:
    BinarySearchTree() : Root{nullptr} {}

    void Insert(const T &Data) {
        InsertHelper(Root, Data);
    }

    bool Search(const T &Data) const noexcept { 
        return SearchHelper(Root, Data);
    }

    void InOrderTraversal(std::ostream &OStream) {
        InOrderHelper(Root, OStream);
    }

    const Node* begin() const noexcept {
        if(!Root) return nullptr;
        Node* LeftMost = Root.get();
        while(LeftMost->Left) LeftMost = LeftMost->Left.get();
        return LeftMost;
    }

    const Node* end() const noexcept {
        return nullptr;
    }
};
}