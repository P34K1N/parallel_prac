#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE * f = fopen(argv[1], "w");
    char mapping[20] = "";
    if (argc >= 8 && argv[7][0] == 'r') {
        strcpy(mapping, "-mapfile my.map");
    }
    fprintf(f, "# @ job_type = bluegene\n# @ class = large\n# @ wall_clock_limit = 00:05:00\n# @ bg_size = %s\n# @ queue\n/bgsys/drivers/ppcfloor/bin/mpirun %s ../main ../big/A_%s_%s ../big/b_%s_%s c %s %s\n", argv[2], mapping, argv[3], argv[4], argv[3], argv[4], argv[5], argv[6]);
    fclose(f);
}
