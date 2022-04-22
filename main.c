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


   
    List_Clause list;
    
    if (argc < 3) {
        puts("Input format :game_filename output_file_name");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    FILE *fileOut;
    fileOut = fopen(argv[2],"w");
    assert(f);
    assert(fileOut);
    int column_list[GridSizeHeight]; 
    int line_list[GridSizeWidth];
    read_game_file(f,column_list,line_list);
    allConstrants(&list,column_list,line_list);
	

    print_In_DIMACS_Format(&list,fileOut);
   


	

    return 0;
}