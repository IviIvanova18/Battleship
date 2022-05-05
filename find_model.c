#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define YELLOW "\e[0;33m"
#define RESET "\e[0m"

void print_table(int *tab) {
    char table[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            table[i][j] = '-';
        }
    }
    for (int i = 0; i < 10; i++) {
        table[tab[i] / 100 - 10][tab[i] / 10 % 10] = (char) (tab[i] % 10 + '0');
    }
    puts("");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
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
            if (x > 999 && x < 2000) {
                tab[i] = x;
                i++;
            }

        }
    }
    puts("");
}

int main(int argc, char* argv[]){
    FILE *g = fopen("model.txt", "r");
    assert(g);

    int *tab = calloc(15, sizeof(int));
    read_minisat_modal(g, tab);

    print_table(tab);

    fclose(g);

    free(tab);
   
    return 0;
}