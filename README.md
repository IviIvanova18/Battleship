# Battleship

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [To execute](#to-execute)
* [Logic](#logic)
* [Sat-solvers](#sat-solvers)
* [Graphics](#graphics)

## General info

Battleships also known as Bimaru is a logic puzzle. This project consists in using a SAT-solver to automatically solve the Battleship puzzle given different grid sizes and boat count. For further information and all the logical formulas used for solvig the puzzle see the pdf file in the main folder. For more information about the game itself you can find [here](https://en.wikipedia.org/wiki/Battleship_(puzzle))

## Technologies
Project is created with:
* C
* Python3

## To execute

To execute all the components at the same time:

```./run_final.sh Tests/{LxH}_games/game{LxH}_{i}.in```

Following :
- `{LxH}`: The size of the grid
- `i`: the number of the grid

- Example:
```./run_final.sh Tests/4x4_games/game4x4_1.in```

	
## Logic

TO DO ..

## Sat-solvers

### How to use

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

### Solvers

#### Solver 1

A "stupid" solver, tries every combination until a correct modal is found.

#### Solver 2

Uses the WalkSat algorithm.

#### Solver 3

DPLL.

### Tests

- To run all satisfiable tests:
  ```make tests_sat```
- To run all unsatisfiable tests: (Not recommended with solver1, running times can be extremly long...)
  ```make tests_unsat```
- To run all 'simple' unsatisfiable tests: (The simple tests are the size of the exercices done in class)
  ```make tests_unsat```

- To run all tests:
  ```make test_all```

##### Output:

If the test is successful, only it's name will be printed.
Otherwise, the assert function will stop the program.

##### Format of test files:

DIMACS

### Comparison

Average time on 1000 satisfiable tests (20 variables and 91 clauses):

- Solver1 : 0.089728s
- Solver2 : 1.860959s
- Solver3 : 0.002850s

Average time for solver3 on 883 unsatisfiable tests (50 variables and 218 clauses):
- 0.728277s

## Graphics

### Prerequisites

The graphical interface of Battleship is using python's library Tkinter.
`Python3` is required to run the graphics

### How to use

To execute only the graphics:

* On windows:
```python3 .\Graphics\graphics.py .\Tests\{LxH}_games\game{LxH}{i}.in .\Tests\{LxH}_games\game{LxH}{i}.solution```

* On linux :
```pyton3 ./Graphics/graphics.py Tests/{LxH}_games/game{LxH}{i}.in ./Tests/{LxH}_games/game{LxH}{i}.solution```

Following :
- `{LxH}`: The size of the grid
- `i`: the number of the grid



