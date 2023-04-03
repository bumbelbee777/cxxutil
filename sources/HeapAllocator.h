#pragma once

namespace Cxxutil {
template<class T = void, size_t Size = 4096>
class HeapAllocator {
public:
HeapAllocator() : Memory(static_cast<std::byte*>(Size)) { }

~HeapAllocator() { delete Memory; }

T *Allocate(size_t Count) {
    size_t Bytes = Count * sizeof(T);
    if(Offset + Bytes > Size) {
        return nullptr;
	}
    T *Result = reinterpret_cast<T*>(Memory + Offset);
    Offset += Bytes;
    return Result;
}

void Free(T *Pointer, size_t Count) {
    size_t Bytes = Count * sizeof(T);
    memset(Pointer, 0, Bytes);
    if(Offset == Bytes) Offset = 0;
    else Offset -= Bytes;
}

private:
    std::byte *Memory;
    size_t Offset = 0;
};

HeapAllocator Heap;
}