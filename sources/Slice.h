#pragma once

#include <Std.h>

namespace Cxxutil {
template<class T> class Slice {
    T *Data_;
    size_t Size_;
public:
    Slice(T *Data, size_t Size) : Data_(Data), Size_(Size) {}

    T &operator[](const size_t Index) { return Data_[Index]; }
    const T &operator[](const size_t Index) const { return Data_[Index]; }

    T *begin() const { return Data_; }

    T *end() const { return Data_ + Size_; }

    size_t Size() const { return Size_; }

    Slice<T> SubSlice(const size_t Offset, const size_t Count) const {
        if(Offset + Count > Size_) Count = Size_ - Offset;
        return Slice<T>(Data_ + Offset, Count);
    }
    Slice<T> SubSlice(const size_t Offset) const {
        if(Offset > Size_) Offset = size_;
        return Slice<T>(Data_ + Offset, Size_ - Offset);
    }

    T *Data() const { return Data_; }

    bool Empty() const { return !Size_; }
};

template<class T> class ConstSlice {
    const T *Data_;
    size_t Size_;
public:
    ConstSlice(const T *Data, size_t Size) : Data_(Data), Size_(Size) {}

    const T &operator[](size_t Index) const { return Data_[Index]; }

    ConstSlice<T> SubSlice(const size_t Offset, const size_t Count) const {
        if(Offset + Count > Size_) Count = Size_ - Offset;
        return ConstSlice<T>(Data_ + Offset, Count);
    }
    ConstSlice<T> SubSlice(const size_t Offset) const {
        if(Offset > Size_) Offset = Size_;
        return ConstSlice<T>(Data_ + Offset, Size_ - Offset);
    }

    const T *begin() const { return Data_; }
    const T *end() const { return Data_ + Size_; }

    size_t Size() const { return Size_; }
};
}  // namespace Cxxutil
