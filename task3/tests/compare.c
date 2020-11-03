#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned pi(unsigned lo, unsigned hi) { //number of primes in [lo, hi] <= pi(lo, hi)
    unsigned neg = trunc((lo - 1 < 17) ? 0 : ((lo - 1) / log(lo - 1))); //number of primes in [1, lo - 1] >= neg
    unsigned pos = trunc(1.3 * hi / log(hi)); //number of primes in [1, hi] <= pos
    return pos - neg;
}

int comp (const unsigned *i, const unsigned *j)
{
    return (int)*i - (int)*j;
}

int main(int argc, char * argv[]) {
    unsigned lo = strtoul(argv[1], NULL, 10);
    unsigned hi = strtoul(argv[2], NULL, 10);

    FILE * t = fopen(argv[3], "r");
    FILE * a = fopen(argv[4], "r");

    unsigned pii = pi(lo, hi);

    unsigned * test = calloc(pii, sizeof(*test));
    unsigned * answer =  calloc(pii, sizeof(*answer));

    unsigned num, t_count = 0, a_count = 0, err = 0;
    const unsigned max_err = 10;

    while (fscanf(t, "%u", &num) > 0) {
        if (num >= lo && num <= hi) {
            t_count++;
            if (t_count > pii) {
                printf("Too many numbers\n");
                err++;
                if (err > max_err) {
                    printf("Result is incorrect\n");    
                    free(test);
                    free(answer);
                    fclose(t);
                    fclose(a);
                    return 1;
                }
                break;
            }
            test[t_count - 1] = num;
        } else {
            printf("Number %u is out of range [%u,%u]\n", num, lo, hi);
            err++;
            if (err > max_err) {
                printf("Result is incorrect\n");    
                free(test);
                free(answer);
                fclose(t);
                fclose(a);
                return 1;
            }
        }
    }
    fclose(t);

    qsort(test, t_count, sizeof(*test), (int(*) (const void *, const void *)) comp);
    
    while (fscanf(a, "%u ", &num) > 0) {
        if (num >= lo && num <= hi) {
            answer[a_count++] = num;
        }
    }
    fclose(a);

    if (t_count > a_count) {
        printf("Too many numbers\n");
        err++;
        if (err > max_err) {
            printf("Result is incorrect\n");    
            free(test);
            free(answer);
            return 1;
        }
    }

    if (t_count < a_count) {
        printf("Too few numbers\n");
        err++;
        if (err > max_err) {
            printf("Result is incorrect\n");    
            free(test);
            free(answer);
            return 1;
        }
    }

    int i, j;
    for (i = 0, j = 0; i < t_count && j < a_count; i++, j++) {
        if (test[i] > answer[j]) {
            printf("Prime number %u not found in the list\n", answer[j]);
            err++;
            if (err > max_err) {
                printf("Result is incorrect\n");    
                free(test);
                free(answer);
                return 1;
            }
            i--;
        } else if (test[i] < answer[j]) {
            printf("Non-prime number %u found in the list\n", test[i]);
            err++;
            if (err > max_err) {
                printf("Result is incorrect\n");    
                free(test);
                free(answer);
                return 1;
            }
            j--;
        }
    }
    for (; i < t_count; i++) {
        printf("Non-prime number %u found in the list\n", test[i]);
        err++;
        if (err > max_err) {
            printf("Result is incorrect\n");    
            free(test);
            free(answer);
            return 1;
        }
    }
    for (; j < a_count; j++) {
        printf("Prime number %u not found in the list\n", answer[j]);
        err++;
        if (err > max_err) {
            printf("Result is incorrect\n");    
            free(test);
            free(answer);
            return 1;
        }
    }
    

    err ? printf("Result is incorrect\n") : printf("Result is correct\n");
    return !!err;
    
}
