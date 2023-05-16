# Cxxutil.

A lightweight and freestanding C++20 library implementing various STL containers, allocators and other data structures such as:
- Vectors (`Vector<T>`).
- Arrays (`Array<T>`).
- Stacks (`Stack<T>`).
- Linked lists (`LinkedList<T>`).
- Binary search tree (`BinarySearchTree<T>`).
- Functions (`Function<T>`).
- Random access iterator (`Iterator<T>`).
- Optional types (`Optional<T>`).
- Mutable and non-mutable strings (`String<T>` and `StringView<T>` respectively).
- Queues (`Queue<T>`).
- Heap allocator (`HeapAllocator<T>`).
- Exceptions (`Exception`, `ExceptionPointer`).
- Smart pointers like boxes, unique and shared pointers (`Box<T>`, `UniquePointer<T>` and `SharedPointer<T>` respectively).
- Maps and hashmaps (`Map<T, U>` and `Hashmap<T, U>` respectively).
- Regular expressions (`Regex`).
- Slices, both mutable and immutable (`Slice<T>` and `ConstSlice<T>` respectively).
- Graphs (`Graph<T>`).
- Spinlocks and mutexes (`Spinlock` and `Mutex<T>` respectively).
- FNV-1a algorithm and djb2 hashing algorithm for strings (`Hash<T>` and `Hash<String>` respectively).
- Pairs and tuples (`Pair<T, U>` and `Tuple<T...>` respectively).
- C++20 string formatting and three-way comparison support.

And more!

**Keep in mind it's still a work in progress and many features are incomplete and/or won't work as intended.**

# Example

```cxx
#include <iostream>
#include <All.h>

using namespace Cxxutil;

int main(int argv, char **argv) {
  	BinarySearchTree<int> bst;
  	bst.Insert(5);
  	bst.Insert(2);
  	bst.Insert(8);
  	bst.Insert(1);
  	bst.Insert(4);
 	bst.Insert(7);
  	bst.Insert(9);

  	std::cout << "Binary Search Tree:\n";
  	bst.ForEach([](int& value, int index) {
    	    std::cout << index << ": " << value << '\n';
  	});

  	std::cout << "Inorder traversal:\n";
  	bst.InOrderTraversal(std::cout);
  	std::cout << "\n";

  	std::cout << "Preorder traversal:\n";
  	bst.PreOrderTraversal(std::cout);
  	std::cout << "\n";

  	std::cout << "Postorder traversal:\n";
  	bst.PostOrderTraversal(std::cout);
  	std::cout << "\n";

  	std::cout << "Searching for value 7: " << std::boolalpha << bst.Search(7) << '\n';
  	std::cout << "Searching for value 3: " << std::boolalpha << bst.Search(3) << '\n';

  	bst.Remove(2);
  	std::cout << "After removing value 2:\n";
  	bst.ForEach([](int& Value, int Index) {
    	    std::cout << index << ": " << value << '\n';
  	});

  	LinkedList<int> ll;
  	ll.Append(1);
  	ll.Append(2);
  	ll.Append(3);
  	ll.Append(4);
  	ll.Append(5);

        Queue<int> queue;
        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);
        queue.Enqueue(4);
        queue.Enqueue(5);

        std::cout << "Queue:\n";
        while(!queue.IsEmpty()) {
            std::cout << queue.Front() << '\n';
            queue.Dequeue();
        }

	Stack<int> MyStack;
	Stack.Push(1);
	Stack.Push(2);
	Stack.Push(3);
	Stack.Push(4);
	Stack.Push(5);
	MyStack.ForEach([&](int &Item, int Index) {
		std::cout << Item << '\n';
	});
  	return 0;
}
```
