#ifndef _DIMACS_
#define _DIMACS_

#include "sat.h"

/***************
 * DIMACS      *
 ***************/
void read_DIMACS(clauseSet *cs, int clauseNum, FILE *f); /* Read a set of clauses form a DIMACS file */
void remove_comments(FILE *f); /* Removes the comments form a DIMACS file */
void read_p_line(FILE *f, int *varNum, int *clauseNum); /* Reading the 'p cnf varNum clauseNum' line form a DIMACS file */

void write_new_DIMACS(FILE *in, FILE *out); /* Reads a DIMACS file with clauses of any size, and files cs with clauses of size 3 !We supposed that there is no variable who's name is > than numVars! */
void read_general_DIMACS(int varNum, int clauseNum, int *newVarNum, int *newClauseNum, FILE *in, FILE *out); /* Sub-function, used to read the original file */
void print_clause_file(FILE *f, clause c); /* Sub-function, used to write in the new file */

#endif