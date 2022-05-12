# Battleship

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [To execute](#to-execute)
* [Logic](#logic)
* [Sat-solvers](#sat-solvers)
* [Graphics](#graphics)

## General info

Battleships also known as Bimaru is a logic puzzle. This project consists in using a SAT-solver to automatically solve the Battleship puzzle given different grid sizes and boat counts. For further information and all the logical formulas used for solving, the puzzle see the [pdf file]{Battleships.pdf}. For more information about the game itself, you can find [here](https://en.wikipedia.org/wiki/Battleship_(puzzle))

## Technologies
Project is created with:
* C
* Python3

## To execute

Getting started:

```
git clone https://github.com/IviIvanova18/Battleship.git
cd BattleShip
```

To execute all the components at the same time using the graphical interface:


```./run_final.sh Tests/{LxH}_games/game{LxH}_{i}.in```

Remark: Before the first execution:
```chmod +x run_final.sh```

To execute all the components at the same time without the graphical interface:


```./run.sh Tests/{LxH}_games/game{LxH}_{i}.in```

Remark: Before the first execution:
```chmod +x run.sh```


Following :
- `{LxH}`: The size of the grid
- `i`: the number of the game test 

- Example:
```./run_final.sh Tests/4x4_games/game4x4_1.in```

Remark: the most performant grid is of size 4x4

  
## Logic

The logical part is the main part of the game. It consists of modeling the problem in conjunctive normal form (product of clauses).

## Sat-solvers

### The Solvers

There are 2 solver categories, K-Sat and 3-Sat.

#### K-Sat

##### Solver 1

A "stupid" solver, tries every combination until a correct modal is found.

##### Solver 2

Uses the WalkSat algorithm.

##### Solver 3

DPLL solver.

#### 3-Sat

DPLL solver.
Can only be used with 3-Sat DIMACS files, so **always convert before running**.

### K-Sat to 3-Sat

- To run with a specific DIMACS file:
    ```
    make satTo3Sat
    ./satTo3Sat filename output-filename
    ```
    - `filename`: name of the DIMACS file
    - `output-filename`: name of the new DIMACS file, will be written in the 3-Sat format

- Example:
    ```
    make satTo3Sat
    ./satTo3Sat ../Tests/exemple.cnf ../Tests/exemple_3sat.cnf 
    ```

### How to use (K-Sat solvers)

- Go to ```Solvers/K-Sat/```
- To run with a specific DIMACS file:
    ```
    make
    ./main filename x n output-filename
    ```
    - `filename`: name of the DIMACS file
    - `x`: expected output (s for SAT and u for UNSAT)
    - `n`: solver number (1, 2 or 3)
    - `output-filename`: an optional argument, used to print the run time

- Example:
    ```
    make
    ./main ../Tests/exemple.cnf s 3
    ```

### How to use (3-Sat solver)

Can only be used with 3-Sat DIMACS files, so **always convert before running**.

- Go to ```Solvers/3-Sat/```
- To run with a specific DIMACS file:
    ```
    make
    ./main filename x
    ```
    - `filename`: name of the DIMACS file
    - `x`: expected output (s for SAT and u for UNSAT)

- Example:
    ```
    make
    ./test_sat ../Tests/exemple_3sat.cnf s
    ```

### Tests

(Most tests were taken from : https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html)

#### 3-Sat:

To run the tests go to ```Solvers/3-Sat/```

- To run all satisfiable tests:
  ```make tests_sat```
- To run all unsatisfiable tests: (Not recommended with solver1, running times can be extremely long...)
  ```make tests_unsat```
- To run all 'simple' unsatisfiable tests: (The simple tests are the size of the exercises done in class)
  ```make tests_unsat```
- To run all tests:
  ```make test_all```

#### K-Sat:

To run the tests go to ```Solvers/K-Sat/```

##### Solver3:

- To run all satisfiable tests:
  ```make tests_sat3```
- To run all unsatisfiable tests:
  ```make tests_unsat3```

##### Others:

- To run all 'simple' tests:
  ```make test_simple```  
  (The simple tests are the size of the exercises done in class)  
  This will run all 'simple' tests (sat and unsat) with the 3 solvers

We do not recommend running more complicated tests on solver 1 and 2, since solving times can be extremely long...

##### Output:

If the test is successful, only its name will be printed.
Otherwise, the assert function will stop the program.

##### Format of test files:

DIMACS

### Comparison

#### Average time on 1000 satisfiable tests (20 variables and 91 clauses):

- Solver1 : **0.089728s**
- Solver2 : **1.860959s**
- Solver3 : **0.002850s**

#### Average times for Solver3 (DPLL with K-Sat)

- 1000 satisfiable tests (50 variables and 218 clauses): **0.517483s**
- 1000 unsatisfiable tests (50 variables and 218 clauses): **0.728277s**

#### Average times for Solver4 (DPLL with 3-Sat)

- 1000 satisfiable tests (20 variables and 91 clauses): **0.000461s**
- 1000 satisfiable tests (50 variables and 218 clauses): **0.015077s**
- 1000 unsatisfiable tests (50 variables and 218 clauses): **0.040009s**
- 100 satisfiable tests (75 variables and 325 clauses): **0.212419s**
- 100 unsatisfiable tests (75 variables and 325 clauses): **0.544030s**
- 100 satisfiable tests (100 variables and 430 clauses): **2.549836s**

## Graphics

### Prerequisites

The graphical interface of Battleship is using python's library Tkinter.
`Python3` is required to run the graphics

### How to use

To execute only the graphics:

* On windows:
```python3 .\Graphics\graphics.py .\Tests\{LxH}_games\game{LxH}_{i}.in .\Tests\{LxH}_games\game{LxH}_{i}.solution```

* On linux :
```pyton3 ./Graphics/graphics.py Tests/{LxH}_games/game{LxH}_{i}.in ./Tests/{LxH}_games/game{LxH}_{i}.solution```

Following :
- `{LxH}`: The size of the grid
- `i`: the number of the game test 



