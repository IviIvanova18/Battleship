#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void read_minisat_modal(FILE *f) {
    char *s = malloc(sizeof(char) * 100);
    fgets(s, 10, f);
    free(s);
    int x;
    while (!feof(f)) {
        fscanf(f, "%d", &x);
        if (x > 0)
            printf("%d\n", x);
    }
}

int main(int argc, char* argv[]){
    
    FILE *g = fopen("model.txt", "r");
    assert(g);
    read_minisat_modal(g);
    fclose(g);

	

    return 0;
}