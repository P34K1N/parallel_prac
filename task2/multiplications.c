#include <stdlib.h>
#include <stdio.h>

void block_mul_ijk (size_t n, size_t m, size_t p, float ** A, float ** B, float ** C, size_t blk_n, size_t blk_m, size_t blk_p) {
    float ** blk_A = calloc(blk_n, sizeof(*blk_A));
    float ** blk_B = calloc(blk_m, sizeof(*blk_B));
    float ** blk_C = calloc(blk_n, sizeof(*blk_C));

    for (size_t i = 0; i < blk_n; i++) {
        blk_A[i] = calloc(blk_m, sizeof(**blk_A));
        blk_C[i] = calloc(blk_p, sizeof(**blk_C));
    }
    for (size_t i = 0; i < blk_m; i++) {
        blk_B[i] = calloc(blk_p, sizeof(**blk_B));
    }

    size_t dim_n = n / blk_n;
    size_t dim_m = m / blk_m;
    size_t dim_p = p / blk_p;

    for (size_t i = 0; i < dim_n; i++) {
        for (size_t j = 0; j < dim_p; j++) {
            for (size_t u = 0; u < blk_n; u++) {
                for (size_t v = 0; v < blk_p; v++) {
                    blk_C[u][v] = 0.0;
                }
            } 
            
            for (size_t k = 0; k < dim_m; k++) {
                for (size_t u = 0; u < blk_n; u++) {
                    for (size_t v = 0; v < blk_m; v++) {
                        blk_A[u][v] = A[i * blk_n + u][k * blk_m + v];
                    }
                }
                for (size_t u = 0; u < blk_m; u++) {
                    for (size_t v = 0; v < blk_p; v++) {
                        blk_B[u][v] = B[k * blk_m + u][j * blk_p + v];
                    }
                }
                
                for (size_t u = 0; u < blk_n; u++) {
                    for (size_t v = 0; v < blk_p; v++) {
                        double sum = 0.0;
                        for (size_t w = 0; w < blk_m; w++) {
                            sum += blk_A[u][w] * blk_B[w][v];
                        }
                        blk_C[u][v] += sum;
                    }
                }
            }

            for (size_t u = 0; u < blk_n; u++) {
                for (size_t v = 0; v < blk_p; v++) {
                    C[i * blk_n + u][j * blk_p + v] = blk_C[u][v];
                }
            }
        }
    }
}

void block_mul_ikj (size_t n, size_t m, size_t p, float ** A, float ** B, float ** C, size_t blk_n, size_t blk_m, size_t blk_p) {
    float ** blk_A = calloc(blk_n, sizeof(*blk_A));
    float ** blk_B = calloc(blk_m, sizeof(*blk_B));
    float ** blk_C = calloc(blk_n, sizeof(*blk_C));

    for (size_t i = 0; i < blk_n; i++) {
        blk_A[i] = calloc(blk_m, sizeof(**blk_A));
        blk_C[i] = calloc(blk_p, sizeof(**blk_C));
    }
    for (size_t i = 0; i < blk_m; i++) {
        blk_B[i] = calloc(blk_p, sizeof(**blk_B));
    }

    size_t dim_n = n / blk_n;
    size_t dim_m = m / blk_m;
    size_t dim_p = p / blk_p;

    for (size_t i = 0; i < dim_n; i++) {
        for (size_t k = 0; k < dim_m; k++) {
            for (size_t u = 0; u < blk_n; u++) {
                for (size_t v = 0; v < blk_m; v++) {
                    blk_A[u][v] = A[i * blk_n + u][k * blk_m + v];
                }
            }
            
            for (size_t j = 0; j < dim_p; j++) {
                for (size_t u = 0; u < blk_n; u++) {
                    for (size_t v = 0; v < blk_p; v++) {
                        blk_C[u][v] = 0;
                    }
                }
                for (size_t u = 0; u < blk_m; u++) {
                    for (size_t v = 0; v < blk_p; v++) {
                        blk_B[u][v] = B[k * blk_m + u][j * blk_p + v];
                    }
                }
                
                for (size_t u = 0; u < blk_n; u++) {
                    for (size_t v = 0; v < blk_m; v++) {
                        double add = blk_A[u][v];
                        for (size_t w = 0; w < blk_p; w++) {
                            blk_C[u][w] += add * blk_B[v][w];
                        }
                    }
                }
    
                for (size_t u = 0; u < blk_n; u++) {
                    for (size_t v = 0; v < blk_p; v++) {
                        C[i * blk_n + u][j * blk_p + v] += blk_C[u][v];
                    }
                }
            }
        }
    }
}
