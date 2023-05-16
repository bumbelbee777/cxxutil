#pragma once

#include <Utility.h>

namespace Cxxutil {
template<class T = void> class HeapAllocator {
public:
	HeapAllocator(size_t Size = 4096) : Size(Size), Memory(new Byte[Size]), Offset(0), FreeList(nullptr) {
		AddBlock(Memory, Size);
	}

	~HeapAllocator() {
		Byte *Block = FreeList;
		while(Block) {
			Byte *NextBlock = *reinterpret_cast<Byte**>(Block);
			delete[] Block;
			Block = NextBlock;
		}
		delete[] Memory;
	}

	T *Allocate(size_t Count = 1) {
		size_t Bytes = Count * sizeof(T);
		if(Bytes <= SmallThreshold) {
			return SmallAllocate(Bytes);
		} else if(Bytes <= MediumThreshold) {
			return MediumAllocate(Bytes);
		} else return BigAllocate(Bytes);
	}

	T *AllocateZeroed(size_t Count = 1) {
		T *Result = Allocate(Count);
		if(Result) memset(Result, 0, Count * sizeof(T));
		return Result;
	}

	void Free(T *Pointer) {
		if(!Pointer) return;
		Byte *Block = reinterpret_cast<Byte*>(Pointer);
		if(Block >= Memory && Block < Memory + Size) {
			Offset = Block - Memory;
		} else FreeFromList(Block);
	}

private:
	static const size_t SmallThreshold = 256;
	static const size_t MediumThreshold = 65536;
	static constexpr size_t BlockSize = 4096;
	static constexpr size_t BigThreshold = 1048576;

	size_t Size;
	Byte* Memory;
	size_t Offset;
	Byte* FreeList;

	Byte *BlockEnd;
	Byte *SmallFreeList;
	Byte *MediumFreeList;

	T *SmallAllocate(size_t Bytes) {
		if(SmallFreeList) {
			Byte *Result = SmallFreeList;
			SmallFreeList = *reinterpret_cast<Byte**>(SmallFreeList);
			return reinterpret_cast<T*>(Result);
		}
		if(static_cast<size_t>(Offset + Bytes) <= static_cast<size_t>(BlockEnd - Memory)) {
			Byte* Result = Memory + Offset;
			Offset += Bytes;
			return reinterpret_cast<T*>(Result);
		}
		return BigAllocate(Bytes);
	}

	T *MediumAllocate(size_t Bytes) {
		if(MediumFreeList) {
			Byte *Result = MediumFreeList;
			MediumFreeList = *reinterpret_cast<Byte**>(MediumFreeList);
			return reinterpret_cast<T*>(Result);
		}
		if(static_cast<size_t>(Offset + Bytes) <= static_cast<size_t>(BlockEnd - Memory)) {
			Byte* Result = Memory + Offset;
			Offset += Bytes;
			return reinterpret_cast<T*>(Result);
		}
		return BigAllocate(Bytes);
	}

	T *BigAllocate(size_t Bytes) {
		if(Bytes > BigThreshold) return reinterpret_cast<T*>(new Byte[Bytes]);
		if(Byte *Block = reinterpret_cast<Byte*>(FreeList)) {
			FreeList = *reinterpret_cast<Byte**>(Block);
			return reinterpret_cast<T*>(Block);
		}
		if(Offset + Bytes > Size) AddBlock(new Byte[BlockSize], BlockSize);
		Byte *Result = Memory + Offset;
		Offset += Bytes;
		return reinterpret_cast<T*>(Result);
	}
	
	void AddBlock(Byte *Block, size_t BlockSize) {
		*reinterpret_cast<Byte**>(Block) = FreeList;
		FreeList = Block;
		BlockEnd = Block + BlockSize;
	}

	void FreeFromList(Byte *Block) {
		if(!Block) return;
		if(Block >= Memory && Block < Memory + Size) return;
		*reinterpret_cast<Byte**>(Block) = FreeList;
		FreeList = Block;
	}
};

HeapAllocator Heap;
}
