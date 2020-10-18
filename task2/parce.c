#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    int n = atoi(argv[1]);
    FILE * in = fopen(argv[2], "r");
    for (int i = 0; i < n; i++) {
        FILE * out = fopen(argv[i + 3], "a");
        char str[20];
        fscanf(in, "%s", str);
        fprintf(out, "%s ", str);
        fclose(out);
    }
    fclose(in);
}
