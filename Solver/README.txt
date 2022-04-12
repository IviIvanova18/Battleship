Super Basic Sat-solver

    To run with a specific DIMACS file:
        'make'
        './test_sat filename x' <- with x the expected output (s for SAT and u for UNSAT)

    Example: 
        make
        ./test_sat Tests/exemple.cnf s

    To run all satisfiable tests:
        'make tests_sat'

    To run all unsatisfiable tests: (Not recommended, running time may exceed ...)
        'make tests_unsat'

    To run all 'simple' unsatisfiable tests: (The simple tests are the size of the exercices done in class)
        'make tests_unsat'

    To run all tests:
        'make test_all'

    Output:
        If the test is successful, only it's name will be printed.
        Otherwise, the assert function will stop the program.

    Format of test files: DIMACS