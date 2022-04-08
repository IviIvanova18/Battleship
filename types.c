#include "types.h"

Node_Clause *create_element_List_Clause(clause *clause){
    Node_Clause *el;
	el = (Node_Clause *)malloc(sizeof(Node_Clause));
	if (el==NULL)
	{
		fprintf(stderr, "create_element_List_Point : impossible allocation\n");
		exit(-1);
	}
	copyInputClauseToDestination(el->data,clause);

	el->next = NULL;
	return el;
}
List_Clause create_empty_List_Clauses(){
    List_Clause L = {0, NULL,NULL};
	return L;
}

List_Clause add_element_List_Clause(List_Clause* L, clause *clause){
    Node_Clause *el;
    
	
	el = create_element_List_Point(clause);
    

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

clause* copyInputClauseToDestination(clause* destination, clause* input){
    int i;

    // return if no memory is allocated to the destination
    if(destination == NULL){
        return NULL;
    }
    char *ptr = destination;
    for(i = 0; i < input->size; i++){
        destination->tab[i].name = input->tab[i].name;
        destination->tab[i].negation = input->tab[i].negation;
    }

    return ptr;
}