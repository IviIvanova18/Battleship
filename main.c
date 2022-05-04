#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "constraints.h"

int main(int argc, char* argv[]){
   
    
    List_Clause list;
    list = create_empty_List_Clauses();
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
    // allConstraints(&list,column_list,line_list);
    
    
    thereIsAtLeastOneBoatK(&list);
    thereIsAtMostOneBoatK(&list);
    contiguousCell(&list);

    oneBoatOrSectionOfBoat(&list);
    // TestConstr(&list);
    noBoatTouchesAnother(&list);
	nonExistingBoat(&list);


    // KChosesNCNF(&list,line_list,true);
    // KChosesNCNF(&list,column_list,false);

    // print_List_Clause(&list);



    print_In_DIMACS_Format(&list,fileOut);


	

    return 0;
}