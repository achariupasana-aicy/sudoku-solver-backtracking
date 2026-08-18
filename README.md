# Sudoku Solver Using Backtracking & MRV

A C-based Sudoku solver that solves 9×9 Sudoku puzzles using **recursive backtracking** and compares the standard approach with an optimized **Minimum Remaining Values (MRV)** heuristic.

## 🚀 Features

* Solves 9×9 Sudoku puzzles using backtracking
* Validates the initial Sudoku configuration
* Checks rows, columns, and 3×3 boxes before placing values
* Uses recursion for systematic search
* Implements **MRV (Minimum Remaining Values)** optimization
* Measures execution time
* Counts recursive calls
* Compares standard backtracking with optimized backtracking

## 🛠️ Technologies

* **Language:** C
* **Concepts:** Recursion, Backtracking, Constraint Satisfaction
* **Optimization:** Minimum Remaining Values (MRV)
* **Libraries:** stdio.h, stdbool.h, time.h

## 🧠 Algorithm

### Standard Backtracking

The algorithm:

1. Finds an empty cell.
2. Tries numbers from 1 to 9.
3. Checks whether the number is valid.
4. Places the number if valid.
5. Recursively solves the remaining puzzle.
6. Backtracks when no valid solution is possible.

### MRV Optimization

The optimized version uses the **Minimum Remaining Values** heuristic.

Instead of selecting the first empty cell, it selects the empty cell having the **fewest possible candidate values**.

This reduces unnecessary search and can significantly reduce the number of recursive calls.

## 📊 Performance Analysis

The program compares:

| Algorithm             | Cell Selection               | Optimization |
| --------------------- | ---------------------------- | ------------ |
| Standard Backtracking | First empty cell             | None         |
| MRV Backtracking      | Cell with minimum candidates | MRV          |

The program records:

* Execution time
* Number of recursive calls

These measurements demonstrate the practical performance difference between the two approaches.

## ▶️ How to Run

### Compile

```bash
gcc sudoku_solver.c -o sudoku_solver
```

### Run

**Windows:**

```bash
sudoku_solver.exe
```

**Linux/macOS:**

```bash
./sudoku_solver
```

## 📁 Project Structure

```text
sudoku-solver-backtracking/
│
├── sudoku_solver.c
├── README.md
├── .gitignore
└── LICENSE
```

## 📌 Concepts Demonstrated

* Recursion
* Backtracking
* Constraint satisfaction
* Algorithm optimization
* Heuristics
* Performance analysis
* 2D arrays
* Boolean logic
* Input validation
* Time complexity analysis

## 🔮 Future Improvements

* Add a graphical user interface
* Allow users to enter their own Sudoku puzzles
* Add multiple solving strategies
* Implement bitmask-based optimization
* Add puzzle difficulty detection
* Display solving steps
* Compare additional heuristics such as degree heuristic and least-constraining value
