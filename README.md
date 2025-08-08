# A\* Routing Algorithm

This project implements the A\* (A-star) routing algorithm in C++, designed to find the shortest path between nodes in a graph. It features a custom graph representation, a min-heap for the open set, and a binary search tree for the closed set.

## Features

* **Graph Representation**: Directed or undirected weighted graph implementation in `Graph.h`.
* **A* Algorithm*\*: Heuristic-based pathfinding implementation in `AstarAlgo.h`.
* **Min-Heap**: Custom priority queue for the open list in `MinHeap.h`.
* **Binary Search Tree**: Efficient closed-list management in `BinarySearchTree.h`.
* **Flexible Input**: Load vertices and edges from plain-text files.

## File Structure

```
├── AstarAlgo.h         # A* algorithm implementation
├── BinarySearchTree.h  # Closed set implementation
├── Graph.h             # Graph data structures and helpers
├── MinHeap.h           # Open set priority queue
├── main.cpp            # Application entry point and I/O handling
├── vertex list.txt     # List of vertices (node coordinates or labels)
├── input.txt           # Edge definitions and heuristic parameters
└── README.md           # Project documentation (this file)
```

## Requirements

* C++11 or later
* Standard C++ STL library
* Make (optional)

## Building

1. **Using g++ directly**:

   ```bash
   g++ -std=c++11 main.cpp -o astar
   ```

2. **Using Makefile** (if provided)

   ```bash
   make
   ```

## Usage

Run the executable with two input files:

```bash
./astar <vertex_list_file> <edge_list_file>
```

For example:

```bash
./astar "vertex list.txt" "input.txt"
```

The program outputs the shortest path and total cost from the start node to the goal node specified in the input.

## Input Format

### Vertex List (`vertex list.txt`)

Each line represents a vertex with an identifier and optional coordinates:

```
A 0 0
B 1 0
C 1 1
...
```

* **ID**: Unique label for the node.
* **Coordinates** (optional): Used by heuristic (e.g., Euclidean distance).

### Edge List (`input.txt`)

First line: start and goal node IDs.
Subsequent lines: edges in the format `source target cost`:

```
A C        # start=A, goal=C
A B 1.5
B C 2.0
A C 3.2
```

## Sample Output

```
Shortest path: A -> B -> C
Total cost: 3.5
```

## Tests and Examples

Include additional test cases in the `tests/` directory (not provided) or use the sample files to verify correctness.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
