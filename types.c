#include "types.h"


Node_Clause *create_element_List_Clause(clause *clause) {
    Node_Clause *el;
    el = (Node_Clause *) malloc(sizeof(Node_Clause));
    if (el == NULL) {
        fprintf(stderr, "create_element_List_Point : impossible allocation\n");
        exit(-1);
    }
    el->data = *clause;

    el->next = NULL;
    return el;
}

List_Clause create_empty_List_Clauses() {
    List_Clause L = {0, NULL, NULL};
    return L;
}

List_Clause add_element_List_Clause(List_Clause *L, clause *c) {
    Node_Clause *el;

    el = create_element_List_Clause(c);
    if (L->size == 0) {
        L->first = L->last = el;
        el->next = NULL;
    } else {
        L->last->next = el;
        L->last = el;
        el->next = NULL;
    }
    L->size++;

    return *L;
}


/*Combinations*/
combination_list create_empty_combination_list() {
    combination_list L = {0, NULL, NULL};
    return L;
}


Node_Combination *create_element_combination_list(combination *c) {
    Node_Combination *el;
    el = (Node_Combination *) malloc(sizeof(Node_Combination));
    if (el == NULL) {
        fprintf(stderr, "create_element_List_Point : impossible allocation\n");
        exit(-1);
    }
    el->data = *c;

    el->next = NULL;
    return el;
}

combination_list add_element_combination_list(combination_list *L, combination *c) {
    Node_Combination *el;

    el = create_element_combination_list(c);
    if (L->size == 0) {
        L->first = L->last = el;
        el->next = NULL;
    } else {
        L->last->next = el;
        L->last = el;
        el->next = NULL;
    }
    L->size++;

    return *L;
}

void print_curr_combination(combination c) {

    for (int i = 0; i < c.size; i++) {
        printf("%d ", c.tab[i]);
    }

    printf("\n");
}

void print_all_combinations(combination_list comb_list) {
    Node_Combination *comb;
    comb = comb_list.first;
    while (comb->next != NULL) {
        combination c;
        c = comb->data;
        print_curr_combination(c);
        comb = comb->next;
    }
}

void add_element_Clause(clause *clause, literal literal) {
    clause->size++;
    clause->tab[clause->size - 1] = literal;
}


void print_literal_usual_form(literal l) {
    int numCopy = l.name;
    int k = numCopy % 10;
    numCopy /= 10;
    int j = numCopy % 10;
    numCopy /= 10;
    int i = numCopy % 10;
    numCopy /= 10;
    if (l.name <= 999) {
        if (l.negation) {
            printf("(-X_%d,%d,%d)", i, j, k);

        } else {
            printf("(+X_%d,%d,%d)", i, j, k);
        }
    } else if (l.name >= 1000 && l.name <= 1999) {
        if (l.negation) {
            printf("(-B_%d,%d,%d)", i, j, k);

        } else {
            printf("(+B_%d,%d,%d)", i, j, k);
        }
    } else if (l.name >= 2000 && l.name <= 2009) {
        if (l.negation) {
            printf("(-O_%d)", k);

        } else {
            printf("(+O_%d)", k);
        }

    } else if (l.name == 2010) {
        if (l.negation) {
            printf("(-X_0,0,0)");

        } else {
            printf("(+X_0,0,0)");
        }
    } else {
        printf("Error %d", l.name);
    }
}

void print_Clause(clause c) {
    int k;
    int n = c.size;

    printf("[");
    for (k = 0; k < n; k++) {
        literal l = c.tab[k];
        print_literal_usual_form(l);
        // if (l.negation) {
        // 	// printf("(-%d)",l.name);
        // }else{
        // // printf("(+%d)",l.name);
        // }
    }
    printf("]");
}


void print_List_Clause(List_Clause *L) {
    assert(L);
    Node_Clause *c;
    c = L->first;
    while (c != NULL) {
        if (c->next == NULL) {
            print_Clause(c->data);
        } else {
            print_Clause(c->data);
            printf(" \n ");
        }

        c = c->next;
    }
    printf("\n");
}


void addBoat(clause *c, int i, int j, int k, bool negation) {
    //-Bi,j,k
    literal l;
    l.name = 1000 + 100 * i + 10 * j + k;
    l.negation = negation;
    add_element_Clause(c, l);
}

void addOrientation(clause *c, int k, bool negation) {
    //ok
    literal l;
    l.name = 2000 + k;
    l.negation = negation;
    add_element_Clause(c, l);
}

void addCell(clause *c, int i, int j, int k, bool negation) {
    literal l;
    if (i == 0 && j == 0 && k == 0) {
        l.name = 2010;
    } else {
        l.name = 100 * i + 10 * j + k;
    }
    l.negation = negation;
    add_element_Clause(c, l);
}

void reset_Clause(clause *c) {
    for (int i = 0; i < c->size; i++) {
        c->tab[i].name = 0;
        c->tab[i].negation = false;
    }
    c->size = 0;
}

