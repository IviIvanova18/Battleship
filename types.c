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

combination_list create_empty_combination_list(){
	combination_list comb_list;
	comb_list.size = 0;
	return comb_list;
}
void add_new_combination(combination_list *comb_list,combination combination){
	comb_list->size++;
	comb_list->tab[comb_list->size-1] = combination;
}

void print_all_combinations(combination_list comb_list) {
	for(int j=0;j<comb_list.size;j++){
        combination c;
        c = comb_list.tab[j];
        for(int i=0;i<c.size;i++){
            printf("%d ",c.tab[i]);
        }
           
        printf("\n");
        
    }
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


void print_literal_usual_form(literal l){
	int numCopy = l.name;        
    int k = numCopy % 10;
    numCopy /= 10;
    int j = numCopy % 10;
    numCopy /= 10;
    int i = numCopy % 10;
    numCopy /= 10;
	if(l.name <=999){
		if (l.negation) {
			printf("(-X_%d,%d,%d)",i,j,k);

		}else{
			printf("(+X_%d,%d,%d)",i,j,k);
		}
	}else if(l.name>=1000 && l.name<=1999){
		if (l.negation) {
			printf("(-B_%d,%d,%d)",i,j,k);

		}else{
			printf("(+B_%d,%d,%d)",i,j,k);
		}
	}else if(l.name >= 2000 && l.name <= 2009){
		if (l.negation) {
			printf("(-O_%d)",k);

		}else{
			printf("(+O_%d)",k);
		}
		
	}else{
		printf("Error %d",l.name);
	}
}

void print_Clause(clause c){
	int k;
	int n = c.size;
	
	printf("[");
	for (k = 0; k < n; k++)
	{	
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



