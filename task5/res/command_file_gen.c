#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE * f = fopen(argv[1], "w");
    char mapping[20] = "";
    if (argc >= 6 && argv[5][0] == 'r') {
        strcpy(mapping, "-mapfile my.map");
    }
    int p = atoi(argv[2]);
    int res = 1;
    while (res < p) res *= 2;
    fprintf(f, "# @ job_type = bluegene\n# @ class = large\n# @ error = $(jobid).err\n# @ wall_clock_limit = 00:05:00\n# @ bg_size = %d\n# @ queue\n/bgsys/drivers/ppcfloor/bin/mpirun -n %s %s ../main ../big/A_%s_%s ../big/B_%s_%s c %s\n", res, argv[2], mapping, argv[3], argv[3], argv[3], argv[3], argv[4]);
    fclose(f);
}
