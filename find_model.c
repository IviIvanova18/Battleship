#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void read_minisat_modal(FILE *f,FILE *fileOut) {
    char *s = malloc(sizeof(char) * 100);
    fgets(s, 10, f);
    free(s);
    int x;
    while (!feof(f)) {
        fscanf(f, "%d", &x);
        if (x > 0){
            printf("%d\n", x);
            int numCopy = x;     
            int k = numCopy % 10;
            numCopy /= 10;
            int j = numCopy % 10;
            numCopy /= 10;
            int i = numCopy % 10;
            numCopy /= 10;
        }
            
    }
}

int main(int argc, char* argv[]){
    
    FILE *g = fopen("model.txt", "r");
    assert(g);
    FILE *fileOut = fopen("solution.txt","w");
    assert(fileOut);
    read_minisat_modal(g,fileOut);
    fclose(g);
    fclose(fileOut);



	

    return 0;
}