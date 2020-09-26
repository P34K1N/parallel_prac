#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    FILE * r = fopen(argv[1], "r");
    FILE * w = fopen(argv[2], "wb");
    char type = 'd';
    fwrite(&type, sizeof(type), 1, w);
    int n, m;
    double * buf = calloc(m, sizeof(*buf));
    fscanf(r, "%d%d", &n, &m);
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&m, sizeof(m), 1, w);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(r, "%lf", &buf[j]);
        }
        fwrite(buf, sizeof(*buf), m, w);
    }
    free(buf);
    return 0;
}
