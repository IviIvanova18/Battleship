#include "sat.h"

#define MAXITERATIONS 100000
#define P 0.5

modal solver2(clauseSet cs) {
    int i = 0;
    double x;
    bool foundModal = false;
    literal l;
    clause cl;
    clauseSet cs2;
    combination c = random_combination(cs.tab[0].size);
    while (!foundModal && i < MAXITERATIONS) {
        cs2 = false_set(cs, c);
        if (cs2.size > 0) cl = random_false_clause(cs2, c);
        else return c;

        x = random_min_max(0, 1);
        if (x <= P) l = random_literal(cl);
        else l = deterministic(cl, cs, c);

        c.tab[l.pos] = 1 - c.tab[l.pos];
        foundModal = check_set_modal(cs, c);
        i++;
    }
    foundModal = check_set_modal(cs, c);

    free(cs2.tab);
    if (foundModal) return c;
    else return null_modal();
}

int number(literal l, clauseSet cs, bool positive) {
    int count = 0, p;
    for (int i = 0; i < cs.size; i++) {
        if (!cs.tab[i].valid) {
            p = in_clause(l, cs.tab[i]);
            if (p != -1) {
                if (positive) {
                    if (cs.tab[i].tab[p].name > 0) count++;
                    else {
                        if (cs.tab[i].tab[p].name < 0) count++;
                    }
                }
            }

        }
    }
    return count;
}

int score(literal l, clauseSet cs, combination c) {
    if (c.tab[l.pos] == 1)
        return abs(number(l, cs, false) - number(l, cs, true));
    else
        return abs(number(l, cs, true) - number(l, cs, false));
}

literal max_score(clause cl, clauseSet cs, combination c) {
    literal l;
    int s, max = 0;
    for (int i = 0; i < cl.size; i++) {
        s = score(cl.tab[i], cs, c);
        // printf("s : %d\n", s);
        if (s > max) {
            max = s;
            l = cl.tab[i];
        }
    }
    return l;
}

/* For now it's just calling max_score(), but if we add new determination methods, it will change */
literal deterministic(clause cl, clauseSet cs, combination c) {
    return max_score(cl, cs, c);
}
