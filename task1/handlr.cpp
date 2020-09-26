#include <iostream>
#include <fstream>
#include <ctime>

#include "tech.cpp"
#include "multiplications.cpp"

template <typename T>
int handlr (size_t n, size_t m, size_t p, std::ifstream & Fa, std::ifstream & Fb, std::ofstream & Fc, char mode, char type) {
    T ** A = new T * [n];
    T ** B = new T * [m];

    for (size_t i = 0; i < n; i++) {
        A[i] = new T [m];
    }
    
    for (size_t i = 0; i < m; i++) {
        B[i] = new T [p];
    }

    if (getm<T>(n, m, Fa, A) < 0 || getm<T>(m, p, Fb, B) < 0) {
        std::cerr << "Not enough elements in the file" << std::endl;

        for (size_t i = 0; i < n; i++) {
            delete [] A[i];
        }
        for (size_t i = 0; i < m; i++) {
            delete [] B[i];
        }
        delete [] A;
        delete [] B;
        
        return -1;
    }

    T ** C = new T * [n];
    for (size_t i = 0; i < n; i++) {
        C[i] = new T [p];
    }

    clock_t time = 0;
    
    switch (mode) {
        case '0':
            time = mult_ijk<T>(n, m, p, A, B, C);
            break;
        case '1':
            time = mult_ikj<T>(n, m, p, A, B, C);
            break;
        case '2':
            time = mult_kij<T>(n, m, p, A, B, C);
            break;
        case '3':
            time = mult_jik<T>(n, m, p, A, B, C);
            break;
        case '4':
            time = mult_jki<T>(n, m, p, A, B, C);
            break;
        case '5':
            time = mult_kji<T>(n, m, p, A, B, C);
            break;
        default:
            std::cerr << "Invalid mode" << std::endl;

            for (size_t i = 0; i < n; i++) {
                delete [] A[i];
                delete [] C[i];
            }
            for (size_t i = 0; i < m; i++) {
                delete [] B[i];
            }
            delete [] A;
            delete [] B;
            delete [] C;

            return -1;
    }

    std::cout << (double) time / CLOCKS_PER_SEC << std::endl;

    char buf[9];
    buf[0] = type;
    size_t_to_char4(n, buf + 1);
    size_t_to_char4(p, buf + 5);

    Fc.write(buf, sizeof(buf));

    for (size_t i = 0; i < n; i++) {
        Fc.write((char *) C[i], p * sizeof(**C));
        delete [] A[i];
        delete [] C[i];
    }

    for (size_t i = 0; i < m; i++) {
        delete [] B[i];
    }

    delete [] A;
    delete [] B;
    delete [] C;

    return 0;
}

