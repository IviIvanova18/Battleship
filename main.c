#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "constraints.h"

int main(int argc, char* argv[]){
    // literal l1;
    // l1.name = 1;
    // l1.negation = true;
    // literal l2;
    // l2.name = 2;
    // l2.negation = false;
    // literal l3;
    // l3.name = 3;
    // l3.negation = true;
    // clause cl;
	// add_element_Clause(&cl,l1);
	// add_element_Clause(&cl,l2);
	// add_element_Clause(&cl,l3);


    // cl.size =3;
    // cl.tab[0]=l1;
    // cl.tab[1]=l2;
    // cl.tab[2]=l3;

    // clause c2;
    // c2.size =4;
    // c2.tab[0]=l1;
    // c2.tab[1]=l2;
    // c2.tab[2]=l3;
    // c2.tab[3]=l2;


   
    // add_element_List_Clause(&list,&c2);
    List_Clause list;
    //add_element_List_Clause(&list,&cl);
    contiguousCell(&list);
}