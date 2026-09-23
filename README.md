# tic-tac-toe
Object-oriented Tic-Tac-Toe engine in the terminal using the Minimax algorithm with heuristic optimizations.

## Build and Usage
Build the project using CMake:
```bash
cmake -B build
cmake --build build
```
Execution:
```bash
./build/tic-tac-toe
```

## Features
- Minimax with Alpha-Beta Pruning (BnB optimization which cuts off useless state evaluations in the game tree)
- Supports arbitrary board sizes ($N \ge 3$) and winning sequence lengths ($k \le N$)
- Limited depth search

