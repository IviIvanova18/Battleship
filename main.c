#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "constraints.h"


// extern int GridSizeHeight, GridSizeWidth;
// extern int StartBoat, BoatCount;

void copy_file(FILE *f, FILE *g) {
    char c;
    fscanf(f, "%c", &c);
    while (!feof(f)) {
        fprintf(g, "%c", c);
        fscanf(f, "%c", &c);
    }
}

int main(int argc, char *argv[]) {
    List_Clause list;
    list = create_empty_List_Clauses();

    if (argc < 3) {
        puts("Input format :game_filename output_file_name");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    FILE *fileOut = fopen("t.tmp", "w");
    assert(f);
    assert(fileOut);
    int column_list[MAXNUM];
    int line_list[MAXNUM];
    read_game_file(f, column_list, line_list, &GridSizeHeight, &GridSizeWidth, &StartBoat, &BoatCount);
    allConstraints(&list, column_list, line_list);
   
    int count = 0;

    count = KChosesNCNF(fileOut, line_list, true);
    count += KChosesNCNF(fileOut, column_list, false);
    fclose(fileOut);

    fileOut = fopen("t.tmp", "r");
    assert(fileOut);

    FILE *newFileOut = fopen(argv[2], "w"); // Makig sure it's empty
    fclose(newFileOut);

    newFileOut = fopen(argv[2], "a");
    assert(newFileOut);

    fprintf(newFileOut, "p cnf 2010 %d\n", list.size + count);
    copy_file(fileOut, newFileOut);
    print_In_DIMACS_Format(&list, newFileOut, count);


    fclose(fileOut);
    fclose(newFileOut);

    return 0;

}