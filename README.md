# 📊 Algorithm Performance Analysis: K-Closest Elements

This repository contains an empirical performance analysis of different search algorithms. The objective of this project is to implement, benchmark, and theoretically analyze algorithms that find the **$K$ closest elements** to a target value within a sorted array.

## 🎯 Project Overview
Instead of relying solely on theoretical time complexities, this project actively measures the real-world execution time (in milliseconds) of three distinct search algorithms under varying workloads (array sizes from $N=2^3$ to $2^{15}$ and different $K$ proportions). 

The implemented algorithms include:
1. **Linear Search ($O(N)$):** Iterates through the array to find the target and expands linearly.
2. **Binary Search ($O(\log N)$):** Utilizes the divide-and-conquer approach to locate the target position before expanding to find the $K$ closest values.
3. **Jump Search ($O(\sqrt{N})$):** Jumps ahead by optimal block sizes ($m = \sqrt{N}$) to find the bounds, followed by a linear scan.

## 📈 Benchmarking & Analysis
The core of this project is the benchmarking engine (`main.cpp`), which dynamically generates test cases, prevents caching biases, and calculates the precise elapsed time using the C++ `<ctime>` library. 

* **Testing Scale:** Averaged over 50,000 repetitions per algorithm to ensure statistical significance and eliminate CPU spike anomalies.
* **Analysis Report:** A comprehensive PDF report (`Report.pdf`) is included in this repository. It features:
  * Detailed tables of raw execution times.
  * Plotted performance graphs visualizing the scalability of Linear vs. Binary vs. Jump search.
  * A comparative discussion matching the empirical results against the theoretical Big-O expectations.

## 🛠️ Tech Stack
* **Language:** C++
* **Key Concepts:** Algorithm Design, Performance Benchmarking, Time Complexity Analysis, Array Manipulation.

---
*Disclaimer: This repository is intended to serve as a personal portfolio. Direct copying of these solutions for academic submissions is a violation of the Bilkent University Honor Code.*
