#include <iostream>
#include <fstream>
#include <cmath>

template <typename T>
bool compare(size_t n, size_t m, T ** test, T ** answer) {
    bool correct = true;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (fabs(test[i][j] - answer[i][j]) > 0.000001) {
                std::cout << "Error in element " << i << "," << j << ": is " << test[i][j] << ", should be " << answer[i][j] << std::endl;
                correct = false;
            }
        }
    }
    std::cout << "The result is " << (correct ? "correct." : "incorrect.") << std::endl;
    return correct;
}

template <typename T>
bool test (size_t n, size_t m, std::ifstream & Fa, std::ifstream & Fb) {
    T ** A = new T * [n];
    T ** B = new T * [n];
    for (size_t i = 0; i < n; i++) {
        A[i] = new T[m];
        B[i] = new T[m];
        Fa.read((char *) A[i], m * sizeof(**A));
        Fb.read((char *) B[i], m * sizeof(**B));
        if ((size_t) Fa.gcount() < m * sizeof(**A) || (size_t) Fb.gcount() < m * sizeof(**B)) {
            std::cout << "Files have not enough elements" << std::endl;
            return false;
        }
    }
    bool correct = compare<T>(n, m, A, B);
    for (size_t i = 0; i < n; i++) {
        delete [] A[i];
        delete [] B[i];
    }
    delete [] A;
    delete [] B;
    return correct;
} 

size_t char4_to_size_t (char * buf) {
    return buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
}

int main(int argc, char *argv[]) {
    std::ifstream Fa (argv[1], std::ios::in | std::ios::binary);
    std::ifstream Fb (argv[2], std::ios::in | std::ios::binary);
    
    char buf[9];

    Fa.read(buf, 9);

    char typeA = buf[0];
    size_t n = char4_to_size_t (buf + 1);
    size_t m = char4_to_size_t (buf + 5);

    Fb.read(buf, 9);

    char typeB = buf[0];
    size_t n_ = char4_to_size_t (buf + 1);
    size_t m_ = char4_to_size_t (buf + 5);
    
    if (typeA != 'f' && typeA != 'd' && typeB != 'f' && typeB != 'd') {
        std::cout << "Incorrect type" << std::endl;
        return 1;
    }
    if (n != n_ || m != m_) {
        std::cout << "Matrix sizes do not match" << std::endl;
        return 1;
    }
    if (typeA != typeB) {
        std::cout << "Matrix types do not match" << std::endl;
        return 1;
    }

    bool correct = typeA == 'd' ? test<double>(n, m, Fa, Fb) : test<float>(n, m, Fa, Fb);
    return correct ? 0 : 1;
}
