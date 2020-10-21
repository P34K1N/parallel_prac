#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <papi.h>
#include <unistd.h>
#include <sys/time.h>

#include "multiplications.h"

// A(n x m) * B(m x p) = C(n x p)

int main(int argc, char * argv[]) {
    PAPI_library_init(PAPI_VER_CURRENT);

    FILE * Fa = fopen(argv[1], "rb");
    FILE * Fb = fopen(argv[2], "rb");
    FILE * Fc = fopen(argv[3], "wb");

    size_t n, m, m_, k;

    fread(&n, sizeof(n), 1, Fa);
    fread(&m, sizeof(m), 1, Fa);
    fread(&m_, sizeof(m_), 1, Fb);
    fread(&k, sizeof(k), 1, Fb);
    
    if (m != m_) {
        fprintf(stderr, "Two matrices cannot be multiplied\n");
        return 1;
    }

    size_t block_n, block_m, block_k;
    long int cache_size = sysconf(_SC_LEVEL1_DCACHE_SIZE);
    if (cache_size == 0) cache_size = 64 * 1024; //on POLUS

    switch (argv[5][0]) {
        case 'd':
            block_n = block_m = block_k = 32;
            break;
        case 'o':
            block_n = block_m = block_k = sqrt(cache_size / 3 / sizeof(float)); 
            break;
        case 'i':
            block_n = strtoul(argv[6], NULL, 10);
            block_m = strtoul(argv[7], NULL, 10);
            block_k = strtoul(argv[8], NULL, 10);
            break;
        default:
            fprintf(stderr, "Incorrect block size input mode\n");
            return 1;
    } 

    size_t sz_n = ((n - 1) / block_n + 1) * block_n;
    size_t sz_m = ((m - 1) / block_m + 1) * block_m;
    size_t sz_k = ((k - 1) / block_k + 1) * block_k;

    float ** A = calloc(sz_n, sizeof(*A));
    float ** B = calloc(sz_m, sizeof(*B));
    float ** C = calloc(sz_n, sizeof(*C));

    for (int i = 0; i < sz_n; i++) {
        A[i] = calloc(sz_m, sizeof(**A));
        C[i] = calloc(sz_k, sizeof(**C));
        if (i < n) {
            fread(A[i], sizeof(**A), m, Fa);
        }
    }
    for (int i = 0; i < sz_m; i++) {
        B[i] = calloc(sz_k, sizeof(**B));
        if (i < m) {
            fread(B[i], sizeof(**B), k, Fb); ;
        }
    }

    fclose(Fa);
    fclose(Fb);
    
    struct timeval begin, end;

    int events[4] = {PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TOT_CYC, PAPI_FP_OPS};
    long long results[4];
    int retval = PAPI_start_counters(events, 4);
    if (retval != PAPI_OK) {
        printf("error in start\n");
        if (retval == PAPI_EINVAL) printf("One or more of the arguments is invalid. \n");
        if (retval == PAPI_EISRUN) printf("Counters already been started, you must call PAPI_stop_counters before you call this function again. \n");
        if (retval == PAPI_ESYS) printf("A system or C library call failed inside PAPI, see the errno variable. \n");
        if (retval == PAPI_ENOMEM) printf("Insufficient memory to complete the operation. \n");
        if (retval == PAPI_ECNFLCT) printf("The underlying counter hardware can not count this event and other events in the EventSet simultaneously. \n");
        if (retval == PAPI_ENOEVNT) printf("The PAPI preset is not available on the underlying hardware.\n");
    }

    gettimeofday(&begin, 0);
    
    switch (argv[4][0]) {
        case '0':
            block_mul_ijk(sz_n, sz_m, sz_k, A, B, C, block_n, block_m, block_k);
            break;
        case '1':
            block_mul_ikj(sz_n, sz_m, sz_k, A, B, C, block_n, block_m, block_k);
            break;
        default: 
            fprintf(stderr, "Incorrect matrix multiplication mode\n");
            return 1;
    }
    
    gettimeofday(&end, 0);

    if (PAPI_stop_counters(results, 4) != PAPI_OK) {
        printf("error in stop\n");
    }

    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("%.20lf %lld %lld %lld %lld\n", elapsed, results[0], results[1], results[2], results[3], results[4]);
    
    fwrite(&n, sizeof(n), 1, Fc);
    fwrite(&k, sizeof(k), 1, Fc);

    for (int i = 0; i < sz_n; i++) {
        if (i < n) {
            //for (int j = 0; j < k; j++) printf("%f ", C[i][j]);
            //printf("\n");
            fwrite(C[i], sizeof(**C), k, Fc);
        }
        free(A[i]);
        free(C[i]);
    }
    for (int i = 0; i < sz_m; i++) {
        free(B[i]);
    }
    fclose(Fc);
    
    
    return 0;
}
