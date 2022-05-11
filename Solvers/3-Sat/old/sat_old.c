#include "../sat.h"

void add_clause_Cset(clauseSet *cs, clause c) {
    cs->tab[cs->size] = c;
    cs->size++;
}

clauseSet init_clauseSet(int clauseNum) {
    clauseSet CS;
    CS.tab = malloc(sizeof(clause) * (clauseNum + 1));
    CS.size = 0;
    return CS;
}

void print_clause(clause c) {
    printf("%d + ", c.tab[0]);
    printf("%d + ", c.tab[1]);
    printf("%d \n", c.tab[2]);
}

void print_clauseSet(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        print_clause(cs.tab[i]);
}

bool is_null_lit(literal l) {
    return l == 0;
}

bool is_null_clause(clause c) {
    for (int i = 0; i < CLAUSESIZE; i++)
        if (!is_null_lit(c.tab[i]))
            return false;
    return true;
}

clause init_null_clause() {
    clause c;
    c.size = CLAUSESIZE;
    c.valid = false;
    for (int i = 0; i < CLAUSESIZE; i++)
        c.tab[i] = init_literal();
    return c;
}

literal init_literal() {
    return (literal) 0;
}

int in_clause(literal l, clause c) {
    for (int i = 0; i < CLAUSESIZE; i++) {
        if (l == c.tab[i])
            return i;
    }
    return -1;
}

int neg_in_clause(literal l, clause c) {
    for (int i = 0; i < CLAUSESIZE; i++) {
        if ((abs(l) == abs(c.tab[i])) && ((l < 0 && c.tab[i] > 0) || (l > 0 && c.tab[i] < 0)))
            return i;
    }
    return -1;
}

int abs_in_clause(literal l, clause c) {
    for (int i = 0; i < CLAUSESIZE; i++) {
        if (abs(l) == abs(c.tab[i]))
            return i;
    }
    return -1;
}

void remove_literal(literal l, clause *c) {
    for (int i = 0; i < CLAUSESIZE; i++) {
        if (abs(l) == abs(c->tab[i]))
            c->tab[i] = init_literal();;
    }
    c->size--;
}

bool neg_in_clauseSet(literal l, clauseSet cs) {
    for (int i = 0; i < cs.size; i++) {
        if (neg_in_clause(l, cs.tab[i]) >= 0)
            return true;
    }
    return false;
}


void remove_clause(clauseSet *cs, int p) {
    for (int i = p; i < cs->size - 1; i++)
        cs->tab[i] = cs->tab[i + 1];
    cs->size--;
}

void remove_valid_clauses(clauseSet *cs) {
    for (int i = 0; i < cs->size; i++) {
        if (cs->tab[i].valid) {
//            puts("valid");
            remove_clause(cs, i);
            i--;
        }
    }
}


void copy_cset(clauseSet cs, clauseSet *cs2) {
    for (int i = 0; i < cs.size; i++) {
        cs2->tab[i] = init_null_clause();
        for (int j = 0; j < CLAUSESIZE; j++) {
            cs2->tab[i].tab[j] = cs.tab[i].tab[j];
        }
        cs2->size++;
    }
}

void copy_cset2(clauseSet cs, clauseSet *cs1, clauseSet *cs2) {
    for (int i = 0; i < cs.size; i++) {
        cs1->tab[i] = init_null_clause();
        cs2->tab[i] = init_null_clause();
        for (int j = 0; j < CLAUSESIZE; j++) {
            cs1->tab[i].tab[j] = cs.tab[i].tab[j];
            cs2->tab[i].tab[j] = cs.tab[i].tab[j];
        }
        cs1->size++;
        cs2->size++;
    }
}


void assign(literal l, clause *c, bool val) {
    int p = abs_in_clause(l, *c);
    if (p < 0) return;
    if ((val && c->tab[p] > 0) || (!val && c->tab[p] < 0))
        c->valid = true;
    c->tab[p] = init_literal();
    c->size--;
}

void assign_to_set(literal l, clauseSet *cs, bool val) {
    for (int i = 0; i < cs->size; i++)
        assign(l, &cs->tab[i], val);
//    remove_valid_clauses(cs);
}

bool is_unit_clause(clause c) {
    bool found1 = false;
    bool found2 = false;;
    for (int i = 0; i < CLAUSESIZE; i++) {
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
    return init_null_clause();
}

void unit_propagate(literal l, clauseSet *cs, linked *watched) {
    bool in = false;
    if (!is_null_lit(l)) {
        for (int i = 0; i < cs->size; i++) {
            if (in_clause(l, cs->tab[i]) >= 0)
                cs->tab[i].valid = true;
            if (neg_in_clause(l, cs->tab[i]) >= 0) {
                remove_literal(l, &cs->tab[i]);
            }
            if (!in && cs->tab[i].size == 1) {
//                add_to_linked(watched, cs->tab[i]);
//                puts("in if");
                node *n = init_node();
                n->c = cs->tab[i];
                watched->head = n;
                in = true;
            }
        }
        remove_valid_clauses(cs);
    }
}

bool is_pure_literal(literal l, clauseSet cs) {
    return !neg_in_clauseSet(l, cs);
}

literal find_pure_literal(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        for (int j = 0; j < CLAUSESIZE; j++)
            if (!is_null_lit(cs.tab[i].tab[j]) && is_pure_literal(cs.tab[i].tab[j], cs))
                return cs.tab[i].tab[j];
    return init_literal();
}

void pure_literal_assign(literal l, clauseSet *cs) {
    for (int i = 0; i < cs->size; i++)
        if (abs_in_clause(l, cs->tab[i]) >= 0)
            cs->tab[i].valid = true;
    remove_valid_clauses(cs);
}

literal first_non_null_literal(clause c) {
    for (int i = 0; i < CLAUSESIZE; i++)
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

bool DPLL(clauseSet cs, FILE *f, linked *watched) {
//    puts("int dpll");

    *watched = init_linked();

    literal l, l2;
    clause c;

    remove_valid_clauses(&cs);

    c = find_unit_clause(cs);
    while (!is_null_clause(c)) {
//        printf("in unit while with the clause : "); print_clause(c);
        l2 = first_non_null_literal(c);
        // assign_to_modal(m, l2.pos, !l2.negation);
//        fprintf(f, "%d ", l2);
        unit_propagate(l2, &cs, watched);

        if (watched->size > 0) {
            c = get_clause(*watched);
//            remove_head(watched);
        } else c = find_unit_clause(cs);
//        c = find_unit_clause(cs);
    }

//    free_linked(watched);


    l = find_pure_literal(cs);
    while (!is_null_lit(l)) {
//        printf("###########in pure while with the literal : %d\n", l);
//        print_clauseSet(cs);

        // assign_to_modal(m, l.pos, !l.negation);
//        fprintf(f, "%d ", l);
        pure_literal_assign(l, &cs);
        l = find_pure_literal(cs);
    }
//    puts("after pure");
//    print_clauseSet(cs);
    // remove_valid_clauses(&cs);


    if (is_empty_set(cs)) {
//        puts("is_empty_set");
        return true;
    }
    if (contains_empty_clause(cs)) {
//        puts("contains_empty_clause");
        return false;
    }

    l = first_non_null_literal_in_set(cs);


////// Copy at the same time
    clauseSet cs1 = init_clauseSet(cs.size);
    clauseSet cs2 = init_clauseSet(cs.size);
    copy_cset2(cs, &cs1, &cs2);

    assign_to_set(l, &cs1, true);
    bool d1 = DPLL(cs1, f, watched);
    free(cs1.tab);
    if (d1) {
        free(cs2.tab);
        return true;
    }

    assign_to_set(l, &cs2, false);
    bool d2 = DPLL(cs2, f, watched);
    free(cs2.tab);
    return d2;

//// 2 separate copies
//    clauseSet cs1 = init_clauseSet(cs.size);
//    copy_cset(cs, &cs1);
//    assign_to_set(l, &cs1, true);
//
//    bool d1 = DPLL(cs1, f, watched);
//    free(cs1.tab);
//    if (d1)
//        return true;
//
//    clauseSet cs2 = init_clauseSet(cs.size);
//    copy_cset(cs, &cs2);
//    assign_to_set(l, &cs2, false);
//
//    bool d2 = DPLL(cs2, f, watched);
//    free(cs2.tab);
//    return d2;
}



//bool DPLL(clauseSet cs, FILE *f, linked *watched, bool assign, literal l2, bool assignVal) {
//    puts("\n #### In dpll #### :");
//    printf("address of cs in dpll : %p\n", &cs);
//
//    if (assign) {
//        printf("assigning %d to %d : \n", l2, assignVal);
//        assign_to_set(l2, &cs, assignVal);
//    }
//
////    print_clauseSet(cs);
////    puts("###");
//
//    *watched = init_linked();
//
//    literal l;
//    clause c;
//
//    remove_valid_clauses(&cs);
//
//    c = find_unit_clause(cs);
//    while (!is_null_clause(c)){
////        printf("in unit while with the clause : "); print_clause(c);
//        l = first_non_null_literal(c);
//        // assign_to_modal(m, l2.pos, !l2.negation);
//        fprintf(f, "%d ", l);
//        unit_propagate(l, &cs, watched);
//
//        if (watched->size > 0) {
//            c = get_clause(*watched);
////            remove_head(watched);
//        }
//        else c = find_unit_clause(cs);
////        c = find_unit_clause(cs);
//    }
//
////    free_linked(watched);
//
//
//    l = find_pure_literal(cs);
//    while (!is_null_lit(l)) {
//        fprintf(f, "%d ", l);
//        pure_literal_assign(l, &cs);
//        l = find_pure_literal(cs);
//    }
//
//    if (is_empty_set(cs)) {
//        puts("is_empty_set");
//        return true;
//    }
//    if (contains_empty_clause(cs)){
//        puts("contains_empty_clause");
//        return false;
//    }
//
//    l = first_non_null_literal_in_set(cs);
//
//    bool d1 = DPLL(cs, f, watched, true, l, true);
//    if (d1)
//        return true;
//    else {
//        clauseSet cs2 = init_clauseSet(cs.size);
//        copy_cset(cs, &cs2);
//        bool d2 = DPLL(cs2, f, watched, true, l, false);
//        free(cs2.tab);
//        return d2;
//    }
//}