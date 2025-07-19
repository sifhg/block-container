#include <iostream>
#include "Block.hpp"

int main()
{
    auto intBlock = Block<int>::CreateBlock(3);
    std::cout << "Allocated size of Block<int> is: " << intBlock.GetAllocatedSize() << std::endl;
    int* intIndex0 = intBlock.Push(500);
    std::cout << "Pushed int to block" << *intIndex0 << ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
    int* intIndex1 = intBlock.Push(600);
    std::cout << "Pushed int to block" << *intIndex1<< ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
    int* intIndex2 = intBlock.Push(700);
    std::cout << "Pushed int to block" << *intIndex2 << ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
    int* intIndex3 = intBlock.Push(800);
    std::cout << "Pushed int to block" << *intIndex3 << ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
    int* intIndex4 = intBlock.Push(850);
    std::cout << "Pushed int to block" << *intIndex4 << ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
    int* intIndex5 = intBlock.Push(900);
    std::cout << "Pushed int to block" << *intIndex5 << ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n";
    int* intIndex6 = intBlock.Push(950);
    std::cout << "Pushed int to block" << *intIndex6 << ".\n";
    std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
    std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 

    std::cout << "intIndex5's address is " << intIndex5 << ".\n";
    std::cout << "Delete data at intIndex5.\n";
    intBlock.Delete(intIndex5);
    std::cout << "intIndex5's address is now " << intIndex5 << ".\n";

    int* intIndex5b = intBlock.Push(1000);
    std::cout << "intIndex5b's address is " << intIndex5b << ".\n";
    std::cout << "intIndex5's value is " << *intIndex5b << ".\n";

    return 0;
}