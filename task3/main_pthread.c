#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

unsigned pi(unsigned lo, unsigned hi) { //number of primes in [lo, hi] <= pi(lo, hi)
    unsigned neg = trunc((lo - 1 < 17) ? 0 : ((lo - 1) / log(lo - 1))); //number of primes in [1, lo - 1] >= neg
    unsigned pos = trunc(1.3 * hi / log(hi)); //number of primes in [1, hi] <= pos
    return pos - neg;
}

struct intel_str {
    unsigned lo, hi, pr_sz, size;
    unsigned * primes;
};

struct pargs {
    unsigned myrank;
    struct intel_str * intel;
    unsigned pr_c;
    unsigned * more_primes;
    double time;
};

void * calc(void * arg) {
    struct timeval begin_t, end_t;
    gettimeofday(&begin_t, 0);
    struct pargs * my_args = (struct pargs *)arg;
    unsigned myrank = my_args->myrank;
    unsigned lo = my_args->intel->lo;
    unsigned hi = my_args->intel->hi;
    unsigned pr_sz = my_args->intel->pr_sz;
    unsigned size = my_args->intel->size;
    unsigned * primes = my_args->intel->primes;

    unsigned mid = sqrt(hi);    
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
    
    my_args->pr_c = pr_c;
    my_args->more_primes = more_primes;
    
    gettimeofday(&end_t, 0);
    my_args->time = end_t.tv_sec - begin_t.tv_sec + 1e-6 * (end_t.tv_usec - begin_t.tv_usec);

    free(is_prime_p);
}

int main(int argc, char *argv[]) {
    FILE * f = fopen(argv[3], "w");

    struct timeval begin, end;
    double time_first = 0, tot = 0, max = 0;
    gettimeofday(&begin, 0);

    unsigned lo = strtoul(argv[1], NULL, 10);
    unsigned hi = strtoul(argv[2], NULL, 10);

    unsigned mid = sqrt(hi);
    unsigned * primes = calloc(pi(1, mid), sizeof(*primes));
    unsigned pr_sz = 0;
    unsigned count = 0;

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

    unsigned size = strtoul(argv[4], NULL, 10);
    struct intel_str intel;
    intel.lo = lo;
    intel.hi = hi;
    intel.pr_sz = pr_sz;
    intel.size = size;
    intel.primes = primes;
    struct pargs * thread_args = calloc(size, sizeof(*thread_args));
    pthread_t * threads = calloc(size, sizeof(*threads));

    gettimeofday(&end, 0);
    time_first = end.tv_sec - begin.tv_sec + 1e-6 * (end.tv_usec - begin.tv_usec);
    
    for (int i = 0; i < size; i++) {
        thread_args[i].myrank = i;
        thread_args[i].intel = &intel;
        pthread_create(&threads[i], NULL, &calc, &thread_args[i]);
    }
    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
        for (int j = 0; j < thread_args[i].pr_c; j++) {
            fprintf(f, "%u ", thread_args[i].more_primes[j]);
        }
        tot += thread_args[i].time;
        if (max < thread_args[i].time) max = thread_args[i].time;
        count += thread_args[i].pr_c;
        free(thread_args[i].more_primes);
    }
    fprintf(f, "\n");
    printf("%u\n", count);

    tot += time_first;
    max += time_first;
    if (argv[5] == NULL || argv[6] == NULL) {
        printf("%lf %lf\n", tot, max);
    } else {
        FILE * res = fopen(argv[5], "w");
        fprintf(res, "%lf ", tot);
        fclose(res);
        res = fopen(argv[6], "w");
        fprintf(res, "%lf ", max);
        fclose(res);
    }

    free(threads);
    free(thread_args);
    free(primes);
    fclose(f);
}
