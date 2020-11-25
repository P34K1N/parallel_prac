#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char * argv[]) {
    srand(atoi(argv[2]) + time(NULL));
    char filenameA[100], filenameB[100], filenameC[100];
    filenameA[0] = 'A';
    filenameA[1] = 0;
    filenameB[0] = 'b';
    filenameB[1] = 0;
    filenameC[0] = 'c';
    filenameC[1] = 0;
    strcat(filenameA, argv[1]);
    strcat(filenameB, argv[1]);
    strcat(filenameC, argv[1]);

    double A[64][64], b[64], c[64];
    int n = rand() % 63 + 1, m = rand() % 63 + 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            A[i][j] = (double) rand() / RAND_MAX;

    for (int i = 0; i < m; i++)
            b[i] = (double) rand() / RAND_MAX;
    
    for (int i = 0; i < n; i++)
            c[i] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            c[i] += A[i][j] * b[j];

    FILE * w = fopen(filenameA, "wb");
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&m, sizeof(m), 1, w);
    for (int i = 0; i < n; i++) {
        fwrite(A[i], sizeof(A[0][0]), m, w);
    }
    fclose(w);

    w = fopen(filenameB, "wb");
    fwrite(&m, sizeof(m), 1, w);
    fwrite(b, sizeof(*b), m, w);
    fclose(w);

    w = fopen(filenameC, "wb");
    fwrite(&n, sizeof(n), 1, w);
    fwrite(c, sizeof(*c), n, w);
    fclose(w);
    return 0;
}
