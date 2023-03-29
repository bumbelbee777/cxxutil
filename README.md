# Cxxutil.

A lightweight C++20 library implementing various STL containers and other data structures such as:
- Vectors (`Vector<T>`).
- Arrays (`Array<t>`).
- Binary search tree (`BinarySearchTree<T>`).
- Functions (`Function<T>`).
- Iterators (`Iterator<T>`).
- Optional types (`Optional<T>`).
- Mutable and non-mutable strings (`String<T>` and `StringView<T>` respectively).
- Queues (`Queue<T>`).

# Example

```cxx
#include <All.h>
#include <iostream>

using namespace Cxxutil;

int main(int argc, char **argv) {
    Array<int, 5> MyArray = {1, 2, 3, 4, 5};
    std::cout << "Size of array is: " << MyArray.Size();
    MyArrat.ForEach([](int &Item, int Index) {
        std::cout << "Item: " << Item << " at " << "Index: " << Index << '\n';
    });
    Vector<int> MyVector;
    MyVector.PushBack(1);
    MyVector.PushBack(2);
    MyVector.PushBack(3);
    MyVector.ForEach([](int &Item, int Index) {
        std::cout << "Item: " << Item << " at " << "Index: " << Index << '\n';
    });
    return 0;
}
```
