#include <iostream>
#include <fstream>
#include <ctime>

#include "handlr.cpp"

// A(n x m) * B(m x p) = C(n x p)

int main(int argc, char * argv[]) {
    std::ifstream Fa (argv[1], std::ios::in | std::ios::binary);
    std::ifstream Fb (argv[2], std::ios::in | std::ios::binary);
    std::ofstream Fc (argv[3], std::ios::out | std::ios::binary);
    
    char buf[9];

    Fa.read(buf, 9);

    char typeA = buf[0];
    size_t n = char4_to_size_t (buf + 1);
    size_t m = char4_to_size_t (buf + 5);

    Fb.read(buf, 9);

    char typeB = buf[0];
    size_t m_ = char4_to_size_t (buf + 1);
    size_t p = char4_to_size_t (buf + 5);
    
    if (typeA != 'f' && typeA != 'd' && typeB != 'f' && typeB != 'd') {
        std::cerr << "Incorrect type" << std::endl;
        return 1;
    }
    if (m != m_ || typeA != typeB) {
        std::cerr << "Two matrices cannot be multiplied" << std::endl;
        return 1;
    }

    if ((typeA == 'd' ? handlr<double>(n, m, p, Fa, Fb, Fc, argv[4][0], typeA) : handlr<float>(n, m, p, Fa, Fb, Fc, argv[4][0], typeA)) < 0) {
        return 1;
    }
    return 0;
}

