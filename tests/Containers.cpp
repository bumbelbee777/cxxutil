#include <iostream>
#include <All.h>

using namespace Cxxutil;

int main(int argc, char **argv) {
  	BinarySearchTree<int> bst;
  	bst.Insert(5);
  	bst.Insert(2);
  	bst.Insert(8);
  	bst.Insert(1);
  	bst.Insert(4);
 	bst.Insert(7);
  	bst.Insert(9);

  	std::cout << "Binary Search Tree:\n";
  	bst.ForEach([](int &value, int index) {
    	std::cout << index << ": " << value << '\n';
  	});

  	std::cout << "Inorder traversal:\n";
  	auto Result = bst.InOrderTraversal();
  	std::cout << "\n";

  	std::cout << "Preorder traversal:\n";
  	auto Result = bst.PreOrderTraversal();
  	std::cout << "\n";

  	std::cout << "Postorder traversal:\n";
  	auto Result = bst.PostOrderTraversal();
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
	std::cout << "4th item in linked list using [] operator: " << ll[4] << '\n';

    Queue<int> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    queue.Enqueue(5);

    std::cout << "Queue:\n";
	queue.ForEach([](int &Item, int Index) {
		std::cout << "Item: " << Item << '\n';
		queue.Dequeue();
	});
  	return 0;
}
