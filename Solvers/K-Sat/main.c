#include "sat.h"

int main(int argc, char *argv[]) {

    clock_t begin = clock();
    srand(time(0));

    if (argc < 5) {
        puts("Input format : filename ; s for SAT or u for UNSAT ; solver number (1, 2 or 3) ; output filename .model ; output filename .time (optional)");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    assert(f);

    FILE *g = fopen(argv[4], "w");
    assert(g);

    clauseSet CS = init_clauseSet(MAXSIZE);

    read_DIMACS(&CS, f);
    remove_valid_clauses(&CS);

//    clauseSet cs2 = init_clauseSet(CS.size);
//    copy_cset(CS, &cs2);

    bool SAT;
    modal m = init_combination(CS.tab[0].size);

    if (argv[3][0] == '3') {
        SAT = DPLL(CS, &m); // The set is being free inside the function
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

    print_modal2(m, g);
//    bool check = check_set_modal(cs2, m);
//    if (check)
//        puts("check");
//    else
//        puts("not check");

    if (argv[2][0] == 's' || argv[2][0] == 'S')
        assert(SAT);
    else
        assert(!SAT);

    FILE *h;
    if (argc == 6) h = fopen(argv[5], "a");
    else h = fopen("../Tests/Times/default.time", "w");

    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    // fprintf(h, "%s, ", argv[1]); // Test's name
    fprintf(h, "%f\n", time_spent);

    free(m.tab);
    free(CS.tab);
    fclose(f);
    fclose(g);
    fclose(h);
    return 0;
}