#include <All.h>
#include <iostream>

int main(int argc, char **argv) {
	void *MyPointer = Cxxutil::Heap.Allocate(5);
	if(!MyPointer) {
		std::cout << "Could not allocate heap memory for pointer!" << '\n';
		return 1;
	}
	Heap.Free(MyPointer);
	return 0;
}