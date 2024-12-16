
#include <iostream>
#include "LRU_utility.h"
#include "myDoubleLL.h"

int main() {
    
    LRUCache<int> cache;
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.put(4, 40);
    cache.put(5, 50);

    cout << "Original List: ";
    cache.list.printLL();

    int temp = cache.get(9);
    cout << "\nValue at get(3): "<<temp<<endl;
    cout << "\nUpdated List after get(3): ";
    cache.list.printLL();

    cache.put(6, 60);
    cout << "\nUpdated List after put(6,60): ";
    cache.list.printLL();

    return 0;
}




/*

To compile and run the program:

cd CPP_Assessment/02_LRU
g++ -std=c++11 -o a main.cpp
./a



g++ -c myDoubleLL.cpp LRU_utility.cpp main.cpp   # Compile .cpp files to object files
g++ -o a ./myDoubleLL.o ./LRU_utility.o ./main.o   # Link object files to create an executable
g++ -o a *.cpp *.h


*/