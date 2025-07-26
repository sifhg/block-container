#include <iostream>
#include "../Block.hpp"
#include "../BlockMap.hpp"
#include "TestKit-pp/Test.hpp"
#include "BlockTest.hpp"

struct positionComponent
{
    int x;
    int y;
    int z;
};
int blockTester();
int blockContainerTester();

int main()
{
  BlockTest::GetTest();
    // Test blockTester("Block tester");
    // blockTester
    //   .AddFeature("CreateBlock")
    //   .AddFeature("Push")
    //   .AddFeature("GetAllocatedSize")
    //   .AddFeature("GetSize")
    //   .AddFeature("Delete");
    
    // Test blockMapTester("Block Map tester");
    // blockTester();
    // blockContainerTester();
    return 0;
}


// int blockTester()
// {
//     auto intBlock = Block<int>::CreateBlock(3);
//     std::cout << "Allocated size of Block<int> is: " << intBlock.GetAllocatedSize() << std::endl;
//     std::cout << "Size of intBlock in memory is " << sizeof(intBlock) << ".\n";
//     int* intIndex0 = intBlock.Push(500);
//     std::cout << "Pushed int to block" << *intIndex0 << ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
//     int* intIndex1 = intBlock.Push(600);
//     std::cout << "Pushed int to block" << *intIndex1<< ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
//     int* intIndex2 = intBlock.Push(700);
//     std::cout << "Pushed int to block" << *intIndex2 << ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
//     int* intIndex3 = intBlock.Push(800);
//     std::cout << "Pushed int to block" << *intIndex3 << ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
//     int* intIndex4 = intBlock.Push(850);
//     std::cout << "Pushed int to block" << *intIndex4 << ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 
//     int* intIndex5 = intBlock.Push(900);
//     std::cout << "Pushed int to block" << *intIndex5 << ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n";
//     int* intIndex6 = intBlock.Push(950);
//     std::cout << "Pushed int to block" << *intIndex6 << ".\n";
//     std::cout << "Block size is: " << intBlock.GetSize() << ".\n";
//     std::cout << "Block allocates " << intBlock.GetAllocatedSize() << ".\n\n"; 

//     std::cout << "intIndex5's address is " << intIndex5 << ".\n";
//     std::cout << "Size of intBlock in memory is " << sizeof(intBlock) << ".\n";
//     std::cout << "Delete data at intIndex5.\n";
//     intBlock.Delete(intIndex5);
//     std::cout << "intIndex5's address is now " << intIndex5 << ".\n";

//     int* intIndex5b = intBlock.Push(1000);
//     std::cout << "intIndex5b's address is " << intIndex5b << ".\n";
//     std::cout << "intIndex5's value is " << *intIndex5b << ".\n";
//     std::cout << "Size of intBlock in memory is " << sizeof(intBlock) << ".\n";

//     std::cout << "sizeof(Block<int>): " << sizeof(Block<int>) << ".\n";
//     std::cout << "sizeof(Block<float>): " << sizeof(Block<float>) << ".\n";
//     std::cout << "sizeof(Block<double>): " << sizeof(Block<double>) << ".\n";
//     std::cout << "sizeof(Block<char>): " << sizeof(Block<char>) << ".\n";
//     std::cout << "sizeof(Block<std::string>): " << sizeof(Block<std::string>) << ".\n";
//     std::cout << "sizeof(Block<positionComponent>): " << sizeof(Block<positionComponent>) << ".\n";
//     return 0;
// }

// int blockContainerTester()
// {
//     BlockMap aBlockMap;
//     aBlockMap.TryAdd<float>(2);
//     std::shared_ptr<Block<float>> aFloatBlock = aBlockMap.Get<float>();
//     std::cout << "Address of float Block is: " << aFloatBlock << ".\n";
//     std::cout << "Allocated size for float Block is: " << aFloatBlock->GetAllocatedSize() << "\n";
//     std::cout << "Size of float Block is: " << aFloatBlock->GetSize() << "\n";
//     float* floatIndex0 = aFloatBlock->Push(2.5);
//     std::cout << "Address of floatIndex0: " << floatIndex0 << ".\n";
//     std::cout << "Value of floatIndex0: " << *floatIndex0 << ".\n";
//     std::cout << "Allocated size for float Block is: " << aFloatBlock->GetAllocatedSize() << "\n";
//     std::cout << "Size of float Block is: " << aFloatBlock->GetSize() << "\n";
//     aFloatBlock->Delete(floatIndex0);
//     std::cout << "Address of floatIndex0: " << floatIndex0 << ".\n";
//     float* floatIndex0b = aFloatBlock->Push(5.2);
//     std::cout << "Address of floatIndex0b: " << floatIndex0b << ".\n";
//     std::cout << "Value of floatIndex0b: " << *floatIndex0b << ".\n";
//     std::cout << "Allocated size for float Block is: " << aFloatBlock->GetAllocatedSize() << "\n";
//     std::cout << "Size of float Block is: " << aFloatBlock->GetSize() << "\n";
//     std::cout << "\n";
//     for (float value = 1.1; value < 30 ; value += 1.0)
//     {
//       aFloatBlock->Push(value);
//       std::cout << "Allocated size for float Block is: " << aFloatBlock->GetAllocatedSize() << "\n";
//       std::cout << "Size of float Block is: " << aFloatBlock->GetSize() << "\n";
//     }
//     std::cout << "Number of owners of floatBlock: " << aFloatBlock.use_count() << ".\n";
//     std::cout << aBlockMap.Delete<float>() << "\n";
//     std::cout << "Number of owners of floatBlock: " << aFloatBlock.use_count() << ".\n";
//     aBlockMap.Get<std::string>();
//     return 0;
// }