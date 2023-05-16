#pragma once

#include <Pair.h>
#include <Vector.h>

namespace Cxxutil {

template<class Key, class Value>
class Map {
    Vector<Pair<Key, Value>> Data;
public:
    void Insert(const Pair(Key, Value) &Value) {
        for(auto &Entry : Data) {
            if(Entry.First == Value.First) {
                Entry.Second = Value.Second;
                return;
            }
        }
        Data.PushBack(Value);
    }

    bool Contains(const Key &Key_) {
        for(const auto &Entry : Data) if(Entry.First == Key_) return true;
        return false;
    }

    const Value &operator[](const Key &Key_) const {
        for(const auto &Entry : Data) if(Entry.First == Key_) return Entry.Second;
    }

    Value &operator[](const Key &Key_) {
        for(auto &Entry : Data) if(Entry.First == Key_) return Entry.Second;
        Data.PushBack(Pair<Key, Value>(Key_, Value()));
        return Data.Back().Second;
    }

    void Clear() {
        Data.Clear();
    }
};
}
