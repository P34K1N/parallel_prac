#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char * argv[]) {
    srand(atoi(argv[2]));
    int n = 127;
    char filenameA[2] = "A", filenameB[2] = "B";
    double ** A = calloc(n, sizeof(A[0]));
    double ** B = calloc(n, sizeof(B[0]));

    for (int i = 0; i < n; i++) {
        A[i] = calloc(n, sizeof(A[0][0]));
        B[i] = calloc(n, sizeof(B[0][0]));
        for (int j = 0; j < n; j++) {
            A[i][j] = (double) rand() / RAND_MAX;
            B[i][j] = (double) rand() / RAND_MAX;
        }
    }

    FILE * w = fopen(filenameA, "wb");
    char type = 'd';
    fwrite(&type, sizeof(type), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    for (int i = 0; i < n; i++) {
        fwrite(A[i], sizeof(A[0][0]), n, w);
    }
    fclose(w);

    w = fopen(filenameB, "wb");
    fwrite(&type, sizeof(type), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    for (int i = 0; i < n; i++) {
        fwrite(B[i], sizeof(B[0][0]), n, w);
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
