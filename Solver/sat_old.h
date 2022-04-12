#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define MAXVARNUM 20
#define MAXCLAUSENUM 20

typedef struct _literal_ {
    char name[2]; // name[0] is either '.' or '-'
    bool negation;
    int pos;
} literal;

typedef struct _literal2_ {
    char name[2]; // name[0] is either '.' or '-'
    bool negation;
    int pos;
} literal2;

typedef struct _clause_ {
    literal tab[MAXVARNUM];
    int size;
    bool valid;
} clause;

typedef struct _clauseSet_ {
    clause tab[MAXCLAUSENUM];
    int size;
} clauseSet;

typedef struct _combination_ {
    int tab[MAXCLAUSENUM];
    int size;
} combination;

typedef combination modal;

/* True if both literals have the same name */
bool same_name(literal a, literal b);

/* True if the modal is true with the given clause */
bool check_modal(clause c, modal m);

/* 
 * Returns a posible modal of the clause starting from the combination cb
 * Returns a list of -1 if a modal can't be found 
 */
modal find_modal(clause c, combination cb);

/* True if the set of clauses is satisfable */
bool sat(clauseSet cs);

/* Gives the next combination */
void inc(combination *cb);

/* True if cb = 11...1 */
bool all_one(combination cb);

/* Return [-1 ... -1] */
modal null_modal();

/* True if equal to [-1 ... -1] */
bool is_null_modal(modal m);

/* True if l's name is '0' */
bool is_null_lit(literal l);

/* Init a combination */
combination init_combination();

/* Init a literal */
literal init_literal();

/* Init a clause */
clause init_clause();

/* Init a clause to [0...0] */
clause init_null_clause();

/* Add the literal l to the clause c */
void add_l_clause(clause *c, literal l);

/* Add the literal l to the clause c (use when c was initialized with init_clause) */
void add_l_clause2(clause *c, literal l);

/* Add the clause c to set cs */
void add_clause_Cset(clauseSet *cs, clause c);

/* Return the position of literal l in the clause c or -1 if it's not in c */
int inSet(literal l, clause c);

/* True if the negation of the literal l is in the clause c */
bool neg_in_clause(literal l, clause c);

/* True if the literal l is in the clause c */
int in_clause(literal l, clause c);

/* True for {a, a} but not for {a, -a} */
bool same_var(literal a, literal b);

/* simplify a clause */
clause simpli(clause c);

/* simplify a clause set */
void simpli_cset(clauseSet *cs);

/* Remove the literal l from the clause c */
void supLitClause(literal l, clause *c);

/* Sub-function of read_clause_set */
void _read(literal *l, clause *cl, clause *dejaVu, char c, bool neg);

/* Read a set of clauses form a file */
void read_clause_set(clauseSet *cs, FILE *f);

/* Read a set of clauses form a DIMACS file */
void read_DIMACS(clauseSet *cs, FILE *f);

void read_start(FILE *f); // Temp
void remove_comments(FILE *f);
void read_p_line(FILE *f, int *varNum, int *clauseNum);



/* Printing */
void print_clause(clause c);
void print_clauseSet(clauseSet cs);
void print_modal(modal m);
void print_modal2(modal m);
void print_is_valid(clause c);
void print_all_combi();
