# 📚 DSA - Data Structures & Algorithms 

This repository contains a collection of data structures implemented during my 1st year at  
**UBB**, as part of the **Data Structures & Algorithms** course.  
Each folder represents a distinct abstract data type (ADT), implemented in **C++** from scratch, without STL containers unless explicitly permitted.

---

## Concepts Practiced

- Linked list on array
- Hashing and separate chaining
- Binary search tree with index-based nodes
- Fixed capacity container design
- Indexed iteration
- Memory-safe dynamic resizing

---

## Implemented ADTs

### `FixedCapBiMap`
- A **bi-directional map** with **fixed capacity**
- One-to-one mapping: each key has a unique value, and vice versa

---

### `MultiMap-DLLA`
- A MultiMap where key-value pairs are stored using a **Doubly Linked List on Array (DLLA)**
- Allows multiple values per key

---

### `MultiMap-hashtable`
- A MultiMap using a **hash table** with **separate chaining**
- Keys are unique; values are stored in **dynamic arrays**

---

### `Set-dynamic array`
- Set represented by a **dynamic Boolean array**, where:
  - Index = integer offset (negative-friendly)
  - Value = presence of element
- Automatically resizes if needed

---

### `SortedList Indexed-DLL`
- A sorted list implemented using a **doubly linked list with integer indexing (`TPozition`)**
- Maintains ordering via a relational function (e.g., ascending/descending)

---

### `SortedMultiMap-BST`
- A SortedMultiMap implemented using a **Binary Search Tree** stored in **array-based linked format**
- Keys appear multiple times if they have multiple values
- Elements are kept sorted based on a custom `Relation`

---




