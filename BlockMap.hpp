#pragma once

#include <typeindex>
#include <unordered_map>
#include <memory>
#include "Block.hpp"

class BlockMap
{
private:
  std::unordered_map<std::type_index, std::shared_ptr<void>> m_componentMap;
public:

  template<typename T>
  bool TryAdd(int a_allocatedContainerSize = 0)
  {
    if (m_componentMap.find(std::type_index(typeid(T))) != m_componentMap.end())
    {
      return false;
    }

    auto block = std::make_shared<Block<T>>(
      a_allocatedContainerSize == 0
      ? Block<T>::CreateBlock()
      : Block<T>::CreateBlock(a_allocatedContainerSize)
    );

    m_componentMap[std::type_index(typeid(T))] = block;
    return true;
  }

  template<typename T>
  std::shared_ptr<Block<T>> Get()
  {
    auto iterator = m_componentMap.find(std::type_index(typeid(T)));
    if (iterator == m_componentMap.end())
    {
      throw std::runtime_error("No element found for the given key: " + std::string(std::type_index(typeid(T)).name()) + ".\n");
    }
    return std::static_pointer_cast<Block<T>>(iterator->second);
  }

  template<typename T>
  bool Delete()
  {
    auto iterator = m_componentMap.find(std::type_index(typeid(T)));
    if (iterator == m_componentMap.end())
    {
      return false;
    }
    iterator->second.reset(); // Reset the shared pointer to release the memory
    m_componentMap.erase(iterator);
    if (m_componentMap.find(std::type_index(typeid(T))) == m_componentMap.end())
    {
      return true;
    }
    return false;
  }
};