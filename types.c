#include "types.h"



Node_Clause *create_element_List_Clause(clause *clause){
    Node_Clause *el;
	el = (Node_Clause *)malloc(sizeof(Node_Clause));
	if (el==NULL)
	{
		fprintf(stderr, "create_element_List_Point : impossible allocation\n");
		exit(-1);
	}
	el->data = *clause;

	el->next = NULL;
	return el;
}
List_Clause create_empty_List_Clauses(){
    List_Clause L = {0, NULL,NULL};
	return L;
}

List_Clause add_element_List_Clause(List_Clause* L, clause *c){
    Node_Clause *el;
    
	el = create_element_List_Clause(c);
	if (L->size == 0)
	{
		L->first = L->last = el;
		el->next =NULL;
	}
	else
	{

		L->last->next = el;
		L->last = el;
		el->next = NULL;
	}
	L->size++;
	
	return *L;
}

void add_element_Clause(clause *clause,literal literal){
	clause->size++;
	clause->tab[clause->size-1] = literal;
}
// clause* copyInputClauseToDestination(clause* destination, clause* input){
//     int i;
//     clause *ptr = destination;
//     for(i = 0; i < input->size; i++){

//         destination->tab[i].name = input->tab[i].name;
// 		printf("%d\n",destination->tab[i].name);
//         destination->tab[i].negation = true;
//     }
//     return ptr;
// }

void print_Clause(clause c){
	int k;
	int n = c.size;
	
	printf("[");
	for (k = 0; k < n; k++)
	{	
		literal l = c.tab[k];
		if (l.negation) {
			printf("(-%d)",l.name);
		}else{
		printf("(+%d)",l.name);

		}
	} 
	printf("]");
}

void print_List_Clause(List_Clause *L)
{
    assert (L); 
    Node_Clause *c;
    c = L->first;
    while (c!=NULL) {
        if(c->next==NULL){
            print_Clause(c->data);
        }else{
			print_Clause(c->data);
            printf(" -> ");
        }
        
        c = c->next;
    }
    printf("\n");
}



