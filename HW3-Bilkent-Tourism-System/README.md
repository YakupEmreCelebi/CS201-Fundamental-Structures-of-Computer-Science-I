# 🚌 Bilkent Tourism: Multi-Linked List Management System

This project is a robust C++ implementation of a public transportation management system. It demonstrates a deep understanding of **dynamic memory management** and **complex linked list architectures**, specifically handling multiple intersecting data layers without using the C++ Standard Template Library (STL).



## 🏗️ Architectural Overview
The system is built using a hierarchical linked list structure:
* **Global Bus Lines:** A primary linked list of all bus lines in the system.
* **Global Stops:** A master list of all existing bus stops.
* **Per-Line Sub-lists:** Each bus line (`LineNode`) contains its own private linked lists for:
    * **Stops:** Specific stops assigned to that route.
    * **Buses:** Active buses and their respective drivers currently assigned to that line.

## 🚀 Key Features & Logic
* **Dynamic Node Management:** Implements sorted insertion and deletion for lines, stops, and buses based on unique IDs.
* **Cross-Reference Safety:** The system prevents the removal of a stop if it is currently "in use" by any active bus line, demonstrating data integrity logic.
* **Manual Memory Cleanup:** Features a comprehensive destructor that traverses and deallocates every nested node (Lines -> Buses/Stops) to ensure zero memory leaks.
* **Search & Filter Algorithms:** Includes functions to find all buses passing through a specific stop by traversing the entire multi-layered network.

## 🛠️ Tech Stack & Concepts
* **Language:** C++
* **Data Structures:** Multi-linked Lists, Nested Pointers, Dynamic Node Allocation.
* **Core Concepts:** Pointer Arithmetic, Memory Safety, Object-Oriented Design (OOD).

---
*Disclaimer: This repository is intended to serve as a personal portfolio. Direct copying of these solutions for academic submissions is a violation of the Bilkent University Honor Code.*
