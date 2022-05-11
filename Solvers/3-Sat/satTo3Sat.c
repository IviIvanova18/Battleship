#include "sat.h"
#include "dimacs.h"

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Input format: filename ; output-filename\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    assert(f);
    FILE *g = fopen(argv[2], "w");
    assert(g);

    write_new_DIMACS(f, g);

    return 0;
}
