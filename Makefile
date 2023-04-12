test:
	g++ tests/Test.cpp -o test -Isources/ -std=c++20

run-test:
	time ./test
