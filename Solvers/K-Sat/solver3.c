#include "sat.h"

void assign(literal l, clause *c, bool val) {
    if ((val && c->tab[l.pos].name > 0) || (!val && c->tab[l.pos].name < 0))
        c->valid = true;
    c->tab[l.pos] = init_literal();
}

void assign_to_set(literal l, clauseSet *cs, bool val) {
    for (int i = 0; i < cs->size; i++)
        assign(l, &cs->tab[i], val);
    remove_valid_clauses(cs);
}

bool is_unit_clause(clause c) {
    bool found1 = false;
    bool found2 = false;;
    for (int i = 0; i < c.size; i++) {
        if (!is_null_lit(c.tab[i])) {
            if (found1) found2 = true;
            else found1 = true;
        }
    }
    return !found2;
}

bool is_empty_set(clauseSet cs) {
    return cs.size == 0;
}

bool contains_empty_clause(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        if (is_null_clause(cs.tab[i]))
            return true;
    return false;
}

clause find_unit_clause(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        if (is_unit_clause(cs.tab[i]))
            return cs.tab[i];
    return init_null_clause(cs.tab[0].size);
}

void unit_propagate(literal l, clauseSet *cs) {
    if (!is_null_lit(l)) {
        for (int i = 0; i < cs->size; i++) {
            if (in_clause2(l, cs->tab[i]) >= 0)
                cs->tab[i].valid = true;
            if (neg_in_clause(l, cs->tab[i]))
                cs->tab[i].tab[l.pos] = init_literal();
        }
        remove_valid_clauses(cs);
    }
}

bool is_pure_literal(literal l, clauseSet cs) {
    return !neg_in_clauseSet(l, cs);
}

literal find_pure_literal(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        for (int j = 0; j < cs.tab[i].size; j++)
            if (!is_null_lit(cs.tab[i].tab[j]) && is_pure_literal(cs.tab[i].tab[j], cs))
                return cs.tab[i].tab[j];
    return init_literal();
}

void pure_literal_assign(literal l, clauseSet *cs) {
    for (int i = 0; i < cs->size; i++)
        if (in_clause(l, cs->tab[i]) >= 0)
            remove_clause(cs, i);
}

literal first_non_null_literal(clause c) {
    for (int i = 0; i < c.size; i++)
        if (!is_null_lit(c.tab[i]))
            return c.tab[i];
    return init_literal();
}

literal first_non_null_literal_in_set(clauseSet cs) {
    for (int i = 0; i < cs.size; i++) {
        literal l = first_non_null_literal(cs.tab[i]);
        if (!is_null_lit(l))
            return l;
    }
    return init_literal();
}

void assign_to_modal(modal *m, int pos, bool val) {
    if (val)
        m->tab[pos] = 1;
    else
        m->tab[pos] = 0;
}


bool DPLL(clauseSet cs, modal *m) {
    literal l = init_literal(), l2, l3;
    clause c;

    remove_valid_clauses(&cs);
    c = find_unit_clause(cs);
    while (!is_null_clause(c)) {
        l2 = first_non_null_literal(c);
        assign_to_modal(m, l2.pos, !l2.negation);
        unit_propagate(l2, &cs);
        c = find_unit_clause(cs);
    }

    l = find_pure_literal(cs);
    while (!is_null_lit(l)) {
        assign_to_modal(m, l.pos, !l.negation);
        pure_literal_assign(l, &cs);
        l = find_pure_literal(cs);
    }

    if (is_empty_set(cs))
        return true;
    if (contains_empty_clause(cs))
        return false;

    l = first_non_null_literal_in_set(cs);

    clauseSet cs1 = init_clauseSet(cs.size);
    copy_cset(cs, &cs1);
    assign_to_set(l, &cs1, true);
    assign_to_modal(m, l.pos, true);

    bool d1 = DPLL(cs1, m);
    free(cs1.tab);
    if (d1)
        return true;

    clauseSet cs2 = init_clauseSet(cs.size);
    copy_cset(cs, &cs2);
    assign_to_set(l, &cs2, false);
    assign_to_modal(m, l.pos, false);

    bool d2 = DPLL(cs2, m);
    free(cs2.tab);
    return d2;
}