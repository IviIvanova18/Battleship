#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 600

typedef struct _literal_ {
    int name;
    bool negation;
    int pos;
} literal;

typedef struct _clause_ {
    literal *tab;
    int size;
    bool valid;
} clause;

typedef struct _clauseSet_ {
    clause *tab;
    int size;
} clauseSet;

typedef struct _combination_ {
    int *tab;
    int size;
} combination;

typedef combination modal;

/* initialization */
literal init_literal(); /* Init a literal */
clause init_clause(int varNum); /* Init a clause */
clause init_null_clause(int varNum); /* Init a clause to [0...0] */
clauseSet init_clauseSet(int clauseNum); /* Init a clause set */

/* Remove and free */
void clear_cset(clauseSet cs); /* Free a clause set */
void free_clause(clause c); /* Free a clause */
void supLitClause(literal l, clause *c); /* Remove the literal l from the clause c */
void remove_clause(clauseSet *cs, int p); /* Remove the clause at position p from cs */
void remove_valid_clauses(clauseSet *cs); /* Remove all valid clauses from c */

/* Printing */
void print_literal(literal l);

void print_clause(clause c);

void print_clauseSet(clauseSet cs);

void print_modal(modal m);

void print_modal2(modal m);

void print_is_valid(clause c);

void print_all_combi(int varNum);

/* Simple tests */
bool is_null_lit(literal l); /* True if l's name is '0' */
bool is_null_clause(clause c); /* True if all the literals are null */
bool same_name(literal a, literal b); /* True if both literals have the same name */
bool same_var(literal a, literal b); /* True for {a, a} or {-a, -a} but not for {a, -a} */
bool neg_in_clause(literal l, clause c); /* True if the negation of the literal l is in the clause c */
bool neg_in_clauseSet(literal l, clauseSet cs); /* True if the negation of the literal l is in the clauseSet cs */
int in_clause(literal l,
              clause c); /* Return the position of literal l in the clause c or -1 if it's not in c, using same_name() */
int in_clause2(literal l,
               clause c); /* Return the position of literal l in the clause c or -1 if it's not in c, using same_var() */

/* Add */
void add_l_clause(clause *c, literal l); /* Add the literal l to the clause c */
void add_l_clause2(clause *c,
                   literal l); /* Add the literal l to the clause c (use when c was initialized with init_clause) */
void add_clause_Cset(clauseSet *cs, clause c); /* Add the clause c to set cs */
void copy_cset(clauseSet cs, clauseSet *cs2); /* Copy cs into cs2 */

/* Random */
clause random_clause(clauseSet cs); /* Returns a random clause from cs */
clause random_false_clause(clauseSet cs, combination c); /* Returns a random clause cl with c(cl) = 0 */
literal random_literal(clause c); /* Returns a random literal from c */
double random_min_max(double min, double max); /* Returns a random float from [min, max] */

/* Other */
clauseSet false_set(clauseSet cs, combination c); /* Return all clauses cl with c(cl) = 0 */

/***************
 * Modals      *
 ***************/
void inc(combination *cb); /* Gives the next combination */
bool all_one(combination cb); /* True if cb = 11...1 */
bool is_null_modal(modal m); /* True if equal to [-1 ... -1] */
bool check_modal(clause c, modal m); /* True if the modal is true with the given clause */
bool check_set_modal(clauseSet cs, modal m); /* True if the model is true with the given clause */
combination init_combination(int varNum); /* Init a combination */
combination random_combination(int varNum); /* Returns a random combination */
modal null_modal(); /* Return [-1 ... -1] */

/* Returns a posible modal of the clause starting from the combination cb
 * Returns a list of -1 if a modal can't be found */
modal find_modal(clause c, combination cb);

/***************
 * DIMACS      *
 ***************/
void read_DIMACS(clauseSet *cs, FILE *f); /* Read a set of clauses form a DIMACS file */
void remove_comments(FILE *f); /* Removes the comments form a DIMACS file */
void
read_p_line(FILE *f, int *varNum, int *clauseNum); /* Reading the 'p cnf varNum clauseNum' line form a DIMACS file */
void add_to_sets(literal *l, clause *cl, clause *dejaVu); /* Adds l to cl and to devaVu if necessary */

/* Old format, not in use */
void _read(literal *l, clause *cl, clause *dejaVu, char c, bool neg); /* Sub-function of read_clause_set */
void read_clause_set(clauseSet *cs, FILE *f); /* Read a set of clauses form a file */

/***************
 * Solver1     *
 ***************/
clause simpli(clause c); /* simplify a clause */
void simpli_cset(clauseSet *cs); /* simplify a clause set */
bool solver1(clauseSet cs, combination *c); /* True if the set of clauses is satisfable */

/***************
 * Solver2     *
 ***************/
int number(literal l, clauseSet cs, bool positive); /* The number of positive/negative occurences across cs */
int score(literal l, clauseSet cs, combination c); /* Score of z depending on c */
literal max_score(clause cl, clauseSet cs, combination c); /* The literal with the highest score in c */
literal deterministic(clause cl, clauseSet cs, combination c); /* Deterministically choose a variable in cl */

modal solver2(clauseSet cs); /* WalkSat solver */

/***************
 * Solver3     *
 ***************/
bool is_unit_clause(clause c); /* True if c contains only one literal */
clause find_unit_clause(clauseSet cs); /* Finds a unit clause, return null clause if there are none */
void unit_propagate(literal l, clauseSet *cs); /* Applies unit propagate ! Sould only be called with unit literals ! */

literal find_pure_literal(
        clauseSet cs); /* Finds a pure literal (if it occurs with only one polarity in the all set), return null literal if there are none */
bool is_pure_literal(literal l, clauseSet cs); /* Checks if l is a pure literal */
void
pure_literal_assign(literal l, clauseSet *cs); /* Assign l such in a way that makes all clauses containing it true */

literal first_non_null_literal(clause c); /* Finds the first non-null literal, return null literal if there are none */
literal first_non_null_literal_in_set(
        clauseSet cs); /* Finds the first non-null literal in a set, return null literal if there are none */
bool is_empty_set(clauseSet cs); /* True if cs is empty */
bool contains_empty_clause(clauseSet cs); /* True if cs contains a null clause */

void assign(literal l, clause *c, bool val); /* Assigning a truth value to l in a clause */
void assign_to_set(literal l, clauseSet *cs, bool val); /* Assigning a truth value to l in a set */
void assign_to_modal(modal *m, int pos, bool val); /* Assign val to the modal at position pos */

bool DPLL(clauseSet cs, modal *m); /* Uses DPLL to decide if cs is sat or unsat, if sat m is a modal of cs */
