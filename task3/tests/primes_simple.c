#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE * f = fopen("primes.txt", "w");
    for (unsigned i = 2; i <= 10000; i++) {
        char isprime = 1;
        for (unsigned j = 2; j * j <= i; j++) {
            if (!(i % j)) {
                isprime = 0;
                break;
            }
        }
        if (isprime) fprintf(f, "%u ", i);
    }
    fprintf(f, "\n");
}
