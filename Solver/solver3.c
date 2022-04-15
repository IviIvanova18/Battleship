#include "sat.h"

void assign(literal l, clause *c, bool val) {
    if ((val && l.name > 0 && c->tab[l.pos].name > 0) || (!val && l.name < 0 && c->tab[l.pos].name < 0))
        c->valid = true;
    c->tab[l.pos] = init_literal();
}

void assign_to_set(literal l, clauseSet *cs, bool val) {
    for (int i = 0; i < cs->size; i++)
        assign(l, &cs->tab[i], val);
}

clauseSet assign_to_new_set(literal l, clauseSet cs, bool val) {
    clauseSet cs2 = init_clauseSet(cs.size);
    for (int i = 0; i < cs.size; i++)
        assign(l, &cs2.tab[i], val);
    return cs2;
}

bool is_empty_clause(clause c) {
    return c.size == 0;
}

bool is_unit_clause(clause c) {
    return c.size == 1;
}

bool is_empty_set(clauseSet cs) {
    return cs.size == 0;
}

bool contains_empty_clause(clauseSet cs) {
    for (int i = 0; i < cs.size; i++) 
        if (is_null_clause(cs.tab[i])) //is_empty_clause
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
    for (int i = 0; i < cs->size; i++) {
        if (in_clause2(l, cs->tab[i]))
            remove_clause(cs, i);
        else if (neg_in_clause(l, cs->tab[i]))
            cs->tab[i].tab[l.pos] = init_literal();
    }
}

bool is_pure_literal(literal l, clauseSet cs) {
    bool pure;
    for (int i = 0; i < cs.size; i++)
        if (is_null_lit(l) || neg_in_clause(l, cs.tab[i]))
            return false;
    return true;
}

literal find_pure_literal(clauseSet cs) {
    for (int i = 0; i < cs.size; i++) {
        for (int j = 0; j < cs.tab[i].size; j++) {
            if (is_pure_literal(cs.tab[i].tab[j], cs))
                return cs.tab[i].tab[j];
        }
    }
    return init_literal();
}

void pure_literal_assign(literal l, clauseSet *cs) {
    bool val;
    if (l.name > 0) val = true;
    else val = false;
    for (int i = 0; i < cs->size; i++)
        if (in_clause(l, cs->tab[i]) >= 0)
            remove_clause(cs, i); //assign(l, &cs->tab[i], val);
}

literal first_non_null_literal(clause c) {
    for (int i = 0; i < c.size; i++) {
        if (!is_null_lit(c.tab[i]))
            return c.tab[i];
    }
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

bool DPLL(clauseSet cs) {
    literal l;
    clause c;
    modal m = init_combination(cs.tab[0].size);
    remove_valid_clauses(&cs);
    c = find_unit_clause(cs);
    while (!is_null_clause(c)){
        unit_propagate(first_non_null_literal(c), &cs);
        c = find_unit_clause(cs);
    }
    remove_valid_clauses(&cs);

    l = find_pure_literal(cs);
    while (!is_null_lit(l)) {
        pure_literal_assign(l, &cs);
        l = find_pure_literal(cs);
    }

    if (is_empty_set(cs)) return true;
    if (contains_empty_clause(cs)) return false;
    
    l = first_non_null_literal_in_set(cs);
 
    clauseSet cs1 = init_clauseSet(cs.size);
    copy_cset(cs, &cs1);
    assign_to_set(l, &cs1, true);
    bool d1 = DPLL(cs1);
    if (d1) {
        free(cs1.tab);
        return true;
    }
    clauseSet cs2 = init_clauseSet(cs.size);
    copy_cset(cs, &cs2);
    assign_to_set(l, &cs2, false);
    bool d2 = DPLL(cs2);
    if (d2) {
        free(cs2.tab);
        return true;
    }
    return false;
}

// Version with prints

// bool DPLL(clauseSet cs) { // , clauseSet *cs1, clauseSet *cs2
//     // puts("In");
//     // puts("\n*************"); print_clauseSet(cs);
//     // printf("size of cs : %d\n", cs.size);
//     literal l;
//     clause c;
//     modal m = init_combination(cs.tab[0].size);
//     remove_valid_clauses(&cs);
//     c = find_unit_clause(cs);
//     while (!is_null_clause(c)){
//         // unit_propagate(find_unit_clause(cs).tab[0], &cs);
//         unit_propagate(first_non_null_literal(c), &cs);
//         c = find_unit_clause(cs);

//         // printf("\nafter  unit_propagate : \n");
//         // print_clauseSet(cs);
//     }
//     // puts("passed first while");
//     remove_valid_clauses(&cs);
//     // literal l2 = find_pure_literal(cs);
//     // print_literal(l2);
//     // bool y = is_null_lit(l2);
//     // if (y) puts("is null");
//     l = find_pure_literal(cs);
//     // printf("Found pure : "); print_literal(l);
//     while (!is_null_lit(l)) {
//         // puts("In 2nd while");
//         pure_literal_assign(l, &cs);
//         // puts("in while 2");
//         // print_clauseSet(cs);
//         l = find_pure_literal(cs);
//         // printf("Found pure : "); print_literal(l);
//     }
//     // puts("passed 2nd while");

//     // remove_valid_clauses(&cs);
//     if (is_empty_set(cs)) {
//         // printf("size of cs in size = 0 : %d\n", cs.size);
//         // puts("is_empty_set");
//         return true;
//     }
//     // puts("passed is_empty_set");
    
//     if (contains_empty_clause(cs)) {
//         // puts("contains_empty_clause");
//         return false;
//     }
//     // puts("passed contains_empty_clause");
//     l = first_non_null_literal_in_set(cs);
//     // puts("passed first_non_null_literal");
 
//  /* Normal version less efficient cause will always run twice (but looks nicer) */
//     // clauseSet cs1 = init_clauseSet(cs.size);
//     // clauseSet cs2 = init_clauseSet(cs.size);  
//     // copy_cset(cs, &cs1);
//     // copy_cset(cs, &cs2);
//     // assign_to_set(l, &cs1, true);
//     // assign_to_set(l, &cs2, false);
//     // bool d1 = DPLL(cs1);
//     // bool d2 = DPLL(cs2);
//     // free(cs1.tab);
//     // free(cs2.tab);
//     // return d1 || d2;
    
//     clauseSet cs1 = init_clauseSet(cs.size);
//     copy_cset(cs, &cs1);
//     assign_to_set(l, &cs1, true);
//     bool d1 = DPLL(cs1);
//     if (d1) {
//         free(cs1.tab);
//         return true;
//     }
//     clauseSet cs2 = init_clauseSet(cs.size);
//     copy_cset(cs, &cs2);
//     assign_to_set(l, &cs2, false);
//     bool d2 = DPLL(cs2);
//     if (d2) {
//         free(cs2.tab);
//         return true;
//     }
//     return false;
// }
