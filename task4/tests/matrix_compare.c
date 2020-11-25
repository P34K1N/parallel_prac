#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(int n, double * test, double * answer) {
    int correct = 1;
    for (int i = 0; i < n; i++) {
        if (fabs(test[i] - answer[i]) > 0.00001) {
            printf("Error in element %d: is %f, should be %f\n", i, test[i], answer[i]);
            correct = 0;
        }
    }
    printf("The result is %s\n", correct ? "correct." : "incorrect.");
    return correct;
}

int test (int n, FILE * Fa, FILE * Fb) {
    double * a = calloc(n, sizeof(*a));
    double * b = calloc(n, sizeof(*b)); 
    if (fread(a, sizeof(*a), n, Fa) < n || fread(b, sizeof(*b), n, Fb) < n) {
        printf("Files do not have enough elements\n");
        return 0; 
    }
    int correct = compare(n, a, b);
    free(a);
    free(b);
    return correct;
} 

int main(int argc, char *argv[]) {
    FILE * Fa = fopen(argv[1], "rb");
    FILE * Fb = fopen(argv[2], "rb");

    int n, n_;
    fread(&n, 1, sizeof(n), Fa);
    fread(&n_, 1, sizeof(n_), Fb);
    
    if (n != n_) {
        printf("Vector sizes do not match\n");
        return 1;
    }

    int res = test(n, Fa, Fb);

    fclose(Fa);
    fclose(Fb);

    return res ? 0 : 1;
}
