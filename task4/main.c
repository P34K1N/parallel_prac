#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void rowwise(int n, int m, double * A, double * b, double * c, int size, int myrank) {
    int * counts, * displc;
    counts = calloc(size, sizeof(*counts));
    displc = calloc(size, sizeof(*displc));

    counts[0] = (n / size + (0 < n % size)) * m;
    displc[0] = 0;
    for (int i = 1; i < size; i++) {
        counts[i] = counts[i - 1];
        if (i == n % size) counts[i] -= m;
        displc[i] = displc[i - 1] + counts[i - 1];
    }

    if (myrank != 0) {
        b = calloc(m, sizeof(*b));
    } 

    int my_n = counts[myrank] / m;

    double * my_A = calloc(my_n * m, sizeof(*my_A));

    MPI_Scatterv(A, counts, displc, MPI_DOUBLE, my_A, my_n * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double * my_c = calloc(my_n, sizeof(*my_c));

    for (int i = 0; i < my_n; i++) {
        for (int j = 0; j < m; j++) {
            my_c[i] += my_A[i * m + j] * b[j];
        }
    }

    free(my_A);

    for (int i = 0; i < size; i++) {
        counts[i] /= m;
        displc[i] /= m;
    }

    if (myrank != 0) {
        free(b);
    } 

    MPI_Gatherv(my_c, my_n, MPI_DOUBLE, c, counts, displc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    free(my_c);
    free(counts);
    free(displc);
}

void columnwise(int n, int m, double * A, double * b, double * c, int size, int myrank) {
    int * counts, * displc;
    counts = calloc(size, sizeof(*counts));
    displc = calloc(size, sizeof(*displc));

    counts[0] = (m / size + (0 < m % size));
    displc[0] = 0;
    for (int i = 1; i < size; i++) {
        counts[i] = counts[i - 1];
        if (i == m % size) counts[i]--;
        displc[i] = displc[i - 1] + counts[i - 1];
    }

    int my_m = counts[myrank];
    
    double * my_A = calloc(n * my_m, sizeof(*my_A));
    double * my_b = calloc(my_m, sizeof(*my_b));
    double * my_c = calloc(n, sizeof(*my_c));

    for (int i = 0; i < n; i++) {
        MPI_Scatterv(A + i * m, counts, displc, MPI_DOUBLE, my_A + my_m * i, my_m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    MPI_Scatterv(b, counts, displc, MPI_DOUBLE, my_b, my_m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < my_m; j++) {
            my_c[i] += my_A[i * my_m + j] * my_b[j];
        }
    }

    MPI_Reduce(my_c, c, n, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    free(counts);
    free(displc);
    free(my_A);
    free(my_b); 
    free(my_c);
}

int main(int argc, char * argv[]) {
    MPI_Init(&argc, &argv);
    int size, myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double * A, * b, * c;
    int n = 0, m = 0;
    if (myrank == 0) {
        FILE * fA = fopen(argv[1], "rb");
        FILE * fb = fopen(argv[2], "rb");
        fread(&n, sizeof(n), 1, fA);
        fread(&m, sizeof(m), 1, fA);
        int m_ = 1;
        fread(&m_, sizeof(m_), 1, fb);
        if (m != m_) {
            fprintf(stderr, "Matrix sizes do not match.\n");
        } 
        
        A = calloc(n * m, sizeof(*A));
        b = calloc(m, sizeof(*b));
        if (fread(A, sizeof(*A), n * m, fA) < n * m || fread(b, sizeof(*b), m, fb) < m) {
            fprintf(stderr, "Not enough elements in the file.\n");
        }
        fclose(fA);
        fclose(fb);
        c = calloc(n, sizeof(*c));
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    switch (argv[4][0]) {
        case 'r': 
            rowwise(n, m, A, b, c, size, myrank);
            break;
        case 'c':
            columnwise(n, m, A, b, c, size, myrank);
            break;
        default:
            if (myrank == 0) {
                fprintf(stderr, "Incorrect parallelism mode.\n");
            }
    }
    

    if (myrank == 0) {
        FILE * fc = fopen(argv[3], "wb");
        fwrite(&n, sizeof(n), 1, fc);
        fwrite(c, sizeof(*c), n, fc);
        fclose(fc);
        free(A);
        free(b);
        free(c);
    }

    MPI_Finalize();

}
