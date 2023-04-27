#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class Key, class Value> class HashMap {
public:
    using key_type = Key;
    using mapped_type = Value;
    using PAIR<Key, Value> = PAIR<Key, Value>;

private:
    VECTOR<PAIR<Key, Value>> Data;
    FUNCTION<size_t(const Key&)> Hasher;

public:
    explicit HashMap(size_t InitialSize = 8)
        : Data(InitialSize), Hasher(Hash<Key>()) {}

    HashMap(const HashMap&) = delete;
    HashMap &operator=(const HashMap&) = delete;

    void Insert(const PAIR<Key, Value>& Value) {
        size_t Index = FindIndex(Value.First);
        if (Index == Data.size()) {
            Resize(Data.size() * 2);
            Index = FindIndex(Value.First);
        }
        Data[Index] = Value;
    }

    bool Contains(const Key &Key) const {
        return FindIndex(Key) != Data.size();
    }

    const Value &operator[](const Key &Key) const {
        size_t Index = FindIndex(Key);
        if (Index == Data.size()) return NULL;
        return Data[Index].second;
    }

    Value &operator[](const Key &Key) {
        size_t Index = FindIndex(Key);
        if(Index == Data.size()) {
            Resize(Data.size() * 2);
            Index = FindIndex(Key);
        }
        return Data[Index].second;
    }

    void Clear() {
        Data.clear();
        Data.resize(8);
    }

private:
    size_t FindIndex(const Key &Key) const {
        size_t Hash = Hasher(Key);
        size_t Index = Hash % Data.size();
        while(Data[Index].First != Key && Data[Index].First != Key()) Index = (Index + 1) % Data.size();
        return Index;
    }

    void Resize(size_t NewSize) {
        Vector<PAIR<Key, Value>> NewData(NewSize);
        for(const auto &Value : Data) {
            if(Value.First != Key()) {
                size_t Index = FindIndex(Value.first);
                NewData[Index] = Value;
            }
        }
        Data = MOVE(NewData);
    }
};
}
