# Sat-solvers

## How to use

- To run with a specific DIMACS file:
    ```
    make
    ./test_sat filename x n output-filename
    ```
    - `filename`: name of the DIMACS file
    - `x`: expected output (s for SAT and u for UNSAT)
    - `n`: solver number (1, 2 or 3)
    - `output-filename`: an optional argument, used to print the run time

- Example:
    ```
    make
    ./test_sat Tests/exemple.cnf s 3
    ```

## Solvers

### Solver 1

A "stupid" solver, tries every combination until a correct modal is found.

### Solver 2

Uses the WalkSat algorithm.

### Solver 3

DPLL.

## Tests

- To run all satisfiable tests:
  ```make tests_sat```
- To run all unsatisfiable tests: (Not recommended with solver1, running times can be extremly long...)
  ```make tests_unsat```
- To run all 'simple' unsatisfiable tests: (The simple tests are the size of the exercices done in class)
  ```make tests_unsat```

- To run all tests:
  ```make test_all```

#### Output:

If the test is successful, only it's name will be printed.
Otherwise, the assert function will stop the program.

#### Format of test files:

DIMACS

## Comparison

Average time on 1000 satisfiable tests (20 variables and 91 clauses):

- Solver1 : 0.089728s
- Solver2 : 1.860959s
- Solver3 : 0.002850s