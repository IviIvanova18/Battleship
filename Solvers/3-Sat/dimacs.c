#include "dimacs.h"

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

void read_DIMACS(clauseSet *cs, int clauseNum, FILE *f) {
    int x;
    clause c = init_null_clause();

    for (int i = 0; !feof(f) && i < clauseNum; i++) {
        for (int j = 0; j < CLAUSESIZE; j++) {
            fscanf(f, "%d", &x);
            c.tab[j] = x;
        }
        fscanf(f, "%d", &x); // Getting the 0 at the end of the line
        add_clause_Cset(cs, c);
        c = init_null_clause();
    }
}


void print_clause_file(FILE *f, clause c) {
    fprintf(f, "%d %d %d 0\n", (int) c.tab[0], (int) c.tab[1], (int) c.tab[2]);
}

void read_general_DIMACS(int varNum, int clauseNum, int *newVarNum, int *newClauseNum, FILE *in, FILE *out) {
    int *c, x, addedVars = varNum;
    *newClauseNum = 0;

    for (int i = 0; !feof(in) && i < clauseNum; i++) {
        c = calloc(MAXCLAUSESIZE, sizeof(int));
        int j = 0;
        fscanf(in, "%d", &x);
        while (x != 0) {
            c[j] = x;
            fscanf(in, "%d", &x);
            j++;
        }
        if (j == 1) {
            print_clause_file(out, (clause) {c[0], addedVars + 1, addedVars + 2});
            print_clause_file(out, (clause) {c[0], -(addedVars + 1), addedVars + 2});
            print_clause_file(out, (clause) {c[0], addedVars + 1, -(addedVars + 2)});
            print_clause_file(out, (clause) {c[0], -(addedVars + 1), -(addedVars + 2)});
            addedVars += 2;
            *newClauseNum += 4;
        } else if (j == 2) {
            print_clause_file(out, (clause) {c[0], c[1], addedVars + 1});
            print_clause_file(out, (clause) {c[0], c[1], -(addedVars + 1)});
            *newClauseNum += 2;
            addedVars += 1;
        } else if (j == 3) {
            print_clause_file(out, (clause) {c[0], c[1], c[2]});
            *newClauseNum += 1;
        } else {
            addedVars++;
            print_clause_file(out, (clause) {c[0], c[1], addedVars});
            for (int k = 2; k < j - 3; k++) {
                print_clause_file(out, (clause) {c[k], -addedVars, addedVars + 1});
                addedVars++;
            }
            print_clause_file(out, (clause) {c[j - 2], c[j - 1], addedVars});
            *newClauseNum += (j - 3);
        }
        free(c);
    }
    *newVarNum = addedVars;
}

void write_new_DIMACS(FILE *in, FILE *out) {
    int varNum, clauseNum, newVarNum, newClauseNum;
    FILE *temp = fopen("temp.cnf", "w");
    assert(temp);

    remove_comments(in);
    read_p_line(in, &varNum, &clauseNum);

    read_general_DIMACS(varNum, clauseNum, &newVarNum, &newClauseNum, in, temp);

    fclose(temp);
    temp = fopen("temp.cnf", "r");

    fprintf(out, "p cnf %d %d\n", newVarNum, newClauseNum);
    char c;
    fscanf(temp, "%c", &c);
    while (!feof(temp)) {
        fprintf(out, "%c", c);
        fscanf(temp, "%c", &c);
    }
    fclose(temp);
}