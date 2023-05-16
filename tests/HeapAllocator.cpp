#include <All.h>
#include <iostream>
<<<<<<< HEAD

int main(int argc, char **argv) {
	void *MyPointer = Cxxutil::Heap.Allocate(5);
	if(!MyPointer) {
		std::cout << "Could not allocate heap memory for pointer!" << '\n';
		return 1;
	}
	Heap.Free(MyPointer);
	return 0;
}
=======
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
>>>>>>> 23862c99b39aa00b38b870fc6c70444d2c2f0ce9
