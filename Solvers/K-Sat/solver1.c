#include "sat.h"

bool solver1(clauseSet cs, combination *c) {
    // simpli_cset(&cs);
    int j;
    bool all_good = false;
    while (!all_good) {
        all_good = true;
        for (int i = 0; i < cs.size; i++) {
            if (!cs.tab[i].valid) {
                if (!check_modal(cs.tab[i], *c)) {
                    all_good = false;
                    break;
                }
            }
        }
        if (all_one(*c))
            return false;
        if (!all_good) // So the modal is not increased after finding the right one
            inc(c);

    }
    // printf("Final modal %d : ", counter); print_modal(*c);
    // free(c.tab);
    return true;
}



/* Not in use */

/* ! ! ! ! ! !
 * since same_name is true even for p and -p, 
 * the simplified version will be wrong in the case of p + -p
 * but it will be set as valid so it will just get removed by simpli_cset
 */
clause simpli(clause c) {
    clause dejaVu = init_null_clause(c.size); // TODO could be pa problem 
    for (int i = 0; i < c.size; i++) {
        int p = in_clause(c.tab[i], dejaVu);
        if (p == -1)// Not in set
            add_l_clause(&dejaVu, c.tab[i]);
        else {
            if ((dejaVu.tab[p].negation + c.tab[i].negation) == 1) { // One of them is 0 and one is 1
                dejaVu.valid = true;
                return dejaVu;
            }
        }
    }
    return dejaVu;
}

void simpli_cset(clauseSet *cs) {
    for (int i = 0; i < cs->size; i++)
        cs->tab[i] = simpli(cs->tab[i]);
}