#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(int n, int m, double ** test, double ** answer) {
    int correct = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fabs(test[i][j] - answer[i][j]) > 0.00001) {
                printf("Error in element %d, %d: is %lf, should be %lf\n", i, j, test[i][j], answer[i][j]);
                correct = 0;
            }
        }
    }
    printf("The result is %s\n", correct ? "correct." : "incorrect.");
    return correct;
}

int test (int n, int m, FILE * Fa, FILE * Fb) {
    double ** A = calloc(n, sizeof(*A));
    double ** B = calloc(n, sizeof(*B));
    for (int i = 0; i < n; i++) {
        A[i] = calloc(m, sizeof(**A));
        B[i] = calloc(m, sizeof(**B));
        int elemsA = fread(A[i], sizeof(**A), m, Fa);
        int elemsB = fread(B[i], sizeof(**B), m, Fb);
        if (elemsA < m || elemsB < m) {
            printf("Files do not have enough elements\n");
            return 0;
        }
    }
    int correct = compare(n, m, A, B);
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
    return correct;
} 

int main(int argc, char *argv[]) {
    FILE * Fa = fopen(argv[1], "rb");
    FILE * Fb = fopen(argv[2], "rb");

    int n, m, n_, m_;
    fread(&n, 1, sizeof(n), Fa);
    fread(&m, 1, sizeof(m), Fa);
    fread(&n_, 1, sizeof(n_), Fb);
    fread(&m_, 1, sizeof(m_), Fb);
    
    if (n != n_ || m != m_) {
        printf("Matrix sizes do not match\n");
        return 1;
    }

    int res = test(n, m, Fa, Fb);

    fclose(Fa);
    fclose(Fb);

    return res ? 0 : 1;
}
