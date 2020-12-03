#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

unsigned pi(unsigned lo, unsigned hi) { //number of primes in [lo, hi] <= pi(lo, hi)
    unsigned neg = trunc((lo - 1 < 17) ? 0 : ((lo - 1) / log(lo - 1))); //number of primes in [1, lo - 1] >= neg
    unsigned pos = trunc(1.3 * hi / log(hi)); //number of primes in [1, hi] <= pos
    return pos - neg;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int size, myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status stat;

    FILE * f;

    double t_start, t_finish, time, tot = 0, max = 0;
    t_start = MPI_Wtime();

    unsigned lo = strtoul(argv[1], NULL, 10);
    unsigned hi = strtoul(argv[2], NULL, 10);

    unsigned mid = sqrt(hi);
    unsigned * primes = calloc(pi(1, mid), sizeof(*primes));
    unsigned pr_sz = 0;
    unsigned count = 0;
    
    if (!myrank) {
        f = fopen(argv[3], "w");
        unsigned char * is_prime = calloc(mid + 1, sizeof(*is_prime));
        is_prime[0] = 1;
        is_prime[1] = 1;
        for (unsigned i = 2; i <= mid; i++) {
            if (is_prime[i] == 0) {
                primes[pr_sz] = i;
                pr_sz++;
                if (i >= lo) {
                    fprintf(f, "%u ", i);
                    count++;
                }
                for (unsigned j = i + 1; j <= mid; j++) {
                    if (!(j % i)) is_prime[j] = 1; 
                }
            }
        }
        free(is_prime);
    }
    MPI_Bcast(&pr_sz, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(primes, pr_sz, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    unsigned begin = ((mid + 1 > lo) ? mid + 1 : lo);
    unsigned range = (hi - begin + 1) / size + 1;
    unsigned start = begin + myrank * range;
    unsigned end = begin + (myrank + 1) * range - 1;
    end = (end < hi) ? end : hi;
    unsigned * is_prime_p = calloc(end - start + 1, sizeof(*is_prime_p));
    unsigned * more_primes = calloc(pi(start, end - 1), sizeof(*more_primes));
    unsigned pr_c = 0;
    
    for (unsigned i = 0; i < pr_sz; i++) {
        for (unsigned j = (start - 1 + primes[i] - (start - 1) % primes[i]); j <= end; j += primes[i]) {
            is_prime_p[j - start] = 1;
        }
    }
    
    for (unsigned i = start; i <= end; i++) {
        if (!is_prime_p[i - start]) {
            more_primes[pr_c] = i;
            pr_c++;
        }
    }

    t_finish = MPI_Wtime(); 
    time = t_finish - t_start;
    MPI_Reduce(&time, &tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&time, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    /*
    if (!myrank) {
        if (argv[4] == NULL || argv[5] == NULL) {
            printf("%lf %lf\n", tot, max);
        } else {
            FILE * res = fopen(argv[4], "w");
            fprintf(res, "%lf ", tot);
            fclose(res);
            res = fopen(argv[5], "w");
            fprintf(res, "%lf ", max);
            fclose(res);
        }
    }
    */

    if (!myrank) {
        for (int i = 0; i < pr_c; i++) {
            fprintf(f, "%u ", more_primes[i]);
        }
        count += pr_c;
        unsigned char semaphore = 0;
        for (int j = 1; j < size; j++) {
            MPI_Send(&semaphore, 1, MPI_UNSIGNED_CHAR, j, 0, MPI_COMM_WORLD);
            MPI_Recv(&pr_c, 1, MPI_UNSIGNED, j, 0, MPI_COMM_WORLD, &stat);
            MPI_Recv(more_primes, pr_c, MPI_UNSIGNED, j, 0, MPI_COMM_WORLD, &stat);
            for (int i = 0; i < pr_c; i++) {
                fprintf(f, "%u ", more_primes[i]);
            }
            count += pr_c;
        }
        fprintf(f, "\n");   
        printf("%u\n", count);
        fclose(f);
    } else {
        MPI_Probe(0, 0, MPI_COMM_WORLD, &stat);
        MPI_Send(&pr_c, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
        MPI_Send(more_primes, pr_c, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
    }
    
    free(is_prime_p);
    free(primes);
    free(more_primes);

    MPI_Finalize();
}


