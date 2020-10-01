#include <iostream>
#include <ctime>

template <typename T>
clock_t mult_ijk (size_t n, size_t m, size_t p, T ** A, T ** B, T ** C) {
    clock_t start = clock();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < p; j++) {
            T sum = 0.0;
            for (size_t k = 0; k < m; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return clock() - start;
}

template <typename T>
clock_t mult_ikj (size_t n, size_t m, size_t p, T ** A, T ** B, T ** C) {
    clock_t start = clock();
    for (size_t i = 0; i < n; i++) {
        for (size_t k = 0; k < m; k++) {
            T add = A[i][k];
            for (size_t j = 0; j < p; j++) {
                C[i][j] += add * B[k][j];
            }
        }
    }
    return clock() - start;
}

template <typename T>
clock_t mult_kij (size_t n, size_t m, size_t p, T ** A, T ** B, T ** C) {
    clock_t start = clock();
    for (size_t k = 0; k < m; k++) {
        for (size_t i = 0; i < n; i++) {
            T add = A[i][k];
            for (size_t j = 0; j < p; j++) {
                C[i][j] += add * B[k][j];
            }
        }
    }
    return clock() - start;
}

template <typename T>
clock_t mult_jik (size_t n, size_t m, size_t p, T ** A, T ** B, T ** C) {
    clock_t start = clock();
    for (size_t j = 0; j < p; j++) {
        for (size_t i = 0; i < n; i++) {
            T sum = 0.0;
            for (size_t k = 0; k < m; k++) {
                sum += A[i][0] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return clock() - start;
}

template <typename T>
clock_t mult_jki (size_t n, size_t m, size_t p, T ** A, T ** B, T ** C) {
    clock_t start = clock();
    for (size_t j = 0; j < p; j++) {
        for (size_t k = 0; k < m; k++) {
            T add = B[k][j];
            for (size_t i = 0; i < n; i++) {
                C[i][j] += A[i][k] * add;
            }
        }
    }
    return clock() - start;
}

template <typename T>
clock_t mult_kji (size_t n, size_t m, size_t p, T ** A, T ** B, T ** C) {
    clock_t start = clock();
    for (size_t k = 0; k < m; k++) {
        for (size_t j = 0; j < p; j++) {
            T add = B[k][j];
            for (size_t i = 0; i < n; i++) {
                C[i][j] += A[i][k] * add;
            }
        }
    }
    return clock() - start;
}
