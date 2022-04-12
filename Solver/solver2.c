#include "sat.h"

#define MAXITERATIONS 1000000
#define P 0.5

modal solver2(clauseSet cs) {
    int i = 0;
    double x;
    bool foundModal = false;
    literal l;
    clause cl;
    // for (int i = 0; i < cs.size; i++)
    //     printf("l.pos : %d \n", cs.tab[i].tab[1].pos);
    clauseSet cs2;
    combination c = random_combination(cs.tab[0].size);
    // puts("passed random comb");
    while (!foundModal && i < MAXITERATIONS) {
        cs2 = false_set(cs, c);
        // puts("passed false set");
        if (cs2.size > 0) {
            cl = random_false_clause(cs2, c);
            // puts("passed random_false_clause");
        } else {
            return c;
        }

        x = random_min_max(0, 1);
        // printf("x : %f\n", x);
        // puts("passed random_x");
        if (x <= P) {
            l = random_literal(cl);
            // puts("passed random literal");
        }
        else {
            l = deterministic(cl, cs, c);
            // puts("passed deterministic literal");
        } 
        // printf("l.pos : %d\n", l.pos);
        // printf("abs(l.name) - 1 : %d\n", abs(l.name) - 1);
        // printf("c.tab[l.pos] : %d\n", c.tab[abs(l.name) - 1]);
        c.tab[l.pos] = 1 - c.tab[l.pos];
        // puts("passed inverting");
        foundModal = check_set_modal(cs, c);
        // puts("passed check_set_modal");
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
        // if (cs.tab[i].valid) puts("Valid");
        if (!cs.tab[i].valid) {
            p = in_clause(l, cs.tab[i]);
            if (p != -1) {
                if (positive)
                    if (cs.tab[i].tab[p].name > 0) count++;
                else 
                    if (cs.tab[i].tab[p].name < 0) count++;
            }

        }
    }
    // printf("In number : count : %d\n", count);
    return count;
}

int score(literal l, clauseSet cs, combination c) {
    // printf("In score : lit : %d ; pos : %d\n", l.name, l.pos);
    if (c.tab[l.pos] == 1)
        return abs(number(l, cs, false) - number(l, cs, true));
    else 
        return abs(number(l, cs, true) - number(l, cs, false));
}

literal max_score(clause cl, clauseSet cs, combination c) {
    // puts("\n###### IN max score ########");
    // print_clause(cl);
    // print_clauseSet(cs);
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
    // printf("lit : %d ; pos : %d\n", l.name, l.pos);
    return l;
}

/* For now it's just calling max_score(), but if we add new determination methods, it will change */
literal deterministic(clause cl, clauseSet cs, combination c) {
    return max_score(cl, cs, c);
}
