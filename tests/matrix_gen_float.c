#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char * argv[]) {
    srand(atoi(argv[2]));
    char filenameA[100], filenameB[100], filenameC[100];
    filenameA[0] = 'A';
    filenameA[1] = 0;
    filenameB[0] = 'B';
    filenameB[1] = 0;
    filenameC[0] = 'C';
    filenameC[1] = 0;
    strcat(filenameA, argv[1]);
    strcat(filenameB, argv[1]);
    strcat(filenameC, argv[1]);

    float A[10][10], B[10][10], C[10][10];
    int n = rand() % 9 + 1, m = rand() % 9 + 1, k = rand() % 9 + 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            A[i][j] = (float) rand() / RAND_MAX;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < k; j++)
            B[i][j] = (float) rand() / RAND_MAX;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            C[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int p = 0; p < k; p++)
                C[i][p] += A[i][j] * B[j][p];

    FILE * w = fopen(filenameA, "wb");
    char type = 'f';
    fwrite(&type, sizeof(type), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&m, sizeof(m), 1, w);
    for (int i = 0; i < n; i++) {
        fwrite(A[i], sizeof(A[0][0]), m, w);
    }
    fclose(w);

    w = fopen(filenameB, "wb");
    fwrite(&type, sizeof(type), 1, w);
    fwrite(&m, sizeof(n), 1, w);
    fwrite(&k, sizeof(k), 1, w);
    for (int i = 0; i < m; i++) {
        fwrite(B[i], sizeof(B[0][0]), k, w);
    }
    fclose(w);

    w = fopen(filenameC, "wb");
    fwrite(&type, sizeof(type), 1, w);
    fwrite(&n, sizeof(n), 1, w);
    fwrite(&k, sizeof(k), 1, w);
    for (int i = 0; i < n; i++) {
        fwrite(C[i], sizeof(C[0][0]), k, w);
    }
    fclose(w);
    return 0;
}
