#include <stdio.h>
#include <stdlib.h>

int main() {
    char proc[7];
    int rows, cols, p;
    char type;
    double time, def_time_r, def_time_c, speedup, efficiency;
    
    FILE * fin = fopen("time.dat", "r");
    FILE * fout1 = fopen("speedup.dat", "w");
    FILE * fout2 = fopen("efficiency.dat", "w");
    while (fscanf(fin, "%s%d%d %c%lf", proc, &rows, &cols, &type, &time) > 0) {
        p = atoi(proc);
        switch (type) {
            case 'r':
                if (p == 32) def_time_r = time;
                speedup = def_time_r / time;
                efficiency = speedup / p * 32;
                fprintf(fout1, "%s %d %d %c %lf\n", proc, rows, cols, type, speedup);
                fprintf(fout2, "%s %d %d %c %lf\n", proc, rows, cols, type, efficiency);
                break;
            case 'c':
                if (p == 32) def_time_c = time;
                speedup = def_time_c / time;
                efficiency = speedup / p * 32;
                fprintf(fout1, "%s %d %d %c %lf\n", proc, rows, cols, type, speedup);
                fprintf(fout2, "%s %d %d %c %lf\n", proc, rows, cols, type, efficiency);
                break;
            default: break;
        }
    }
    fclose(fin);
    fclose(fout1);
    fclose(fout2);
}
