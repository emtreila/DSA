# 📚 DSA — Data Structures & Algorithms 

This repository contains a collection of data structures implemented during my first year at  
**UBB**, as part of the **Data Structures & Algorithms** course.  
Each folder represents a distinct abstract data type (ADT), implemented in **C++** from scratch, without STL containers unless explicitly permitted.

---

## 🧠 Concepts Practiced

- Linked list with custom allocator (DLLA)
- Hashing and separate chaining
- Binary search tree with index-based nodes
- Fixed capacity container design
- Indexed iteration
- Memory-safe dynamic resizing

---

## 📦 Implemented ADTs

### 🔁 `MultiMap-DLLA`
- A MultiMap where key-value pairs are stored using a **Doubly Linked List Array (DLLA)**
- Allows multiple values per key
- Custom memory management with reuse of deleted nodes
- Supports full iteration, addition, removal, search

---

### 🧵 `MultiMap-hashtable`
- A MultiMap using a **hash table** with **separate chaining**
- Keys are unique; values are stored in **dynamic arrays**
- Good performance on large sets due to hash-based access

---

### 🌲 `SortedMultiMap-BST`
- A SortedMultiMap implemented using a **Binary Search Tree** stored in **array-based linked format**
- Keys appear multiple times if they have multiple values
- Elements are kept sorted based on a custom `Relation`

---

### 📃 `SortedList Indexed-DLL`
- A sorted list implemented using a **doubly linked list with integer indexing (`TPozition`)**
- Maintains ordering via a relational function (e.g., ascending/descending)
- Supports indexed iteration, insertion, removal

---

### ✅ `Set-dynamic array`
- Set represented by a **dynamic Boolean array**, where:
  - Index = integer offset (negative-friendly)
  - Value = presence of element
- Allows very fast membership checks in O(1)
- Automatically resizes if needed

---

### 🔄 `FixedCapBiMap`
- A **bi-directional map** with **fixed capacity**
- One-to-one mapping: each key has a unique value, and vice versa
- Constant-time search by key or value
- Insertion fails when full or duplicate found

---
