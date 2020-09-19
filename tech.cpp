#include <iostream>
#include <fstream>

size_t char4_to_size_t (char * buf) {
    return buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
}

void size_t_to_char4 (size_t n, char * buf) {
    buf[0] = n & 0xff;
    buf[1] = (n & 0xff00) >> 8;
    buf[2] = (n & 0xff0000) >> 16;
    buf[3] = (n & 0xff000000) >> 24;
}

template <typename T>
int getm (size_t n, size_t m, std::ifstream & F, T ** A) {
    for (size_t i = 0; i < n; i++) {
        A[i] = new T[m];
        F.read((char *) A[i], m * sizeof(**A));
        if ((size_t) F.gcount() < m * sizeof(**A)) return -1;
    }
    return 0;
} 
