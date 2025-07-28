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
  static Block<T> CreateBlock(int a_firstContainerSize = 256) {
    if (a_firstContainerSize < 0)
    {
      throw std::invalid_argument("Block::CreateBlock: Cannot create a block with a negative container size.\na_firstContainerSize: " + a_firstContainerSize);
    }
    return Block<T>(a_firstContainerSize);
  }

  bool Delete(T*& ptr)
  {
    if (FindContainerIndexForPointer(ptr) == -1) return false;
    T* disposePointer = ptr;
    m_disposed.push(disposePointer);
    ptr = nullptr;
    return true;
  }
  [[nodiscard]] int GetAllocatedSize() const
  {
    return m_maxSize;
  }
  [[nodiscard]] int GetSize() const
  {
    return m_size;
  }
  [[nodiscard]] T* Push(const T &newValue)
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
  explicit Block(int a_firstContainerSize)
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
    const int nextContainerSize = (m_containers.size() == 1)
      ? m_containerSizes[0]
      : m_containerSizes.back() + m_containerSizes[m_containerSizes.size() - 2];
    AddContainer(nextContainerSize);
  }
  void AddContainer(const int &a_nextContainerSize)
  {
    if (a_nextContainerSize <= 0)
    {
      throw std::invalid_argument("Cannot add a container of size 0 or less.");
    }
    int nextContainerFirstIndex = m_containerFirstIndexes.back() + m_containerSizes.back();
    m_containerSizes.push_back(a_nextContainerSize);
    m_containerFirstIndexes.push_back(nextContainerFirstIndex);
    m_containers.push_back(std::make_unique<T[]>(a_nextContainerSize));
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

