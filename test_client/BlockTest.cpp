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
    "Create a char block allocating 0 elements and verify that it allocates 0 elements",
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
    testPtr->AddFeatureTest(
      "Verify that CreateBlock<int>(5) with 10 pushes maintains contiguous memory for first 5 and next 5 elements",
      {"Push", "contiguousness"},
      []{
        auto intBlock = Block<int>::CreateBlock(5);
        int* ptrs[10];

        // Push 10 values
        for (int i = 0; i < 10; ++i) {
          ptrs[i] = intBlock.Push(i-5);
        }

        // Verify first 5 are contiguous
        for (int i = 0; i < 4; ++i) {
          if (ptrs[i+1] != ptrs[i] + 1) {
            throw std::runtime_error("First 5 elements are not contiguous");
          }
        }

        // Verify next 5 are contiguous
        for (int i = 5; i < 9; ++i) {
          if (ptrs[i+1] != ptrs[i] + 1) {
            throw std::runtime_error("Next 5 elements are not contiguous");
          }
        }

        // Verify the two groups are not contiguous
        if (ptrs[5] == ptrs[4] + 1) {
          throw std::runtime_error("First and second groups of elements are contiguous");
        }
      }
    );
    testPtr->AddFeatureTest(
      "Verify that CreateBlock<float>(3) with Push, Delete, and Push again maintains contiguous memory for remaining elements",
      {"Push", "Delete", "contiguousness"},
      []{
        auto floatBlock = Block<float>::CreateBlock(3);
        float* floatPtr1 = floatBlock.Push(1.1f);
        float* floatPtr2 = floatBlock.Push(2.2f);
        float* floatPtr3 = floatBlock.Push(3.3f);
        float* floatPtr4;

        // Verify initial contiguousness
        if (floatPtr2 != floatPtr1 + 1 || floatPtr3 != floatPtr2 + 1) {
          throw std::runtime_error("Initial elements are not contiguous");
        }

        // Delete the middle element
        floatBlock.Delete(floatPtr2);
        if (floatPtr2 != nullptr) {
          throw std::runtime_error("Pointer is not nullptr after Delete");
        }

        // Push a new value
        floatPtr4 = floatBlock.Push(4.4f);

        // Verify contiguousness after deletion and push
        if (floatPtr4 != floatPtr1 + 1) {
          throw std::runtime_error("Elements are not contiguous after deletion and push");
        }

        // Verify values
        if (*floatPtr1 != 1.1f || *floatPtr3 != 3.3f || *floatPtr4 != 4.4f) {
          throw std::runtime_error("Values do not match expected values");
        }
      }
    );
  testPtr->AddFeatureTest(
    "Verify contiguousness with multiple pushes and deletes using CreateBlock<char>",
    {"Push", "Delete", "contiguousness"},
    []{
      auto charBlock = Block<char>::CreateBlock(3);
      char* ptrs[10];

      // Initial pushes
      ptrs[0] = charBlock.Push('a');
      ptrs[1] = charBlock.Push('b');
      ptrs[2] = charBlock.Push('c');

      // Verify initial contiguousness
      if (ptrs[1] != ptrs[0] + 1 || ptrs[2] != ptrs[1] + 1) {
        throw std::runtime_error("Initial elements are not contiguous");
      }

      // Delete middle element
      charBlock.Delete(ptrs[1]);
      if (ptrs[1] != nullptr) {
        throw std::runtime_error("Pointer is not nullptr after Delete");
      }

      // Push new element
      ptrs[3] = charBlock.Push('d');

      // Verify contiguousness after deletion and push
      if (ptrs[3] != ptrs[0] + 1) {
        throw std::runtime_error("Elements are not contiguous after deletion and push");
      }

      // Delete first element
      charBlock.Delete(ptrs[0]);
      if (ptrs[0] != nullptr) {
        throw std::runtime_error("Pointer is not nullptr after Delete");
      }

      // Push more elements
      ptrs[4] = charBlock.Push('e');
      ptrs[5] = charBlock.Push('f');
      ptrs[6] = charBlock.Push('g');
      ptrs[7] = charBlock.Push('h');
      ptrs[8] = charBlock.Push('i');
      ptrs[9] = charBlock.Push('j');

      // Verify contiguousness after deletion and push
      if (ptrs[3] != ptrs[4] + 1) {
        throw std::runtime_error("Elements are not contiguous after deletion and push");
      }

      // Verify contiguousness of new elements
      for (int i = 5; i < 7; ++i) {
        if (ptrs[i+1] != ptrs[i] + 1) {
          throw std::runtime_error("New elements 5-7 are not contiguous");
        }
      }
          for (int i = 8; i < 9; ++i) {
        if (ptrs[i+1] != ptrs[i] + 1) {
          throw std::runtime_error("New elements 7-9 are not contiguous");
        }
      }

      // Verify the two groups are not contiguous
      if (ptrs[5] == ptrs[4] + 1) {
        throw std::runtime_error("First and second groups of elements are contiguous");
      }

      // Verify values
      if (*ptrs[3] != 'd' || *ptrs[4] != 'e' || *ptrs[5] != 'f' || *ptrs[9] != 'j') {
        throw std::runtime_error("Values do not match expected values");
      }
    }
  );

  // START 
  testPtr->AddFeatureTest(
    "Verify that adding multiple containers works correctly",
    {"AddContainer", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      intBlock.AddContainer(4);
      intBlock.AddContainer(8);
      intBlock.AddContainer(16);

      if (intBlock.GetAllocatedSize() != 2 + 4 + 8 + 16) {
        throw std::runtime_error("Allocated size after adding multiple containers is incorrect");
      }
    }
  );

  testPtr->AddFeatureTest(
    "Verify that adding containers with specific sizes works correctly",
    {"AddContainer", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      intBlock.AddContainer(4);
      intBlock.AddContainer(8);
      intBlock.AddContainer(16);

      if (intBlock.GetAllocatedSize() != 2 + 4 + 8 + 16) {
        throw std::runtime_error("Allocated size after adding containers with specific sizes is incorrect");
      }
    }
  );

  testPtr->AddFeatureTest(
    "Verify that adding containers after pushes and deletes works correctly",
    {"AddContainer", "Push", "Delete", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      int* ptr1 = intBlock.Push(42);
      int* ptr2 = intBlock.Push(100);
      intBlock.Delete(ptr1);
      intBlock.AddContainer(4);
      intBlock.AddContainer(8);

      if (intBlock.GetAllocatedSize() != 2 + 4 + 8) {
        throw std::runtime_error("Allocated size after adding containers after pushes and deletes is incorrect");
      }
    }
  );

  testPtr->AddFeatureTest(
    "Verify that adding containers with sizes that are not powers of two works correctly",
    {"AddContainer", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      intBlock.AddContainer(3);
      intBlock.AddContainer(5);
      intBlock.AddContainer(7);

      if (intBlock.GetAllocatedSize() != 2 + 3 + 5 + 7) {
        throw std::runtime_error("Allocated size after adding containers with sizes that are not powers of two is incorrect");
      }
    }
  );

  testPtr->AddFeatureTest(
    "Verify that adding containers with sizes that are very large works correctly",
    {"AddContainer", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      intBlock.AddContainer(1000000);
      intBlock.AddContainer(2000000);

      if (intBlock.GetAllocatedSize() != 2 + intBlock.GetMaxContainerSize() + intBlock.GetMaxContainerSize()) {
        throw std::runtime_error("Allocated size after adding containers with sizes that are very large is incorrect");
      }
    }
  );

  testPtr->AddFeatureTest(
    "Verify that adding containers with sizes that are very small works correctly",
    {"AddContainer", "GetAllocatedSize"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      intBlock.AddContainer(1);
      intBlock.AddContainer(2);

      if (intBlock.GetAllocatedSize() != 2 + 1 + 2) {
        throw std::runtime_error("Allocated size after adding containers with sizes that are very small is incorrect");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify contiguousness after adding containers with different sizes and multiple pushes",
    {"CreateBlock", "AddContainer", "Push", "contiguousness"},
    []{
      auto intBlock = Block<int>::CreateBlock(5);
      intBlock.AddContainer(5);
      intBlock.AddContainer(3);
      intBlock.AddContainer(7);

      // First loop of 5 pushes
      int* ptrs5[5];
      for (int i = 0; i < 5; ++i) {
        ptrs5[i] = intBlock.Push(i);
      }
      for (int i = 0; i < 4; ++i) {
        if (ptrs5[i+1] != ptrs5[i] + 1) {
          throw std::runtime_error("First 5 elements are not contiguous");
        }
      }

      // Second loop of 5 pushes
      int* ptrs5_2[5];
      for (int i = 0; i < 5; ++i) {
        ptrs5_2[i] = intBlock.Push(i + 5);
      }
      for (int i = 0; i < 4; ++i) {
        if (ptrs5_2[i+1] != ptrs5_2[i] + 1) {
          throw std::runtime_error("Next 5 elements are not contiguous");
        }
      }

      // Third loop of 3 pushes
      int* ptrs3[3];
      for (int i = 0; i < 3; ++i) {
        ptrs3[i] = intBlock.Push(i + 10);
      }
      for (int i = 0; i < 2; ++i) {
        if (ptrs3[i+1] != ptrs3[i] + 1) {
          throw std::runtime_error("Next 3 elements are not contiguous");
        }
      }

      // Fourth loop of 7 pushes
      int* ptrs7[7];
      for (int i = 0; i < 7; ++i) {
        ptrs7[i] = intBlock.Push(i + 13);
      }
      for (int i = 0; i < 6; ++i) {
        if (ptrs7[i+1] != ptrs7[i] + 1) {
          throw std::runtime_error("Next 7 elements are not contiguous");
        }
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that Delete returns false when given a pointer that does not belong in the Block",
    {"Delete"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      int* ptr1 = intBlock.Push(42);
      int* ptr2 = intBlock.Push(100);

      // Create a pointer that doesn't belong to the block
      int value = 200;
      int* invalidPtr = &value;

      int* ptr3 = intBlock.Push(300);

      // Verify Delete returns false for invalid pointer
      if (intBlock.Delete(invalidPtr)) {
        throw std::runtime_error("Delete returned true for a pointer that does not belong to the Block");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that Delete returns false when given a pointer that does not belong in the Block",
    {"Delete"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      int* ptr1 = intBlock.Push(42);
      int* ptr2 = intBlock.Push(100);

      // Create a pointer that doesn't belong to the block
      int* invalidPtr = new int(200);

      int* ptr3 = intBlock.Push(300);

      // Verify Delete returns false for invalid pointer
      if (intBlock.Delete(invalidPtr)) {
        throw std::runtime_error("Delete returned true for a pointer that does not belong to the Block");
      }

      // Clean up the invalid pointer
      delete invalidPtr;
    }
  );
  testPtr->AddFeatureTest(
    "Verify that Delete returns false when given a pointer that belongs to another Block",
    {"Delete"},
    []{
      auto floatBlock1 = Block<float>::CreateBlock(2);
      auto floatBlock2 = Block<float>::CreateBlock(2);

      float* ptr1 = floatBlock1.Push(1.1f);
      float* ptr2 = floatBlock2.Push(2.2f);

      // Verify Delete returns false for pointer from another block
      if (floatBlock1.Delete(ptr2)) {
        throw std::runtime_error("Delete returned true for a pointer that belongs to another Block");
      }

      // Verify the pointer is still valid and points to the same value
      if (*ptr2 != 2.2f) {
        throw std::runtime_error("Pointer from another Block was modified");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify contiguousness after deleting a middle element and pushing a new one in a Position Block",
    {"Push", "Delete", "contiguousness"},
    []{
      struct Position
      {
        int x;
        int y;
      };

      auto positionBlock = Block<Position>::CreateBlock(3);
      Position* pos0 = positionBlock.Push({0, 0});
      Position* pos1 = positionBlock.Push({1, 1});
      Position* pos2 = positionBlock.Push({2, 2});

      // Verify initial contiguousness
      if (pos1 != pos0 + 1 || pos2 != pos1 + 1)
      {
        throw std::runtime_error("Initial elements are not contiguous");
      }

      // Delete the middle element
      positionBlock.Delete(pos1);
      if (pos1 != nullptr)
      {
        throw std::runtime_error("Pointer is not nullptr after Delete");
      }

      // Push a new value
      Position* pos3 = positionBlock.Push({3, 3});

      // Verify contiguousness after deletion and push
      if (pos3 != pos0 + 1)
      {
        throw std::runtime_error("Elements are not contiguous after deletion and push");
      }
      if (pos2 != pos3 + 1)
      {
        throw std::runtime_error("Elements are not contiguous after deletion and push");
      }

      // Verify values
      if (pos0->x != 0 || pos0->y != 0 ||
          pos3->x != 3 || pos3->y != 3 ||
          pos2->x != 2 || pos2->y != 2) {
        throw std::runtime_error("Values do not match expected values");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify contiguousness after adding containers and performing multiple pushes and deletes on a string Block",
    {"AddContainer", "Push", "Delete", "contiguousness"},
    [] {
      auto stringBlock = Block<std::string>::CreateBlock(0);
      stringBlock.AddContainer(3);
      stringBlock.AddContainer(3);

      // Push initial elements to fill the block
      std::string* string0 = stringBlock.Push("string0");
      std::string* string1 = stringBlock.Push("string1");
      std::string* string2 = stringBlock.Push("string2");
      std::string* string3 = stringBlock.Push("string3");
      std::string* string4 = stringBlock.Push("string4");
      std::string* string5 = stringBlock.Push("string5");
      std::string* string6 = stringBlock.Push("string6");

      // Verify initial contiguousness
      if (string1 != string0 + 1 || string2 != string1 + 1) {
        throw std::runtime_error("First 3 elements are not contiguous");
      }
      if (string4 != string3 + 1 || string5 != string4 + 1) {
        throw std::runtime_error("Next 3 elements are not contiguous");
      }

      // Delete elements
      stringBlock.Delete(string1);
      stringBlock.Delete(string3);
      stringBlock.Delete(string5);

      // Push new elements
      std::string* string1b = stringBlock.Push("string1b");
      std::string* string3b = stringBlock.Push("string3b");
      std::string* string5b = stringBlock.Push("string5b");

      // Verify contiguousness after deletion and push
      if (string1b != string0 + 1 || string2 != string1b + 1) {
        throw std::runtime_error("First 3 elements are not contiguous");
      }
      if (string4 != string3b + 1 || string5b != string4 + 1) {
        throw std::runtime_error("Next 3 elements are not contiguous");
      }

      // Verify values
      if (*string1b != "string1b" || *string2 != "string2" || *string3b != "string3b" ||
          *string4 != "string4" || *string5b != "string5b" || *string6 != "string6" || *string0 != "string0") {
        throw std::runtime_error("Values do not match expected values");
      }

      // Delete elements
      stringBlock.Delete(string0);
      stringBlock.Delete(string1b);

      // Push new elements
      std::string* string0b = stringBlock.Push("string0b");
      std::string* string1c = stringBlock.Push("string1c");

      // Verify contiguousness after deletion and push
      if (string1c != string0b + 1 || string2 != string1c + 1) {
        throw std::runtime_error("First 3 elements are not contiguous");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify contiguousness after deleting values in reverse order, and repulate then in the same reverse order on a double Block",
    {"CreateBlock", "AddContainer", "Push", "Delete", "contiguousness"},
    []{
      auto doubleBlock = Block<double>::CreateBlock(3);
      doubleBlock.AddContainer(3);

      // Push initial elements
      double* double0 = doubleBlock.Push(0.0);
      double* double1 = doubleBlock.Push(1.0);
      double* double2 = doubleBlock.Push(2.0);
      double* double3 = doubleBlock.Push(3.0);
      double* double4 = doubleBlock.Push(4.0);
      double* double5 = doubleBlock.Push(5.0);

      // Verify initial contiguousness
      if (double1 != double0 + 1 || double2 != double1 + 1) {
        throw std::runtime_error("First 3 elements are not contiguous");
      }
      if (double4 != double3 + 1 || double5 != double4 + 1) {
        throw std::runtime_error("Next 3 elements are not contiguous");
      }

      // Delete elements in specified order
      doubleBlock.Delete(double4);
      doubleBlock.Delete(double3);
      doubleBlock.Delete(double1);

      // Push new elements
      double* double4b = doubleBlock.Push(4.5);
      double* double3b = doubleBlock.Push(3.5);
      double* double1b = doubleBlock.Push(1.5);

      // Verify contiguousness in specified order
      if (double1b != double0 + 1 || double2 != double1b + 1) {
        throw std::runtime_error("Elements double0, double1b, double2 are not contiguous");
      }
      if (double4b != double3b + 1 || double5 != double4b + 1) {
        throw std::runtime_error("Elements double3b, double4b, double5 are not contiguous");
      }

      // Verify values
      if (*double0 != 0.0 || *double1b != 1.5 || *double2 != 2.0 ||
          *double3b != 3.5 || *double4b != 4.5 || *double5 != 5.0) {
        throw std::runtime_error("Values do not match expected values");
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify that AddContainer(0) throws an error",
    {"AddContainer"},
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
    "Verify that AddContainer(-1) throws an error",
    {"AddContainer"},
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
    "Verify contiguousness after multiple pushes and deletes with a very large number of elements",
    {"CreateBlock", "AddContainer", "Push", "Delete", "contiguousness"},
    []
    {
      const int largeSize = 10000;
      auto intBlock = Block<int>::CreateBlock(largeSize / 2);
      intBlock.AddContainer(largeSize / 2);

      // Push initial elements
      std::vector<int*> pointers;
      for (int i = 0; i < largeSize; ++i) {
        pointers.push_back(intBlock.Push(i));
      }

      // Verify initial contiguousness
      for (int i = 0; i < intBlock.GetMaxContainerSize() - 2; ++i) {
        if (
        pointers[i+1] != pointers[i] + 1
        ) {
          throw std::runtime_error("Initial elements are not contiguous");
        }
      }

      // Delete every other element
      for (int i = 0; i < largeSize; i += 2) {
        intBlock.Delete(pointers[i]);
        if (pointers[i] != nullptr) {
          throw std::runtime_error("Pointer is not nullptr after Delete");
        }
      }

      // Push new elements to fill the gaps
      for (int i = 0; i < largeSize; i += 2) {
        pointers[i] = intBlock.Push(i + largeSize);
      }

      // Verify contiguousness after deletion and push
      for (int i = 0; i < largeSize - 1; ++i) {
        if (
        pointers[i+1] != pointers[i] + 1
        && i % intBlock.GetMaxContainerSize() != intBlock.GetMaxContainerSize() - 1
        ) {
          throw std::runtime_error("Elements are not contiguous after deletion and push");
        }
      }

      // Verify values
      for (int i = 0; i < largeSize; ++i) {
        int expectedValue = (i % 2 == 0) ? (i + largeSize) : i;
        if (*pointers[i] != expectedValue) {
          throw std::runtime_error("Values do not match expected values");
        }
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify contiguousness after multiple pushes and deletes with a very large number of disposed pointers",
    {"CreateBlock", "AddContainer", "Push", "Delete", "contiguousness"},
    []
    {
      constexpr int largeSize = 10000;
      auto intBlock = Block<int>::CreateBlock(largeSize / 2);
      intBlock.AddContainer(largeSize / 2);

      // Push initial elements
      std::vector<int*> pointers;
      for (int i = 0; i < largeSize; ++i) {
        pointers.push_back(intBlock.Push(i));
      }

      // Verify initial contiguousness
      for (int i = 0; i < intBlock.GetMaxContainerSize() - 2; ++i) {
        if (pointers[i+1] != pointers[i] + 1) {
          throw std::runtime_error("Initial elements are not contiguous");
        }
      }

      // Delete every other element
      for (int i = 0; i < largeSize; i += 2) {
        intBlock.Delete(pointers[i]);
        if (pointers[i] != nullptr) {
          throw std::runtime_error("Pointer is not nullptr after Delete");
        }
      }
      // Verify disposed pointers are nullptr
      for (int i = 0; i < largeSize; i += 2) {
        if (pointers[i] != nullptr) {
          throw std::runtime_error("Disposed pointer is not nullptr");
        }
      }

      // Push new elements to fill the gaps
      for (int i = 0; i < largeSize; i += 2) {
        pointers[i] = intBlock.Push(i + largeSize);
      }

      // Verify contiguousness after deletion and push
      for (int i = 0; i < largeSize - 1; ++i) {
        if (pointers[i+1] != pointers[i] + 1 && i % intBlock.GetMaxContainerSize() != intBlock.GetMaxContainerSize() - 1) {
          throw std::runtime_error("Elements are not contiguous after deletion and push");
        }
      }

      // Verify values
      for (int i = 0; i < largeSize; ++i) {
        int expectedValue = (i % 2 == 0) ? (i + largeSize) : i;
        if (*pointers[i] != expectedValue) {
          throw std::runtime_error("Values do not match expected values");
        }
      }
    }
  );
  testPtr->AddFeatureTest(
    "Verify contiguousness after adding containers with sizes that are not powers of two",
    {"AddContainer", "Push", "contiguousness"},
    []{
      auto intBlock = Block<int>::CreateBlock(2);
      intBlock.AddContainer(3);
      intBlock.AddContainer(5);
      intBlock.AddContainer(7);

      // Push elements to fill the containers
      int* ptrs[17];
      for (int i = 0; i < 17; ++i) {
        ptrs[i] = intBlock.Push(i);
      }

      // Verify contiguousness of first container (size 2)
      for (int i = 0; i < 1; ++i) {
        if (ptrs[i+1] != ptrs[i] + 1) {
          throw std::runtime_error("First container elements are not contiguous");
        }
      }

      // Verify contiguousness of second container (size 3)
      for (int i = 2; i < 4; ++i) {
        if (ptrs[i+1] != ptrs[i] + 1) {
          throw std::runtime_error("Second container elements are not contiguous");
        }
      }

      // Verify contiguousness of third container (size 5)
      for (int i = 5; i < 9; ++i) {
        if (ptrs[i+1] != ptrs[i] + 1) {
          throw std::runtime_error("Third container elements are not contiguous");
        }
      }

      // Verify contiguousness of fourth container (size 7)
      for (int i = 10; i < 17 - 1; ++i) {
        if (ptrs[i+1] != ptrs[i] + 1) {
          throw std::runtime_error("Fourth container elements are not contiguous");
        }
      }
    }
  );
  return testPtr;
}