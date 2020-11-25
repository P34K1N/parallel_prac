#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    FILE * r = fopen(argv[1], "r");
    FILE * w = fopen(argv[2], "wb");
    int n;
    fscanf(r, "%d", &n);
    double x;
    fwrite(&n, sizeof(n), 1, w);
    for (int i = 0; i < n; i++) {
        fscanf(r, "%lf", &x);
        fwrite(&x, sizeof(x), 1, w);
    }
    return 0;
}
