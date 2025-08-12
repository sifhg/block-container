# Block: A Contiguous Memory Container for C++

## Overview

`Block` is a C++ container class designed for Entity Component System (ECS) architecture. A `Block` manages data in contiguous memory blocks, optimizing for:

- **Cache efficiency** (sequential memory access).
- **Dynamic resizing** (Fibonacci-based allocation to minimize reallocations).
- **Pointer stability** (safe pointer access even after resizing).

### Use `Block` for ECS?

In ECS, components of the same type are often accessed sequentially (e.g., iterating all `Position` or `Mesh` components). `Block` ensures:

1. **Contiguity**: Components are packed tightly in memory, improving cache locality.
2. **Predictable growth**: When the developer pushes more elements to a `Block` than what was orginially allocated, the `Block` will manage memory allocation, making a qualified guess on how many elements will be necessary using a Fibonacci-based allocation allocation algorithm. Allocating appropriate memory reduces reallocation overhead and optimises contiguouness.
3. **Pointer safety**: Memory locations of deleted elements are recycled, and valid pointers persist across resizes.

### Key Features

| Feature                | Benefit for ECS                                         |
| ---------------------- | ------------------------------------------------------- |
| Contiguous storage     | Faster iteration (e.g., `for (auto& pos : positions)`). |
| Fibonacci allocation   | Balances memory usage and growth efficiency.            |
| Pointer recycling      | Reuses memory from deleted elements.                    |
| Bounded container size | Prevents unbounded memory spikes.                       |

---

## Quick Start

### Installation

TODO: Write this paragraph later when you have created a release tag

### Basic Usage

```cpp
#include "Block.hpp"

// Create a block for 'Position' components (default initial size: 256)
Block<Position> positions = Block<Position>::CreateBlock();

// Add components
Position* p1 = positions.Push(Position{1.0f, 2.0f});
Position* p2 = positions.Push(Position{3.0f, 4.0f});

// Delete a component (pointer becomes invalid)
positions.Delete(p1);

// Iterate all active components
for (int i = 0; i < positions.GetSize(); ++i) {
    Position* p = positions.FindPointerForIndex(i);
    // Use p->x, p->y...
}
```

## API Reference

### Methods

#### `CreateBlock`

```cpp
/**
 * Factory method to initialize a new `Block` with contiguous memory allocation.
 *
 * @tparam T        Type of elements stored in the block.
 * @param a_firstContainerSize Initial container size (default: 256). Must be ≥ 0.
 * @return          A new `Block<T>` instance with preallocated memory.
 * @throws          std::invalid_argument if `a_firstContainerSize` is negative.
 */
static Block<T> CreateBlock(const int a_firstContainerSize = 256);
```

#### `Push`

```cpp
/**
 * Adds an element to the block and returns a pointer to it.
 * Automatically allocates new containers if the block is full.
 *
 * @param newValue  The element to add (copied into contiguous storage).
 * @return          Pointer to the newly added element.
 * @throws          std::runtime_error if the block has zero allocation (call `AddContainer()` first).
 */
[[nodiscard]] T* Push(const T& newValue);
```

#### `Delete`

```cpp
/**
 * Marks an element for reuse and invalidates its pointer.
 * The memory is recycled for future `Push` operations.
 *
 * @param ptr       Reference to the pointer being deleted (set to `nullptr` on success).
 * @return          `true` if the pointer was valid and deleted, `false` otherwise.
 */
bool Delete(T*& ptr);
```

#### `GetSize`

```cpp
/**
 * Returns the number of **active** elements (excludes deleted/reusable slots).
 *
 * @return          Count of active elements (size_t).
 */
[[nodiscard]] size_t GetSize() const;
```

#### `GetAllocatedSize`

```cpp
/**
 * Returns the total allocated capacity (including deleted elements).
 * Represents the maximum possible elements before reallocation.
 *
 * @return          Total capacity (int).
 */
[[nodiscard]] int GetAllocatedSize() const;
```

#### `AddContainer`

```cpp
/**
 * Manually adds a new container to the block.
 * If no size is specified, the next container follows the Fibonacci sequence (e.g., 256 → 256 → 512).
 *
 * @param a_nextContainerSize Optional. Custom size for the new container (clamped to `m_maxContainerSize`).
 * @throws          std::invalid_argument if `a_nextContainerSize` ≤ 0.
 */
void AddContainer(const int& a_nextContainerSize = /* Fibonacci-based */);
```
