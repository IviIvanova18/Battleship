#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define MAXSIZE 10
#define MAXVARNUM 10



// ab
typedef struct _literal_ {
    char name; 
    bool negation;
} literal;


//a+b
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

Node_Clause *create_element_List_Clause(clause c);
List_Clause create_empty_List_Clauses();
List_Clause add_element_List_Clause(List_Clause* L, clause c);