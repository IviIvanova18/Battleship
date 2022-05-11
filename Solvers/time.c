#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double average_time(FILE *f) {
    double sum = 0, num = 0, x;
    while (!feof(f)) {
        fscanf(f, "%lf", &x);
        sum += x;
        num++;
    }
    return (double) sum / num;
}

int main(int argc, char const *argv[]) {
    FILE *h = fopen(argv[1], "r");
    assert(h);
    printf("avg time %f\n", average_time(h));
    return 0;
}
