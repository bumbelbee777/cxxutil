#include <All.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
	void *MyPointer = Heap.Allocate(100);
	assert(MyPointer, "Heap.Allocate() failed!");
	Heap.Free(MyPointer);
	std::cout << "Freed MyPointer." << '\n';
	void *MyPointer2 = Heap.AllocateZeroed(200);
	assert(MyPointer2, "Heap.AllocateZeroed() failed!");
	MyPointer2 = Heap.ReAllocate(300);
	assert(MyPointer2, "Heap.ReAllocate() failed!");
	Heap.Free(MyPointer2);
	std::cout << "All tests passed successfully!" << '\n';
	return 0;
}
