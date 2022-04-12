#include "sat.h"

/* initialization */

literal init_literal() {
    literal l;
    l.name = 0;
    l.negation = false;    
    // l.pos = 0;
    return l;
}

clause init_clause(int varNum) {
    clause c;
    c.size = 0;
    c.valid = false;
    c.tab = malloc(sizeof(literal) * varNum);
    return c;
}

clause init_null_clause(int varNum) {
    clause c;
    c.size = varNum;
    c.valid = false;
    literal l = init_literal();
    c.tab = malloc(sizeof(literal) * varNum);
    for (int i = 0; i < varNum; i++) {
        l.pos = i;
        c.tab[i] = l;
    }
    return c;
}

clauseSet init_clauseSet(int clauseNum) {
    clauseSet CS;
    CS.tab = malloc(sizeof(clause) * clauseNum);
    CS.size = 0;
    return CS;
}

/* Remove and free */

void free_clause(clause c) {
    free(c.tab);
}

void clear_cset(clauseSet cs) {
    for (int i = 0; i < cs.size; i++) 
        free_clause(cs.tab[i]);
}

void supLitClause(literal l, clause *c) {
    for (int i = 0; i < c->size; i++) {
        if (same_name(l,c->tab[i])) {
            for (int j = i; j < c->size - 1; j++)
                c->tab[j] = c->tab[j + 1];
            c->size--;
            return;
        }
    } 
}

void remove_clause(clauseSet *cs, int p) {
    for (int i = p; i < cs->size - 1; i++)
        cs->tab[i] = cs->tab[i + 1];
    cs->size--;
    return;
}

void remove_valid_clauses(clauseSet *cs) {
    for (int i = 0; i < cs->size; i++) {
        if (cs->tab[i].valid) {
            remove_clause(cs, i);
            i--;
        }
    }
}

/* Printing */

void print_literal(literal l) {
    printf("l.name : %d ; l.pos : %d ; l.neg : %d\n", l.name, l.pos, l.negation);
}

void print_clause(clause c) {
    for (int i = 0; i < c.size - 1; i++)
        printf("%d + ", c.tab[i].name);
    printf("%d ###\n", c.tab[c.size - 1].name);
}

void print_clauseSet(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        print_is_valid(cs.tab[i]); //print_clause(cs.tab[i]);
}

void print_modal(modal m) {
    for (int i = 0; i < m.size - 1; i++)
        printf("%d ", m.tab[i]);
    printf("%d\n", m.tab[m.size - 1]);
    
}

void print_is_valid(clause c) {
    if (c.valid) 
        {printf("Valid : "); print_clause(c);}
    else {printf("NOT Valid : "); print_clause(c);}

}

void print_all_combi(int varNum) {
    combination c = init_combination(varNum);
    while (!all_one(c)) {
        print_modal(c);
        inc(&c);
    }
    print_modal(c);
}

/* Simple tests */

bool is_null_lit(literal l) {
    return l.name == 0;
}

bool is_null_clause(clause c) {
    for (int i = 0; i < c.size; i++) {
        if (!is_null_lit(c.tab[i]))
            return false;
    }
    return true;
}


bool same_name(literal a, literal b) {
    return (abs(a.name) == abs(b.name));
}

bool same_var(literal a, literal b) {
    return (abs(a.name) == abs(b.name) && (a.negation - b.negation == 0));
}

bool neg_in_clause(literal l, clause c) {
    int p = in_clause(l, c);
    if (p == -1) return false;
    return (l.negation + c.tab[p].negation == 1);
}

int in_clause(literal l, clause c) {
    for (int i = 0; i < c.size; i++) 
        if (same_name(l, c.tab[i])) return i;
    return -1;
}

int in_clause2(literal l, clause c) {
    for (int i = 0; i < c.size; i++) 
        if (same_var(l, c.tab[i])) return i;
    return -1;
}

/* Add */

void add_l_clause2(clause *c, literal l) {
    c->tab[c->size] = l;
    c->size++;
}

void add_l_clause(clause *c, literal l) {
    if (same_name(l, c->tab[l.pos]) && l.negation + c->tab[l.pos].negation == 1)
        c->valid = true;
    c->tab[l.pos] = l;
}

void add_clause_Cset(clauseSet *cs, clause c) {
    cs->tab[cs->size] = c;
    cs->size++;
}

/* Other */
clause random_clause(clauseSet cs) {
    return cs.tab[rand() % cs.size];
}

clauseSet false_set(clauseSet cs, modal m) {
    clauseSet cs2 = init_clauseSet(cs.size);
    for (int i = 0; i < cs.size; i++)
        if (!check_modal(cs.tab[i], m))
            add_clause_Cset(&cs2, cs.tab[i]);
    return cs2;
}

clause random_false_clause(clauseSet cs, modal m) {
    clause c = random_clause(cs);
    while (check_modal(c, m)) 
        c = random_clause(cs);
    return c;
}

literal random_literal(clause c) {
    return c.tab[rand() % c.size];
}

double random_min_max(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void copy_cset(clauseSet cs, clauseSet *cs2) {
    for (int i = 0; i < cs.size; i++) {
        cs2->tab[i] = init_null_clause(cs.tab[i].size);
        for (int j = 0; j < cs.tab[i].size; j++) {
            cs2->tab[i].tab[j] = cs.tab[i].tab[j];
        }
        cs2->size++;
    }
}