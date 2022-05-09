#include "sat.h"

int main(int argc, char *argv[]) {

    clock_t begin = clock();
    srand(time(0));

    if (argc < 4) {
        puts("Input format : filename ; s for SAT or u for UNSAT ; solver number (1, 2 or 3) ; output filename (optional)");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    assert(f);

    clauseSet CS = init_clauseSet(600);

    read_DIMACS(&CS, f);
    // print_clauseSet(CS);
    remove_valid_clauses(&CS);
    // remove_clause(&CS, 0);
    // puts("");
    // print_clauseSet(CS);
    clauseSet cs2 = init_clauseSet(600);
    copy_cset(CS, &cs2);
    // puts("cs2 ; ");
    // print_clauseSet(cs2);





    bool SAT;
    modal m = init_combination(CS.tab[0].size);

    if (argv[3][0] == '3') {
        SAT = DPLL(CS, &m); // The set is being free inside the function
        // puts("\nDPLL");
    } else if (argv[3][0] == '1') {
        SAT = solver1(CS, &m);
        clear_cset(CS);
    } else {
        m = solver2(CS);
        if (is_null_modal(m)) SAT = false;
        else SAT = true;
        clear_cset(CS);
    }

    clock_t end = clock();

    if (SAT)
        puts("SAT");
    else
        puts("UNSAT");

    // print_modal(m);
    // bool check = check_set_modal(cs2, m);
    // if (check)
    //     puts("check");
    // else
    //     puts("not check");

    if (argv[2][0] == 's' || argv[2][0] == 'S')
        assert(SAT);
    else
        assert(!SAT);

    FILE *g;
    if (argc == 5) g = fopen(argv[4], "a");
    else g = fopen("Tests/time.time", "w");

    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    // fprintf(g, "%s, ", argv[1]); // Test's name
    fprintf(g, "%f\n", time_spent);

    free(m.tab);
    free(CS.tab);
    free(cs2.tab);
    fclose(f);
    return 0;
}