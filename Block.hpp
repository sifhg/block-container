#pragma once

#include <memory>
#include <queue>
#include <vector>

template <typename T>
class Block
{
private:
  std::vector<std::unique_ptr<T[]>> m_containers;
  std::vector<int> m_containerFirstIndexes;
  std::vector<int> m_containerSizes;
  std::queue<T*> m_disposed;
  int m_maxSize;
  int m_size;

public:
  static Block<T> CreateBlock(int firstContainerSize = 256) {
    return Block<T>(firstContainerSize);
  }

  bool Delete(T*& ptr)
  {
    if (FindContainerIndexForPointer(ptr) == -1) return false;
    T* disposePointer = ptr;
    m_disposed.push(disposePointer);
    ptr = nullptr;
    return true;
  }
  int GetAllocatedSize()
  {
    return m_maxSize;
  }
  int GetSize()
  {
    return m_size;
  }
  T* Push(T newValue)
  {
    T* itemPtr;
    if (!m_disposed.empty())
    {
      itemPtr = m_disposed.front();
      m_disposed.pop();
      *itemPtr = newValue;
      return itemPtr;
    }
    m_size++;
    if (m_size > m_maxSize)
    {
      AddContainer();
    }
    itemPtr = m_containers.back().get() + (m_size - m_containerFirstIndexes.back() - 1);
    *itemPtr = newValue;
    return itemPtr;
  }

private:
  Block(int a_firstContainerSize)
  {
    m_containers.push_back(std::make_unique<T[]>(a_firstContainerSize));
    m_containerFirstIndexes = { 0 };
    m_containerSizes = { a_firstContainerSize };
    m_maxSize = a_firstContainerSize;
    m_size = 0;
    m_disposed = { };
  }
  Block() : Block(256) {}

  void AddContainer()
  {
    int nextContainerSize;
    if (m_containers.size() == 1) {
      nextContainerSize = m_containerSizes[0];
    }
    else
    {
      nextContainerSize = m_containerSizes.back() + m_containerSizes[m_containerSizes.size() - 2];
    }
    int nextContainerFirstIndex = m_containerFirstIndexes.back() + m_containerSizes.back();
    m_containerSizes.push_back(nextContainerSize);
    m_containerFirstIndexes.push_back(nextContainerFirstIndex);
    m_containers.push_back(std::make_unique<T[]>(nextContainerSize));
    m_maxSize = m_containerFirstIndexes.back() + m_containerSizes.back();
  }
  int FindContainerIndexForPointer(T* a_ptr)
  {
    for (int v = m_containers.size() - 1; v >= 0; --v)
    {
      if (
          a_ptr >= m_containers[v].get() &&
          a_ptr <= m_containers[v].get() + m_containerSizes[v] - 1
      )
      {
        return v;
      }
    }
    return -1;
  }
};

