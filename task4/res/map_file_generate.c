#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct three {
    int x, y, z;
};

int main(int argc, char *argv[]) {
    int p = atoi(argv[1]);
    srand(time(NULL) + p);
    int X, Y, Z;
    switch (p) {
        case 32:
            X = 4;
            Y = 4;
            Z = 2;
            break;
        case 64:
            X = 4;
            Y = 4;
            Z = 4;
            break;
        case 128:
            X = 4;
            Y = 4;
            Z = 8;
            break;
        case 256:
            X = 8;
            Y = 4;
            Z = 8;
            break;
        case 512:
            X = 8;
            Y = 8;
            Z = 8;
            break;
        default: break;
    }
    struct three * arr = calloc(p, sizeof(*arr));
    int cnt = 0;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                arr[cnt].x = i;
                arr[cnt].y = j;
                arr[cnt].z = k;
                cnt++;
            }
        }
    }
    
    for (cnt = 0; cnt < p - 1; cnt++) {
        int swp = cnt + rand() / (RAND_MAX / (p - cnt) + 1);
        struct three t = arr[cnt];
        arr[cnt] = arr[swp];
        arr[swp] = t;
    }

    FILE * f = fopen("my.map", "w");
    for (cnt = 0; cnt < p; cnt++) {
        fprintf(f, "%d %d %d 0\n", arr[cnt].x, arr[cnt].y, arr[cnt].z);
    }
    fclose(f);
    free(arr);
}
