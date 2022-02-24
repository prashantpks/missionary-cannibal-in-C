# Missionary - Cannibal Problem 

This repository contains various search algorithms to solve missionary - cannibal problem in C language.

## Problem Statement
There are 3 missionaries and 3 cannibals on one side of the river. They need to cross the river through boat having maximum capacity 2 such that missionaries shouldn't be outnumbered by cannibals on either side of the river.

There is also a cost of travelling through boat i.e.
* For missionary: $10
* For cannibal: $20

Print the solution path along with cost to reach other side of the river.
## Solution

### Approach
The above problem can be solved by several search strategies. This repository contains solution involving 4 main search strategies in different C files.

* [misscan.c (Breadth First Search)](misscan.c)
* [misscan_dfs.c (Depth First Search)](misscan_dfs.c)
* [misscan_id.c (Iterative Deepening)](misscan_id.c)
* [misscan_ucs.c (Uniform Cost Search)](misscan_ucs.c)

### Language Used
C

### Output Result
These C programs will print the **solution path, path cost and nodes generated and expanded at each step.**

### Modifications

The charge to travel can be modified
```c
#define CANNIBAL_CHARGE 20
#define MISSIONARY_CHARGE 10
```

## Issues
* There are memory leaks as allocated heap variables aren't being unallocated.
* Output format can be improved
* New search strategies can be added to solve this, heuristic search strategies can be used.

## Author
* LinkedIn: [@Prashant Kumar](https://www.linkedin.com/in/prashant-kumar-7aa9a4203/)
* Email: [@prashant](mailto:prashantrkt2002@gmail.com)
* Github: [@prashantpks](https://github.com/prashantpks/)