#include "sat.h"

bool check_modal(clause c, modal m) {
    for (int i = 0; i < c.size; i++) {
        if (!is_null_lit(c.tab[i])) {
            if (m.tab[i] == 1) {
                if (!c.tab[i].negation)
                    return true;
            } else {
                if (c.tab[i].negation)
                    return true;
            }
        }
    }
    return false;
}

bool check_set_modal(clauseSet cs, modal m) {
    for (int i = 0; i < cs.size; i++)
        if (!cs.tab[i].valid && !check_modal(cs.tab[i], m))
            return false;
    return true;
}

modal find_modal(clause c, combination cb) {
    while (!check_modal(c, cb)) {
        if (all_one(cb))
            return null_modal(c.size);
        inc(&cb);
    }
    return cb;
}

combination init_combination(int varNum) {
    combination c;
    c.size = varNum;
    c.tab = malloc(sizeof(int) * varNum);
    for (int i = 0; i < varNum; i++)
        c.tab[i] = 0;
    return c;
}

combination random_combination(int varNum) {
    combination c;
    c.size = varNum;
    c.tab = malloc(sizeof(int) * varNum);
    for (int i = 0; i < varNum; i++)
        c.tab[i] = rand() % 2;
    return c;
}

void inc(combination *cb) {
    for (int i = cb->size - 1; i >= 0; i--) {
        cb->tab[i] = (cb->tab[i] + 1) % 2;
        if (cb->tab[i] != 0)
            break;
    }
}

bool all_one(combination cb) {
    for (int i = 0; i < cb.size; i++)
        if (cb.tab[i] != 1)
            return false;
    return true;
}

modal null_modal(int varNum) {
    modal m;
    m.size = varNum;
    m.tab = malloc(sizeof(int) * varNum);
    for (int i = 0; i < varNum; i++)
        m.tab[i] = -1;
    m.size = varNum;
    return m;
}

bool is_null_modal(modal m) {
    for (int i = 0; i < m.size; i++)
        if (m.tab[i] != -1)
            return false;
    return true;
}