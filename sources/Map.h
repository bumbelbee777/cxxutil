#pragma once

#include <Cxxutil.h>

namespace Cxxutil {

template<class Key, class Value>
class Map {
    VECTOR(PAIR(Key, Value)) Data;
public:
    void Insert(const PAIR(Key, Value) &Value) {
        for(auto &Entry : Data) {
            if(Entry.First == Value.First) {
                Entry.Second = Value.Second;
                return;
            }
        }
        Data.push_back(Value);
    }

    bool Contains(const Key &Key_) {
        for(const auto &Entry : Data) {
            if(Entry.First == Key_) {
                return true;
            }
        }
        return false;
    }

    const Value &operator[](const Key &Key_) const {
        for(const auto &Entry : Data) {
            if(Entry.First == Key_) {
                return Entry.Second;
            }
        }
    }

    Value &operator[](const Key &Key_) {
        for(auto &Entry : Data) {
            if(Entry.First == Key_) {
                return Entry.Second;
            }
        }
        Data.push_back(PAIR(Key, Value)(Key_, Value()));
        return Data.back().Second;
    }

    void Clear() {
        Data.clear();
    }
};
}
