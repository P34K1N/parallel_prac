#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char * argv[]) {
    srand(atoi(argv[3]));
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    char filenameA[20] = "A", filenameB[20] = "b";
    strcat(filenameA, "_");
    strcat(filenameA, argv[1]);
    strcat(filenameA, "_");
    strcat(filenameA, argv[2]);
    strcat(filenameB, "_");
    strcat(filenameB, argv[1]);
    strcat(filenameB, "_");
    strcat(filenameB, argv[2]);
    double ** A = calloc(n, sizeof(A[0]));
    double * b = calloc(m, sizeof(b[0]));

    for (int i = 0; i < n; i++) {
        A[i] = calloc(m, sizeof(A[0][0]));
        for (int j = 0; j < m; j++) {
            A[i][j] = (double) rand() / RAND_MAX;
            b[j] = (double) rand() / RAND_MAX;
        }
    }

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

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    return 0;
}
