#include "sat_old.h"

void print_clause(clause c) {
    for (int i = 0; i < c.size - 1; i++) {
        if (c.tab[i].negation)
            printf("-%c + ", c.tab[i].name[1]);
        else    
            printf("%c + ", c.tab[i].name[1]);
    }
    if (c.tab[c.size - 1].negation)
        printf("-%c\n", c.tab[c.size - 1].name[1]);
    else    
        printf("%c\n", c.tab[c.size - 1].name[1]);
}

void print_clauseSet(clauseSet cs) {
    for (int i = 0; i < cs.size; i++)
        print_clause(cs.tab[i]);
}

void print_modal(modal m) {
    for (int i = 0; i < m.size - 1; i++)
        printf("%d ", m.tab[i]);
    printf("%d\n", m.tab[m.size - 1]);
    
}

void print_modal2(modal m) {
    for (int i = m.size - 1; i >= 0 ; i--)
        printf("%d ", m.tab[i]);
    puts("");    
}

void print_is_valid(clause c) {
    if (c.valid) 
        {printf("Valid : "); print_clause(c);}
    else {printf("NOT Valid : "); print_clause(c);}

}

void print_all_combi() {
    combination c = init_combination();
    while (!all_one(c)) {
        print_modal(c);
        inc(&c);
    }
    print_modal(c);
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

modal null_modal() {
    modal m;
    for (int i = 0; i < MAXVARNUM; i++)
        m.tab[i] = -1;
    m.size = MAXVARNUM;
    return m;
}

bool is_null_modal(modal m) {
    for (int i = 0; i < m.size; i++)
        if (m.tab[i] != -1)
            return false;
    return true;
}

bool is_null_lit(literal l) {
    return l.name[1] == '0';
}

combination init_combination() {
    combination c;
    c.size = MAXVARNUM;
    for (int i = 0; i < MAXVARNUM; i++)
        c.tab[i] = 0;
    return c;
}

bool same_name(literal a, literal b) {
    return (a.name[1] == b.name[1]);
}

int inSet(literal l, clause c) {
    for (int i = 0; i < c.size; i++) 
        if (same_name(l, c.tab[i])) return i;
    return -1;
}

bool neg_in_clause(literal l, clause c) {
    int p = inSet(l, c);
    if (p == -1) return false;
    return (l.negation + c.tab[p].negation == 1);
}

bool same_var(literal a, literal b) {
    return (a.name[1] == b.name[1] && (a.negation - b.negation == 0));
}

int in_clause(literal l, clause c) {
    for (int i = 0; i < c.size; i++) 
        if (same_var(l, c.tab[i])) return i;
    return -1;
}

clause init_clause() {
    clause c;
    c.size = 0;
    c.valid = false;
    return c;
}

literal init_literal() {
    literal l;
    l.name[0] = '0';
    l.name[1] = '0';
    l.negation = false;
    l.pos = 0;
    return l;
}


clause init_null_clause() {
    clause c;
    c.size = MAXVARNUM;
    c.valid = false;
    literal l = init_literal();
    for (int i = 0; i < MAXVARNUM; i++) {
        l.pos = i;
        c.tab[i] = l;
    }
    return c;
}

void simpli_cset(clauseSet *cs) {
    for (int i = 0; i < cs->size; i++) 
        cs->tab[i] = simpli(cs->tab[i]);
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

void add_l_clause2(clause *c, literal l) {
    c->tab[c->size] = l;
    c->size++;
}

void add_l_clause(clause *c, literal l) {
    c->tab[l.pos] = l;
}

void add_clause_Cset(clauseSet *cs, clause c) {
    cs->tab[cs->size] = c;
    cs->size++;
}

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

modal find_modal(clause c, combination cb) {
    while (!check_modal(c, cb)) {
        if (all_one(cb))
            return null_modal();
        inc(&cb);
    }
    return cb;
}

/* ! ! ! ! ! !
 * since same_name is true even for p and -p, 
 * the simplified version will be wrong in the case of p + -p
 * but it will be set as valid so it will just get removed by simpli_cset
 */ 
clause simpli(clause c) {
    clause dejaVu = init_null_clause();
    for (int i = 0; i < c.size; i++) {
        int p = inSet(c.tab[i], dejaVu);
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

void _read(literal *l, clause *cl, clause *dejaVu, char c, bool neg) {
    if (neg) l->name[0] = '-';
    else l->name[0] = '.';
    l->name[1] = c;
    l->negation = neg; 
    int p = inSet(*l, *dejaVu);
    if (p == -1) {
        l->pos = dejaVu->size;
        add_l_clause2(dejaVu, *l);
    }
    else l->pos = p;
    add_l_clause(cl, *l);
}

void read_clause_set(clauseSet *cs, FILE *f) {
    int p;
    char c;
    literal l;
    clause cl = init_null_clause();
    clause dejaVu = init_clause();
    while(!feof(f)) {
        cl = init_null_clause();
        fscanf(f, "%c", &c);
        while (c != '\n') { 
            if (c == '-') {
                fscanf(f, "%c", &c);
                _read(&l, &cl, &dejaVu, c, true);
            } else if (c != ' ')
                _read(&l, &cl, &dejaVu, c, false);
            fscanf(f, "%c", &c);             
        }
        add_clause_Cset(cs, cl);
    }
}

void read_start(FILE *f) {
    char c;
    fscanf(f, "%c", &c);
    printf("%c", c);
    fscanf(f, "%c", &c);
    printf("%c", c);
}

void remove_comments(FILE *f) {
    char c;
    char *s = malloc(sizeof(char) * 50);
    fscanf(f, "%c", &c);
    while (c == 'c') { // Getting rid of the comments 
        fgets(s, 50, f);
        fscanf(f, "%c", &c);
        printf("%c\n", c);
    }
    free(s);
}

void read_p_line(FILE *f, int *varNum, int *clauseNum) {
    char c, *s = malloc(sizeof(char) * 50);
    fscanf(f, "%s", s); // Getting cnf
    fscanf(f, "%c", &c); // Getting space 
    fscanf(f, "%d", varNum); // Getting number of variables
    fscanf(f, "%c", &c); // Getting space 
    fscanf(f, "%d", clauseNum); // Getting number of clauses
    // I apologize for that
    #undef MAXVARNUM
    #undef MAXCLAUSENUM
    #define MAXVARNUM varNum
    #define MAXCLAUSENUM clauseNum
    free(s);
}

void read_DIMACS(clauseSet *cs, FILE *f) {
    int x;
    literal2 l;
    clause cl = init_null_clause();
    clause dejaVu = init_clause();
    while (!feof(f)) {
        fscanf(f, "%d", &x);
        printf("%d\n", x);
    }
    

}

/* !!!!!!!!!
 * The modal sat is printing in the right modal + 1 (so not the right modal)
 */
bool sat(clauseSet cs) {
    simpli_cset(&cs);
    int j;
    bool all_good = false;
    combination c = init_combination();
    modal m = find_modal(cs.tab[0], c);
    while (!all_good) {
        all_good = true;
        for (int i = 0; i < cs.size; i++) {
            if (!cs.tab[i].valid) {
                if (!check_modal(cs.tab[i], m)) {
                    all_good = false;
                    break; 
                }   
            }
        }
        inc(&c);
        j = 0;
        while (cs.tab[j].valid)
            j++;
        m = find_modal(cs.tab[j], c);
        if (all_one(m) || all_one(c))
            return false;
    }
    // foundModal : printf("Final modal : "); print_modal(m);
    return true;
}