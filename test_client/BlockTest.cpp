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

  // TODO: Test that it throws an error if you create a Block of size 0 and tries to Push.
  // TODO: Verify that it does not throw and error if you create a Block of size 0, AddContainer, and then Push.
  // TODO: It should not be possible to AddContainer of size 0.
  // TODO: It should not be possible to AddContainer of a negative size.



  return testPtr;
}