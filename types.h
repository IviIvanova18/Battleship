#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#ifndef _TYPES_H_
#define _TYPES_H_

#define MAXSIZE 100
#define MAXVARNUM 1000

#define GridSizeHeight 10
#define GridSizeWidth 10

#define BoatCount 10

#define BigBoatSize 4
#define BigBoatCount 1

#define MediumBoatSize 3
#define MediumBoatCount 2

#define SmallBoatSize 2
#define SmallBoatCount 3

#define TinyBoatSize 1
#define TinyBoatCount 4






//x
typedef struct _literal_ {
    int name; 
    bool negation;
} literal;

//x+y
typedef struct _clause_ {
    literal tab[MAXVARNUM];
    int size;
} clause;

// typedef struct _clauseSet_ {
//     clause tab[MAXSIZE];
//     int size;
// } clauseSet;


typedef struct Node_Clause_
{
	clause data;    
	struct Node_Clause_* next; 
}Node_Clause;


typedef struct List_Clause_
{
	unsigned int size;      
	Node_Clause *first; 
    Node_Clause *last;    
}List_Clause;



typedef struct Boat_{
    int n;//size of boat associated with k
    // k in (1...10)
    int k;//the number of boat 
    
}Boat;

typedef struct literalB_{
    bool val;
    int i, j;   
    Boat boat;
}literalB;

typedef bool literalO;

typedef struct CellX_{
    bool val;
    int i, j;   
    int k;
}CellX;

Node_Clause *create_element_List_Clause(clause *clause);
List_Clause create_empty_List_Clauses();
List_Clause add_element_List_Clause(List_Clause* L, clause *clause);
clause* copyInputClauseToDestination(clause* destination, clause* input);
void print_List_Clause(List_Clause*L);
void print_literal_usual_form(literal l);
void print_Clause(clause c);
void add_element_Clause(clause *c,literal l);

#endif 
