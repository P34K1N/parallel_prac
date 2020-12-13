#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char * argv[]) {
    srand(atoi(argv[4]));
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);
    char filenameA[20] = "A", filenameB[20] = "B";
    strcat(filenameA, "_");
    strcat(filenameA, argv[1]);
    strcat(filenameA, "_");
    strcat(filenameA, argv[2]);
    strcat(filenameB, "_");
    strcat(filenameB, argv[1]);
    strcat(filenameB, "_");
    strcat(filenameB, argv[2]);
    double ** A = calloc(n, sizeof(A[0]));
    double ** B = calloc(m, sizeof(B[0]));

    for (int i = 0; i < n; i++) {
        A[i] = calloc(m, sizeof(A[0][0]));
        B[i] = calloc(k, sizeof(B[0][0]));
        for (int j = 0; j < m; j++) {
            A[i][j] = (double) rand() / RAND_MAX;
            B[i][j] = (double) rand() / RAND_MAX;
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
    fwrite(&k, sizeof(k), 1, w);
    for (int i = 0; i < m; i++) {
        fwrite(B[i], sizeof(B[0][0]), k, w);
    }
    fclose(w);

    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
    return 0;
}
