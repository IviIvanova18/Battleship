#include "linked.h"

void add_to_linked(linked *l, clause c) {
//    printf("in add : adding : "); print_clause(c);
    assert(l);
    node *n = init_node();
    n->c = c;
    n->next = l->head;
    l->head = n;
    l->size++;
}

clause get_clause(linked l) {
    assert(l.size > 0);
    return l.head->c;
}


void remove_head(linked *l) {
//    puts("in remove head");
    assert(l);
//    printf("\n head before : "); print_clause(*l->head->c);
    node *n = l->head;
    l->head = n->next;
    l->size--;
    free_node(n);
//    if (l->size > 0){printf("\n head after : "); print_clause(*l->head->c);}
}

linked init_linked() {
    linked l;
    l.head = NULL;
    l.size = 0;
    return l;
}

node *init_node() {
    node *n = malloc(sizeof(node));
    return n;
}

void free_node(node *n) {
    free(n);
}


void free_linked(linked *l) {
    if (l->size == 0) return;
    assert(l->head);
    node *n = l->head;
    node *n2;
    while (n) {
        n2 = n->next;
        free_node(n);
        n = n2;
    }
    l->head = NULL;
    l->size = 0;
}

void print_linked(linked l) {
    node *n = l.head;
    while (n) {
        print_clause(n->c);
        n = n->next;
    }
}













//void add_to_linked(linked *l, clause *c) {
//    printf("in add : adding : "); print_clause(*c);
//    assert(l);
//    assert(c);
//    node *n = init_node();
//    n->c = c;
//    n->next = l->head;
//    l->head = n;
//    l->size++;
//}
//
////clause get_clause(linked l) {
////    assert(l.size > 0);
////    puts("in get_clause");
//////    print_clause(*l.head->c);
////    clause c = *l.head->c;
//////    print_clause(c);
////
////    return c;
////}
//
//clause *get_clause(linked l) {
//    assert(l.size > 0);
//    return l.head->c;
//}
//
//
//void remove_head(linked *l) {
////    puts("in remove head");
//    assert(l);
////    printf("\n head before : "); print_clause(*l->head->c);
//    node *n = l->head;
//    l->head = n->next;
//    l->size--;
//    free_node(n);
////    if (l->size > 0){printf("\n head after : "); print_clause(*l->head->c);}
//}
//
//linked init_linked() {
//    linked l;
//    l.head = NULL;
//    l.size = 0;
//    return l;
//}
//
//node *init_node() {
//    node *n = malloc(sizeof(node));
//    return n;
//}
//
//void free_node(node *n) {
//    free(n);
//}
//
//
//void free_linked(linked *l) {
//    if (l->size == 0) return;
//    assert(l->head);
//    node *n = l->head;
//    node *n2;
//    while (n) {
//        n2 = n->next;
//        free_node(n);
//        n = n2;
//    }
//    l->head = NULL;
//    l->size = 0;
//}
//
//void print_linked(linked l) {
//    node *n = l.head;
//    while (n) {
//        print_clause(*(n->c));
//        n = n->next;
//    }
//}
//
//typedef struct _node_ {
//    clause *c;
//    struct _node_ *next;
//} node;
//
//typedef struct _linked_ {
//    node *head;
//    int size;
//} linked;