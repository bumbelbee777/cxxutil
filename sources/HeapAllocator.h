#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class T = void> class HeapAllocator {
public:
	HeapAllocator(size_t Size = 4096) : Size(Size), Memory(new std::byte[Size]), Offset(0) {
		AddBlock(Memory, Size);
	}

	~HeapAllocator() {
		std::byte *Block = FreeList;
		while(Block) {
			std::byte *NextBlock = *reinterpret_cast<std::byte**>(Block);
			delete[] Block;
			Block = NextBlock;
		}
	}

	T *Allocate(size_t Count = 1) {
		size_t Bytes = Count * sizeof(T);
		std::byte *Result = nullptr;
		if(Bytes <= BlockSize) {
			if(static_cast<size_t>(Offset + Bytes) <=
			    static_cast<size_t>(BlockEnd - Memory)) {
				Result = Memory + Offset;
				Offset += Bytes;
			} else {
				if(FreeList) {
					Result = FreeList;
					FreeList = *reinterpret_cast<std::byte**>(FreeList);
				}
			}
		}
		if(!Result) {
			if(Bytes > BigAllocationThreshold) return BigAllocate(Count);
			size_t NewBlockSize = 	MAX(Bytes, BlockSize);
			std::byte *NewBlock = new std::byte[NewBlockSize];
			AddBlock(NewBlock, NewBlockSize);
			Result = NewBlock;
		}
		return reinterpret_cast<T*>(Result);
	}

	T *AllocateZeroed(size_t Count = 1) {
		T *Result = Allocate(Count);
		if(Result) memset(Result, 0, Count * sizeof(T));
		return Result;
	}

	void Free(T *Pointer) {
		if(Pointer == nullptr) return;
		std::byte *Block = reinterpret_cast<std::byte*>(Pointer);
		if(Block >= Memory && Block < Memory + Size) {
			Offset = Block - Memory;
		} else {
			*reinterpret_cast<std::byte**>(Block) = FreeList;
			FreeList = Block;
		}
	}

private:
	static constexpr size_t BlockSize = 4096;
	static constexpr size_t BigAllocationThreshold = 1048576;

	size_t Size;
	std::byte *Memory;
	size_t Offset;

	std::byte *BlockEnd;
	std::byte *FreeList;

	void AddBlock(std::byte *Block, size_t Size) {
		*reinterpret_cast<std::byte**>(Block) = FreeList;
		FreeList = Block;
		BlockEnd = Block + Size;
	}

	T *BigAllocate(size_t Count) {
		size_t Bytes = Count * sizeof(T);
		size_t NewBlockSize = MAX(Bytes, BlockSize);
		std::byte* NewBlock = new std::byte[NewBlockSize];
		*reinterpret_cast<std::byte**>(NewBlock) = FreeList;
		FreeList = NewBlock;
		return reinterpret_cast<T*>(NewBlock);
	}
};

HeapAllocator Heap;
}
