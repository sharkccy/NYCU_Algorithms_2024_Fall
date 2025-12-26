# HW1 — Young Tableau Insert/Extract
StudentID: 110612117

Name: Chung-Yu Chang (張仲瑜)

Introduction:
 - Implements Young Tableau operations (insert and extract-min) for the Algorithm Analysis course exercise.
 - The C++ solution is provided in `Exercise1_110612117.cpp` and uses a rectangular matrix representation where `x` denotes an empty cell.

Files:
 - `Exercise#1 Spec.pdf`: Problem specification and input/output format description.
 - `Exercise1_110612117.cpp`: C++ source implementing insert and extract-min on a Young Tableau.
 - `input.txt`: Example input used by the program (test cases and tableaux).
 - `output.txt`: Program output produced after running the executable.
 - `Report.pdf`: A brief report discussing the implementation details and complexity analysis.

How to build
 - Compile with `g++` (Linux/macOS/WSL) or a compatible compiler:

```bash
g++ hw1/Exercise1_110612117.cpp -O2 -std=c++17 -o hw1/Exercise1
```

How to run
 - Run the program redirecting input (the program reads `input.txt` by filename by default):

```bash
./hw1/Exercise1
# or on Windows PowerShell
./hw1/Exercise1.exe
```

 - The program reads test cases from `input.txt` and writes results to `output.txt`.

Notes:
 - The implementation uses a large sentinel (`LONG_MAX`) to represent empty cells (`x`).
 - The program supports two operation codes: `1` for Insert, `2` for Extract-min, matching the exercise specification.

Contact / Author:
 - Chung-Yu Chang (張仲瑜)
