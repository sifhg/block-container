#include "../Block.hpp"
#include "TestKit-pp/Test.hpp"
#include "BlockTest.hpp"
#include <memory>
#include <iostream>

std::shared_ptr<Test> BlockTest::GetTest()
{
  const auto testPtr = std::make_shared<Test>("BlockTest");
  testPtr->AddFeature("CreateBlock")
    .AddFeature("Push")
    .AddFeature("GetAllocatedSize")
    .AddFeature("GetSize")
    .AddFeature("Delete")
    .AddFeature("contiguousness");

  testPtr->AddFeatureTest(
    "Create a char block allocating 0 elements and verifie that it allocates 0 elements",
    {"CreateBlock", "GetAllocatedSize"},
    []{
      auto charBlock = Block<char>::CreateBlock(0);
      if (charBlock.GetAllocatedSize() != 0)
      {
        throw std::runtime_error("Allocated size is not 256");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Create an empty int block without arguments and verifies that it allocated 256 elements",
    {"CreateBlock", "GetAllocatedSize", "GetSize"},
    []{
      auto intBlock = Block<int>::CreateBlock();
      if (intBlock.GetAllocatedSize() != 256)
      {
        throw std::runtime_error("Allocated size is not 256");
      }
      if (intBlock.GetSize() != 0)
      {
        throw std::runtime_error("Block is not empty");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Create an empty int block that allocates 2 elements",
    {"CreateBlock", "GetAllocatedSize", "GetSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      if (intBlock.GetAllocatedSize() != 2)
      {
        throw std::runtime_error("Allocated size is not 2");
      }
        if (intBlock.GetSize() != 0)
      {
        throw std::runtime_error("Block is not empty");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Attempt to create a Block that allocates 0 elements",
    {"CreateBlock"},
    []{
      auto intBlock = Block<int>::CreateBlock(0);
    }
  );
  testPtr->AddFeatureTest(
    "Attempt to create an int Block that allocates -1 elements",
    {"CreateBlock"},
    []{
      try {
        auto intBlock = Block<int>::CreateBlock(-1);
      } catch (...) {
        std::cout << "/nEntering catch\n";
        return;
      }
      throw std::runtime_error("Block::CreateBlock with argument -1 threw no error.");
    }
  );
  testPtr->AddFeatureTest(
    "Attempt to create a double Block that allocates -256 elements",
    {"CreateBlock"},
    []{
      try {
        auto intBlock = Block<double>::CreateBlock(-256); 
      }
      catch (...) {
        return;
      }
      throw std::runtime_error("Block::CreateBlock with argument -256 threw no error.");
    }
  );
  testPtr->AddFeatureTest(
    "Attempt to create a char Block that allocates INT_MIN elements",
    {"CreateBlock"},
    []{
      try {
        auto intBlock = Block<char>::CreateBlock(INT_MIN); 
      }
      catch (...) {
        return;
      }
      throw std::runtime_error("Block::CreateBlock with argument INT_MIN threw no error.");
    }
  );
  testPtr->AddFeatureTest(
    "Attempt to create a double Block that allocates INT_MAX elements",
    {"CreateBlock"},
    []{
      try {
        auto intBlock = Block<double>::CreateBlock(INT_MAX); 
      }
      catch (...) {
        std::cout << "Could not create double Block for " << INT_MAX << " elements.\n";
        return;
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that pushing to a Block of size 0 throws an error",
    {"CreateBlock", "Push"},
    []{
      auto intBlock = Block<int>::CreateBlock(0);
      try {
        int* integer = intBlock.Push(42);
      } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return;
      }
      throw std::runtime_error("Block::Push did not throw an error when pushing to a Block of size 0.");
    }
  );
  testPtr->AddFeatureTest(
    "Verify that CreateBlock<int>(0) returns a Block with size 0",
    {"CreateBlock", "GetSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(0);
      if (intBlock.GetSize() != 0) {
        throw std::runtime_error("Block size is not 0");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that CreateBlock<double>() returns a Block with size 0",
    {"CreateBlock", "GetSize"},
    []{
      auto doubleBlock = Block<double>::CreateBlock();
      if (doubleBlock.GetSize() != 0) {
        throw std::runtime_error("Block size is not 0");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that CreateBlock<char>(10) returns a Block with size 0",
    {"CreateBlock", "GetSize"},
    []{
      auto charBlock = Block<char>::CreateBlock(10);
      if (charBlock.GetSize() != 0) {
        throw std::runtime_error("Block size is not 0");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that AddContainer allocates 256 elements if the Block has size 0",
    {"CreateBlock", "AddContainer", "GetAllocatedSize"},
    []{
      auto stringBlock = Block<std::string>::CreateBlock(0);
      stringBlock.AddContainer();
      if (stringBlock.GetAllocatedSize() != 256) {
        throw std::runtime_error("Allocated size is not 256 after AddContainer");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that CreateBlock<float>(0), AddContainer(1), and Push(5.5) work correctly",
    {"CreateBlock", "AddContainer", "Push"},
    []{
      auto floatBlock = Block<float>::CreateBlock(0);
      floatBlock.AddContainer(1);
      float* floatPtr = floatBlock.Push(5.5f);
      if (*floatPtr != 5.5f) {
        throw std::runtime_error("Pushed value does not match expected value");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that AddContainer(0) throws an error",
    {"CreateBlock", "AddContainer"},
    []{
      auto intBlock = Block<int>::CreateBlock(0);
      try {
        intBlock.AddContainer(0);
      } catch (const std::exception& e) {
        return;
      }
      throw std::runtime_error("Block::AddContainer(0) did not throw an error.");
    }
  );
  testPtr->AddFeatureTest(
    "Verify that AddContainer with a negative argument throws an error",
    {"CreateBlock", "AddContainer"},
    []{
      auto intBlock = Block<int>::CreateBlock(0);
      try {
        intBlock.AddContainer(-1);
      } catch (const std::exception& e) {
        return;
      }
      throw std::runtime_error("Block::AddContainer(-1) did not throw an error.");
    }
  );
  testPtr->AddFeatureTest(
    "Verify that Push operations correctly update size and allocated size, and that returned pointers have correct values",
    {"Push", "GetSize", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      if (intBlock.GetSize() != 0 || intBlock.GetAllocatedSize() != 2) {
        throw std::runtime_error("Initial block state is incorrect");
      }

      int* ptr1 = intBlock.Push(42);
      if (intBlock.GetSize() != 1 || intBlock.GetAllocatedSize() != 2 || *ptr1 != 42) {
        throw std::runtime_error("First Push operation failed");
      }

      int* ptr2 = intBlock.Push(100);
      int* ptr3 = intBlock.Push(200);
      if (intBlock.GetSize() != 3) {
        throw std::runtime_error("Size after three pushes is not 3\nIt is " + std::to_string(intBlock.GetSize()));
      }
      if (intBlock.GetAllocatedSize() != 4) {
        throw std::runtime_error("Allocated size after three pushes is not 4\nIt is " + std::to_string(intBlock.GetAllocatedSize()));
      }
      if (*ptr2 != 100) {
        throw std::runtime_error("Value at ptr2 is not 100\nIt is " + std::to_string(*ptr2));
      }
      if (*ptr3 != 200) {
        throw std::runtime_error("Value at ptr3 is not 200\nIt is" + std::to_string(*ptr3));
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that Delete sets the pointer to nullptr after deletion",
    {"Push", "Delete"},
    []{
      auto vectorBlock = Block<std::vector<int>>::CreateBlock(1);
      std::vector<int>* ptr = vectorBlock.Push({42});
      if (ptr == nullptr) {
        throw std::runtime_error("Pointer is nullptr after Push");
      }
      vectorBlock.Delete(ptr);
      if (ptr != nullptr) {
        throw std::runtime_error("Pointer is not nullptr after Delete");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that after Push, Delete, and Push again, the first pointer is nullptr, the new value is correct, and the new pointer has the same address as the old one",
    {"Push", "Delete"},
    []{
      auto intBlock = Block<int>::CreateBlock(1);
      int* ptr1 = intBlock.Push(42);
      int* originalAddress = ptr1;

      intBlock.Delete(ptr1);
      if (ptr1 != nullptr) {
        throw std::runtime_error("Pointer is not nullptr after Delete");
      }

      int* ptr2 = intBlock.Push(100);
      if (*ptr2 != 100) {
        throw std::runtime_error("New value is not correct after Push");
      }
      if (ptr2 != originalAddress) {
        throw std::runtime_error("New pointer does not have the same address as the old one");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that CreateBlock(3) with 5 pushes, 4 deletes, and 4 new pushes works correctly",
    {"Push", "Delete", "GetSize", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(3);
      int* ptr1 = intBlock.Push(1);
      int* ptr2 = intBlock.Push(2);
      int* ptr3 = intBlock.Push(3);
      int* ptr4 = intBlock.Push(4);
      int* ptr5 = intBlock.Push(5);

      if (intBlock.GetSize() != 5) {
        throw std::runtime_error("Size after 5 pushes is not 5");
      }
      if (intBlock.GetAllocatedSize() != 6) {
        throw std::runtime_error("Allocated size after 5 pushes is not 6");
      }

      intBlock.Delete(ptr2);
      intBlock.Delete(ptr3);
      intBlock.Delete(ptr4);
      intBlock.Delete(ptr5);

      if (intBlock.GetSize() != 1) {
        throw std::runtime_error("Size after 4 deletes is not 1");
      }
      if (intBlock.GetAllocatedSize() != 6) {
        throw std::runtime_error("Allocated size after 4 deletes is not 6");
      }

      int* ptr6 = intBlock.Push(6);
      int* ptr7 = intBlock.Push(7);
      int* ptr8 = intBlock.Push(8);
      int* ptr9 = intBlock.Push(9);

      if (intBlock.GetSize() != 5) {
        throw std::runtime_error("Size after 4 new pushes is not 5");
      }
      if (intBlock.GetAllocatedSize() != 6) {
        throw std::runtime_error("Allocated size after 4 new pushes is not 6");
      }
    }
  );



  return testPtr;
}