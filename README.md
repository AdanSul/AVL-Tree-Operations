# AVL-Tree-Operations

This repository provides an implementation of AVL Tree operations to address a variety of computational tasks related to binary search trees. The implementation ensures that all operations maintain the AVL Tree's balance property, providing efficient solutions to tree-based queries.

## Features
The implementation includes the following key operations:
1. **Insert(x)**: Adds a new node with the key `x` to the AVL Tree.
2. **Search(x)**: Checks if a node with the key `x` exists in the AVL Tree.
3. **Delete(x)**: Removes a node with the key `x` from the AVL Tree if it exists.
4. **DeleteAll()**: Removes all nodes from the AVL Tree, clearing the structure entirely.
5. **LCA(x, y)**: Finds the Lowest Common Ancestor of nodes with keys `x` and `y`.
6. **Sum(x, y)**: Calculates the sum of all keys in the range `[x, y]`.
7. **Merge(T1, T2)**: Merges two AVL Trees `T1` and `T2` into a single AVL Tree.

## Complexity
- **Insert, Delete, Search, LCA, Sum**: O(log(n))
- **DeleteAll, Merge**: O(n)