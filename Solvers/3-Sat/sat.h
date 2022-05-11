#ifndef _SAT_
#define _SAT_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "types.h"

/* initialization */
clauseSet init_clauseSet(int clauseNum); /* Init a clause set */

/* Printing */
void print_clause(clause c);
void print_clauseSet(clauseSet cs);

/***************
 * Solvers      *
 ***************/
void add_clause_Cset(clauseSet *cs, clause c);

bool is_null_lit(literal l); /* True if l's name is '0' */
bool is_null_clause(clause c); /* True if all the literals are null */

clause init_null_clause();
literal init_literal();

int in_clause(literal l, clause c); /* True if the literal l is in the clause c */
int neg_in_clause(literal l, clause c); /* True if the negation of the literal l is in the clause c */
bool neg_in_clauseSet(literal l, clauseSet cs); /* True if the negation of the literal l is in the clauseSet cs */
void remove_literal(literal l, clause *c); /* Removes l from c */
int abs_in_clause(literal l, clause c); /* True if the negation of the literal l is in the clauseSet cs */

void copy_cset(clauseSet cs, clauseSet *cs2); /* Copy cs into cs2 */
void copy_cset2(clauseSet cs, clauseSet *cs1, clauseSet *cs2); /* Copy cs into cs1 and cs2 */
void remove_clause(clauseSet *cs, int p); /* Remove the clause at position p from cs */
void remove_valid_clauses(clauseSet *cs); /* Remove all valid clauses from c */

int number(clauseSet *cs, literal l);
int max_score(clauseSet *cs, literal l);

/***************
 * Solver3     *
 ***************/
bool is_unit_clause(clause c); /* True if c contains only one literal */
clause find_unit_clause(clauseSet cs); /* Finds a unit clause, return null clause if there are none */
//void unit_propagate(literal l, clauseSet *cs,
//                    linked *watched); /* Applies unit propagate ! Sould only be called with unit literals ! */
void unit_propagate(literal l, clauseSet *cs);

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

bool DPLL(clauseSet cs); /* Uses DPLL to decide if cs is sat or unsat */
//bool DPLL(clauseSet cs, FILE *f); /* Uses DPLL to decide if cs is sat or unsat, if sat m is a modal of cs */




#endif
