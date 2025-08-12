# Block 
## Overview
The `Block` class is a C++ container designed to manage data efficiently by keeping it contiguous in memory. This makes it ideal for scenarios where data needs to be accessed both by index and by pointer, such as in Entity Component System (ECS) architectures.
## Features 
- **Contiguous Memory**: Data is stored contiguously to optimize iteration across all data of the same type.
- **Resizable**: Allows for dynamic resizing by allocating whole blocks of memory.
- **Pointer Management**: Provides pointers to data, enabling efficient access and management.
- **Fibonacci-Based Allocation**: Uses Fibonacci sequence to make qualified guesses for future memory needs.
## Usage
### Example  

```cpp
#include "Block.hpp"

int main() {

	// Create a block of integers
	Block<int> intBlock = Block<int>::CreateBlock(256);
	
	// Add a container
	intBlock.AddContainer(512);
	
	// Push data to the block
	int* ptr1 = intBlock.Push(42);
	int* ptr2 = intBlock.Push(100);
	
	// Delete data from the block
	intBlock.Delete(ptr1);  
	
	// Get block information
	int allocatedSize = intBlock.GetAllocatedSize();
	int size = intBlock.GetSize();
	
	return 0;
}

```

### Creating a Block  
To create a `Block`, use the `CreateBlock` static method:  
```cpp
Block<int> intBlock = Block<int>::CreateBlock(256);
```

### Adding Containers
You can add containers to the block using the `AddContainer` method:
```cpp
intBlock.AddContainer();
intBlock.AddContainer(512);
```

### Pushing Data
Push data to the block and get a pointer to the stored data:
```cpp
int* ptr = intBlock.Push(42);
```

### Deleting Data
Delete data from the block and set the pointer to `nullptr`:
```cpp
intBlock.Delete(ptr);
```  

### Getting Block Information
Retrieve information about the block:
```cpp
int allocatedSize = intBlock.GetAllocatedSize();
int size = intBlock.GetSize();
```