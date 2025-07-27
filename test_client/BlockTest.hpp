#pragma once

#include "TestKit-pp/Test.hpp"
#include <memory>

class BlockTest
{
public:
  static std::shared_ptr<Test> GetTest();
};