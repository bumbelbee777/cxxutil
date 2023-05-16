test:
	g++ tests/Containers.cpp -o containers -Isources/ -std=c++20 -mtune=native -march=native -O2
	g++ tests/HeapAllocator.cpp -o heap -Isources/ -std=c++20 -mtune=native -march=native -O2

run-test:
	time ./containers
	time ./heap
