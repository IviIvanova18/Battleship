#ifndef _TYPES_
#define _TYPES_

#include <stdbool.h>

#define CLAUSESIZE 3
#define MAXCLAUSESIZE 110

typedef int literal;

typedef struct _clause_ {
    literal tab[CLAUSESIZE];
    int size;
    bool valid;
} clause;

typedef struct _clauseSet_ {
    clause *tab;
    int size;
} clauseSet;

typedef struct _modal_ {
    int *tab;
    int size;
} modal;

typedef struct _node_ {
    clause c;
    struct _node_ *next;
} node;

typedef struct _linked_ {
    node *head;
    int size;
} linked;

#endif
