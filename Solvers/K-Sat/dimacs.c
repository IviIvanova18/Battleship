#include "sat.h"

void remove_comments(FILE *f) {
    char c;
    char *s = malloc(sizeof(char) * 100);
    fscanf(f, "%c", &c);
    while (c == 'c') {
        fgets(s, 100, f);
        fscanf(f, "%c", &c);
    }
    free(s);
}

void read_p_line(FILE *f, int *varNum, int *clauseNum) {
    char c, *s = malloc(sizeof(char) * 100);
    fscanf(f, "%s", s); // Getting cnf
    fscanf(f, "%c", &c); // Getting space 
    fscanf(f, "%d", varNum); // Getting number of variables
    fscanf(f, "%c", &c); // Getting space 
    fscanf(f, "%d", clauseNum); // Getting number of clauses
    free(s);
}

void add_to_sets(literal *l, clause *cl, clause *dejaVu) {
    int p = in_clause(*l, *dejaVu);
    if (p == -1) {
        // l->pos = dejaVu->size;  
        add_l_clause2(dejaVu, *l);
    }
    // else l->pos = p;
    l->pos = abs(l->name) - 1;
    add_l_clause(cl, *l);
}

void read_DIMACS(clauseSet *cs, FILE *f) {
    literal l;
    int x, varNum, clauseNum;

    remove_comments(f);
    read_p_line(f, &varNum, &clauseNum);
    clause cl = init_null_clause(varNum);
    clause dejaVu = init_clause(varNum);

    fscanf(f, "%d", &x);
    for (int i = 0; i < clauseNum; i++) {
        cl = init_null_clause(varNum);
        while (x != 0) {
            l.name = x;
            l.pos = abs(l.name) - 1;
            if (x < 0) l.negation = true;
            else l.negation = false;
            add_to_sets(&l, &cl, &dejaVu);
            fscanf(f, "%d", &x);
        }
        fscanf(f, "%d", &x);
        add_clause_Cset(cs, cl);
    }
    free_clause(dejaVu);
}
