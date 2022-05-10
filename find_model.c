#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "constraints.h"


#define YELLOW "\e[0;33m"
#define RESET "\e[0m"

int totalSize() {
    int count = 0;
    for (int i = StartBoat; i < BoatCount; i++)
        count += matchKBoatToNSizeofK(i);
    return count;
}

void print_table(int *tab, int size) {
    char table[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            table[i][j] = '-';
        }
    }
    for (int i = 0; i < totalSize(); i++) {
        printf("%c ", (tab[i] % 10 + '0'));
        int numCopy = tab[i];
        int k = numCopy % 10;
        numCopy /= 10;
        int j = numCopy % 10;
        numCopy /= 10;
        int i = numCopy % 10;
        numCopy /= 10;
        table[i][j] = (char) (k + '0');
    }
    puts("");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (table[i][j] != '-')
                printf(YELLOW"%c "RESET, table[i][j]);
            else
                printf("%c ", table[i][j]);
        }
        puts("");
    }
}

void read_minisat_modal(FILE *f, int *tab) {
    char *s = malloc(sizeof(char) * 10);
    fgets(s, 10, f);
    free(s);
    int x;
    int i = 0;
    while (!feof(f)) {
        fscanf(f, "%d", &x);
        if (x > 0) {
            printf("%d ", x);
            if (x > 0 && x < 999) {
                tab[i] = x;
                i++;
            }

        }
    }
    puts("");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Input format : filename");
        return 1;
    }

    FILE *g = fopen(argv[1], "r");
    assert(g);

    int *tab = calloc(15, sizeof(int));
    read_minisat_modal(g, tab);
    int size = GridSizeHeight;
    print_table(tab, size);

    fclose(g);

    free(tab);

    return 0;
}