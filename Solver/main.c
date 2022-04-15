#include "sat.h"

int main(int argc, char *argv[]) {

    // clock_t begin = clock();
    srand(time(0));

    if (argc < 4) {
        puts("Input format : filename ; s for SAT or u for UNSAT ; solver number (1, 2 or 3)");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    assert(f);

    clauseSet CS = init_clauseSet(600);

    read_DIMACS(&CS, f);
    remove_valid_clauses(&CS);
    fclose(f);

    // bool SAT = sat(CS);
    // m = solver2(CS);
    // if (argv[3][0] == '1')
    //     SAT = sat(CS);
    // else 
    
    // bool SAT = true;    
    // modal m = solver2(CS);
    // if (is_null_modal(m)) SAT = false;
    
    modal m = init_combination(CS.tab[0].size);
    bool SAT = DPLL(CS, &m);

    if (SAT)
        puts("SAT");
    else
        puts("UNSAT");

    print_modal(m);

    // if (argv[2][0] == 's' || argv[2][0] == 'S')
    //     assert(SAT);
    // else 
    //     assert(!SAT);

    // clock_t end = clock();
    // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    // printf("Time : %f\n", time_spent);

    // free(m.tab);
    // clear_cset(CS);
    free(CS.tab);
    return 0;
}