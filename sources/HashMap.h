#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class Key, class Value> class HashMap {
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = PAIR<Key, Value>;

private:
    VECTOR<value_type> Data;
    FUNCTION<size_t(const Key&)> Hasher;

public:
    explicit HashMap(size_t InitialSize = 8)
        : Data(InitialSize), Hasher(Hash<Key>()) {}

    HashMap(const HashMap&) = delete;
    HashMap &operator=(const HashMap&) = delete;

    void Insert(const value_type& Value) {
        size_t Index = FindIndex(Value.First);
        if (Index == Data.size()) {
            Resize(Data.size() * 2);
            Index = FindIndex(Value.First);
        }
        Data[Index] = Value;
    }

    bool Contains(const key_type& Key) const {
        return FindIndex(Key) != Data.size();
    }

    const Value &operator[](const key_type& Key) const {
        size_t Index = FindIndex(Key);
        if (Index == Data.size()) {
            throw std::out_of_range("Key not found");
        }
        return Data[Index].second;
    }

    Value &operator[](const key_type& Key) {
        size_t Index = FindIndex(Key);
        if (Index == Data.size()) {
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
    size_t FindIndex(const key_type& Key) const {
        size_t Hash = Hasher(Key);
        size_t Index = Hash % Data.size();
        while(Data[Index].First != Key && Data[Index].First != key_type()) Index = (Index + 1) % Data.size();
        return Index;
    }

    void Resize(size_t NewSize) {
        Vector<value_type> NewData(NewSize);
        for(const auto& Value : Data) {
            if(Value.First != key_type()) {
                size_t Index = FindIndex(Value.first);
                NewData[Index] = Value;
            }
        }
        Data = MOVE(NewData);
    }
};
}
