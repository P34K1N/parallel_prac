#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char * argv[]) {
    srand(atoi(argv[2]));
    size_t n = atoi(argv[1]);
    char filenameA[10] = "A", filenameB[10] = "B";
    strcat(filenameA, argv[1]);
    strcat(filenameB, argv[1]);
    float ** A = calloc(n, sizeof(A[0]));
    float ** B = calloc(n, sizeof(B[0]));

    for (int i = 0; i < n; i++) {
        A[i] = calloc(n, sizeof(A[0][0]));
        B[i] = calloc(n, sizeof(B[0][0]));
        for (int j = 0; j < n; j++) {
            A[i][j] = (float) rand() / RAND_MAX;
            B[i][j] = (float) rand() / RAND_MAX;
        }
    }

    FILE * w = fopen(filenameA, "wb");
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    for (int i = 0; i < n; i++) {
        fwrite(A[i], sizeof(A[0][0]), n, w);
    }
    fclose(w);

    w = fopen(filenameB, "wb");
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
