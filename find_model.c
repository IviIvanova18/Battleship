#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "constraints.h"


#define YELLOW "\e[0;33m"
#define RESET "\e[0m"
#define BLUE "\e[0;34m"	
#define RED "\e[0;91m"
#define GREEN "\e[0;92m"

int totalSize() {
    int count = 0;
    for (int i = StartBoat; i < BoatCount; i++)
        count += matchKBoatToNSizeofK(i);
    return count;
}

void print_table(int *tab, int size,int column_list[], int line_list[]) {
    char table[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            table[i][j] = '-';
        }
    }
    for (int i = 0; i < totalSize(); i++) {
        int numCopy = tab[i];
        int k = numCopy % 10;
        numCopy /= 10;
        int j = numCopy % 10;
        numCopy /= 10;
        int i = numCopy % 10;
        numCopy /= 10;
        table[i][j] = (char) (k + '0');
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (table[i][j] != '-')
                printf(YELLOW"%c "RESET, table[i][j]);
            else
                printf("%c ", table[i][j]);
        }
        printf(BLUE"%d\n"RESET,column_list[i]);
        // puts("");
    }
    for (int j = 0; j<size; j++){
        printf(BLUE"%d "RESET,line_list[j]);
    }
    puts("");

}

int read_minisat_modal(FILE *f, int *tab) {
    char *s = malloc(sizeof(char) * 10);
    fgets(s, 10, f);
    if(s[0] =='U'){
        return -1;
    }
    free(s);
    int x;
    int i = 0;
    while (!feof(f)) {
        fscanf(f, "%d", &x);
        if (x > 0) {
            if ((x > 0 && x < 999) || x==2010) {
                tab[i] = x;
                i++;
            }

        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Input format : filename gamefile\n");
        return 1;
    }

    FILE *g = fopen(argv[1], "r");
    assert(g);

    FILE *file = fopen(argv[2], "r");
    assert(file);

    int column_list[MAXNUM];
    int line_list[MAXNUM];
    read_game_file(file, column_list, line_list, &GridSizeHeight, &GridSizeWidth, &StartBoat, &BoatCount);

    int *tab = calloc(15, sizeof(int));
    if (read_minisat_modal(g, tab) == -1){
        printf(RED"UNSAT\n"RESET);
        return 1;
    }
    int size = GridSizeHeight;
    printf(GREEN"SAT\n"RESET);

    print_table(tab, size, column_list, line_list);

    fclose(g);
    free(tab);

    return 0;
}