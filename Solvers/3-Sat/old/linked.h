#ifndef _LINKED_
#define _LINKED_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "../types.h"
#include "../sat.h"

node *init_node();

linked init_linked();

void print_linked(linked l);

void add_to_linked(linked *l, clause c);

clause get_clause(linked l);

void remove_head(linked *l);

void free_node(node *n);

void free_linked(linked *l);

#endif
