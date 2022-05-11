#include "types.h"
#include "sat.h"
#include "dimacs.h"

int main(int argc, char const *argv[]) {

    if (argc < 3) {
        puts("Input format: filename ; s for SAT or u for UNSAT");
        return 1;
    }

    FILE *h = fopen("time.time", "a");
    assert(h);

    clock_t begin = clock();
    srand(time(0));

    FILE *f = fopen(argv[1], "r");
    assert(f);

    int varNum, clauseNum;

    remove_comments(f);
    read_p_line(f, &varNum, &clauseNum);
    clauseSet cs = init_clauseSet(clauseNum);
    read_DIMACS(&cs, clauseNum, f);

    bool SAT = DPLL(cs);

    clock_t end = clock();

    if (SAT)
        puts("SAT");
    else
        puts("UNSAT");

    if (argv[2][0] == 's' || argv[2][0] == 'S')
        assert(SAT);
    else
        assert(!SAT);

    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
//     fprintf(g, "%s, ", argv[1]); // Test's name
    fprintf(h, "%f\n", time_spent);

    free(cs.tab);
    fclose(f);
    fclose(h);
    return 0;
}