#pragma once

#include <memory>
#include <queue>
#include <vector>
#include <typeinfo>
#include <string>
#include <stdexcept>

template <typename T>
class Block
{
private:
  std::vector<std::unique_ptr<T[]>> m_containers;
  std::vector<size_t> m_containerFirstIndexes;
  std::vector<size_t> m_containerSizes;
  std::queue<T*> m_disposed;
  size_t m_maxSize;
  size_t m_size;

public:
  void AddContainer()
  {
    const int nextContainerSize =
      m_containerSizes.back() == 0
      ? 256
      : m_containers.size() == 1
      ? m_containerSizes[0]
      : m_containerSizes.back() + m_containerSizes[m_containerSizes.size() - 2];
    AddContainer(nextContainerSize);
  }
  void AddContainer(const int &a_nextContainerSize)
  {
    if (a_nextContainerSize <= 0) {
      throw std::invalid_argument("Cannot add a container of size 0 or less.");
    }
    const size_t nextContainerFirstIndex = m_containerFirstIndexes.back() + m_containerSizes.back();
    m_containerSizes.push_back(static_cast<size_t>(a_nextContainerSize));
    m_containerFirstIndexes.push_back(nextContainerFirstIndex);
    m_containers.push_back(std::make_unique<T[]>(static_cast<size_t>(a_nextContainerSize)));
    m_maxSize = m_containerFirstIndexes.back() + m_containerSizes.back();
  }
  static Block<T> CreateBlock(const int a_firstContainerSize = 256) {
    if (a_firstContainerSize < 0)
    {
      throw std::invalid_argument("Block::CreateBlock: Cannot create a block with a negative container size.\na_firstContainerSize: " + std::to_string(a_firstContainerSize));
    }
    return Block<T>(static_cast<size_t>(a_firstContainerSize));
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
    return m_size - m_disposed.size();
  }
  [[nodiscard]] T* Push(const T &newValue)
  {
    if (m_maxSize == 0)
    {
      const std::string CONTAINER_TYPE = "Container type: " + std::string(typeid(T).name());
      throw std::runtime_error("Block::Push. Cannot push to a block with zero allocation. Use AddContainer() to allocate space.\n" + CONTAINER_TYPE);
    }
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
    // TODO: The latest index is not necessarily the first index with an undefined value.
    itemPtr = FindPointerForIndex(m_size) - 1;
    // itemPtr = m_containers.back().get() + (m_size - m_containerFirstIndexes.back() - 1);
    *itemPtr = newValue;
    return itemPtr;
  }

private:
  explicit Block(size_t a_firstContainerSize)
  {
    m_containers.push_back(std::make_unique<T[]>(a_firstContainerSize));
    m_containerFirstIndexes = { 0 };
    m_containerSizes = { a_firstContainerSize };
    m_maxSize = a_firstContainerSize;
    m_size = 0;
    m_disposed = { };
  }
  Block() : Block(256) {}

  [[nodiscard]] int FindContainerIndexForIndex(const int a_index) const
  {
    if (a_index > m_size || a_index < 0) throw std::out_of_range("Index " + std::to_string(a_index) + " does not exist in Block of size " + std::to_string(m_size) + ".\n");
    if (m_containerFirstIndexes.size() == 1) return 0;
    if (a_index > m_containerFirstIndexes.back()) return m_containerFirstIndexes.size() - 1;
    int containerIndex = m_containerFirstIndexes.size() / 2;
    int stepSize = m_containerFirstIndexes.size() / 4;
    stepSize = (stepSize == 0) ? 1 : stepSize;
    while (!(a_index >= m_containerFirstIndexes[containerIndex] && a_index < m_containerFirstIndexes[containerIndex + 1]))
    {
      if (a_index >= m_containerFirstIndexes[containerIndex + 1])
      {
        containerIndex = containerIndex + stepSize;
      }
      else
      {
        containerIndex = containerIndex - stepSize;
      }
      stepSize /= 2;
      stepSize = (stepSize == 0) ? 1 : stepSize;
    }
    return containerIndex;
  }
  [[nodiscard]] int FindContainerIndexForPointer(T* a_ptr)
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
  [[nodiscard]] T* FindPointerForIndex(const size_t a_index)
  {
    const size_t containerIndex = FindContainerIndexForIndex(a_index);
    return m_containers[containerIndex].get() + (a_index - m_containerFirstIndexes[containerIndex]);
  }
};

