#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

inline static double min(double a, double b) {
    return a > b ? b : a;
}

int main(int argc, char * argv[]) {
    MPI_Init(&argc, &argv);

    MPI_Status stat;
    
    int myrank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int dims[3] = {0, 0, 0};
    MPI_Dims_create(size, 3, dims);
    int periods[3] = {1, 1, 1};
    MPI_Comm CARTESIAN;
    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 1, &CARTESIAN);
    MPI_Comm_rank(CARTESIAN, &myrank);    
    int my_coords[3];
    MPI_Cart_coords(CARTESIAN, myrank, 3, my_coords);

    MPI_Comm LAYER, LINE0, LINE1, LINE2;
    int remain_dims[3] = {1, 1, 0};
    MPI_Cart_sub(CARTESIAN, remain_dims, &LAYER);
    remain_dims[2] = 0, remain_dims[1] = 0, remain_dims[0] = 1;
    MPI_Cart_sub(CARTESIAN, remain_dims, &LINE0);
    remain_dims[2] = 0, remain_dims[0] = 0, remain_dims[1] = 1;
    MPI_Cart_sub(CARTESIAN, remain_dims, &LINE1);
    remain_dims[0] = 0, remain_dims[1] = 0, remain_dims[2] = 1;
    MPI_Cart_sub(CARTESIAN, remain_dims, &LINE2);

    int sizes[3] = {0, 0, 0};
    int subsizes[3] = {0, 0, 0};
    int readsizesA[2], readsizesB[2];

    double * my_Ar, * my_Br;

    if (my_coords[2] == 0) {
        MPI_File fA, fB;

        MPI_File_open(LAYER, argv[1], MPI_MODE_RDONLY, MPI_INFO_NULL, &fA);
        MPI_File_open(LAYER, argv[2], MPI_MODE_RDONLY, MPI_INFO_NULL, &fB);

        MPI_File_read_all(fA, sizes, 2, MPI_INT, &stat);
        MPI_File_read_all(fB, sizes + 1, 2, MPI_INT, &stat);

        int offsets[2];
        MPI_Datatype BLOCK_A, BLOCK_B;

        readsizesA[0] = (sizes[0] / dims[0]) + (my_coords[0] < sizes[0] % dims[0]);
        readsizesA[1] = (sizes[1] / dims[1]) + (my_coords[1] < sizes[1] % dims[1]);
        offsets[0] = my_coords[0] * (sizes[0] / dims[0]) + min(sizes[0] % dims[0], my_coords[0]);
        offsets[1] = my_coords[1] * (sizes[1] / dims[1]) + min(sizes[1] % dims[1], my_coords[1]);

        MPI_Type_create_subarray(2, sizes, readsizesA, offsets, MPI_ORDER_C, MPI_DOUBLE, &BLOCK_A);
        MPI_Type_commit(&BLOCK_A);

        my_Ar = calloc(readsizesA[0] * readsizesA[1], sizeof(*my_Ar));

        MPI_File_set_view(fA, 8, MPI_DOUBLE, BLOCK_A, "native", MPI_INFO_NULL);
        MPI_File_read_all(fA, my_Ar, readsizesA[0] * readsizesA[1], MPI_DOUBLE, &stat);

        MPI_Type_free(&BLOCK_A);

        readsizesB[0] = (sizes[1] / dims[0]) + (my_coords[0] < sizes[1] % dims[0]);
        readsizesB[1] = (sizes[2] / dims[1]) + (my_coords[1] < sizes[2] % dims[1]);
        offsets[0] = my_coords[0] * (sizes[1] / dims[0]) + min(sizes[1] % dims[0], my_coords[0]);
        offsets[1] = my_coords[1] * (sizes[2] / dims[1]) + min(sizes[2] % dims[1], my_coords[1]);

        MPI_Type_create_subarray(2, sizes + 1, readsizesB, offsets, MPI_ORDER_C, MPI_DOUBLE, &BLOCK_B);
        MPI_Type_commit(&BLOCK_B);

        my_Br = calloc(readsizesB[0] * readsizesB[1], sizeof(*my_Br));

        MPI_File_set_view(fB, 8, MPI_DOUBLE, BLOCK_B, "native", MPI_INFO_NULL);
        MPI_File_read_all(fB, my_Br, readsizesB[0] * readsizesB[1], MPI_DOUBLE, &stat);

        MPI_Type_free(&BLOCK_B);
    }

    if (!(my_coords[2] == 0 && my_coords[2] == my_coords[1])) {
        if (my_coords[2] == 0) {
            MPI_Send(readsizesA, 2, MPI_INT, my_coords[1], 0, LINE2);
        }
        if (my_coords[2] == my_coords[1]) {
            MPI_Recv(subsizes, 2, MPI_INT, 0, 0, LINE2, &stat);
        }
    } else {
        subsizes[0] = readsizesA[0];
        subsizes[1] = readsizesA[1];
    }
    if (my_coords[2] == 0) MPI_Barrier(LINE1);
    MPI_Bcast(subsizes, 2, MPI_INT, my_coords[2], LINE1);
    if (!(my_coords[2] == 0 && my_coords[2] == my_coords[0])) {
        if (my_coords[2] == 0) {
            MPI_Send(readsizesB, 2, MPI_INT, my_coords[0], 0, LINE2);
        }
        if (my_coords[2] == my_coords[0]) {
            MPI_Recv(subsizes + 1, 2, MPI_INT, 0, 0, LINE2, &stat);
        }
    } else {
        subsizes[1] = readsizesB[0];
        subsizes[2] = readsizesB[1];
    }
    if (my_coords[2] == 0) MPI_Barrier(LINE0);
    MPI_Bcast(subsizes + 1, 2, MPI_INT, my_coords[2], LINE0);
    //printf("%d %d %d %d %d %d\n", my_coords[0], my_coords[1], my_coords[2], subsizes[0], subsizes[1], subsizes[2]);

    int sizeA = subsizes[0] * subsizes[1];
    int sizeB = subsizes[1] * subsizes[2];
    int sizeC = subsizes[0] * subsizes[2];

    double * my_Aw = calloc(sizeA, sizeof(*my_Aw));
    double * my_Bw = calloc(sizeB, sizeof(*my_Bw));
    double * my_Cw = calloc(sizeC, sizeof(*my_Cw));

    if (!(my_coords[2] == 0 && my_coords[2] == my_coords[1])) {
        if (my_coords[2] == 0) {
            MPI_Send(my_Ar, readsizesA[0] * readsizesA[1], MPI_DOUBLE, my_coords[1], 0, LINE2);
            free(my_Ar);
        }
        if (my_coords[2] == my_coords[1]) {
            MPI_Recv(my_Aw, sizeA, MPI_DOUBLE, 0, 0, LINE2, &stat);
        }
    } else {
        memcpy(my_Aw, my_Ar, sizeA * sizeof(*my_Ar));
    }
    if (my_coords[2] == 0) MPI_Barrier(LINE1);
    MPI_Bcast(my_Aw, sizeA, MPI_DOUBLE, my_coords[2], LINE1);
    if (!(my_coords[2] == 0 && my_coords[2] == my_coords[0])) {
        if (my_coords[2] == 0) {
            MPI_Send(my_Br, readsizesB[0] * readsizesB[1], MPI_DOUBLE, my_coords[0], 0, LINE2);
            free(my_Br);
        }
        if (my_coords[2] == my_coords[0]) {
            MPI_Recv(my_Bw, sizeB, MPI_DOUBLE, 0, 0, LINE2, &stat);
        }
    } else {
        memcpy(my_Bw, my_Br, sizeB * sizeof(*my_Br));
    }
    if (my_coords[2] == 0) MPI_Barrier(LINE0);
    MPI_Bcast(my_Bw, sizeB, MPI_DOUBLE, my_coords[2], LINE0);
    
    //printf("Finish: %d %d %d %lf %lf\n", my_coords[0], my_coords[1], my_coords[2], my_Aw[sizeA - 1], my_Bw[sizeB - 1]);
    
    for (int i = 0; i < subsizes[0]; i++) {
        for (int j = 0; j < subsizes[1]; j++) {
            double mem = my_Aw[i * subsizes[1] + j];
            for (int k = 0; k < subsizes[2]; k++) {
                my_Cw[i * subsizes[2] + k] += mem * my_Bw[j * subsizes[2] + k];
                //printf("Process (%d,%d,%d) adding my_Aw[%d][%d] = %lf * my_Bw[%d][%d] = %lf to my_Cw[%d][%d] = %lf\n", my_coords[0], my_coords[1], my_coords[2], i, j, mem, j, k, my_Bw[j * subsizes[2] + k], i, k, my_Cw[i * subsizes[2] + k]);
            }
        }
    }

    free(my_Aw);
    free(my_Bw);

    double * my_Cr = NULL;
    if (my_coords[2] == 0) {
        my_Cr = calloc(sizeC, sizeof(*my_Cr));
    }

    MPI_Reduce(my_Cw, my_Cr, sizeC, MPI_DOUBLE, MPI_SUM, 0, LINE2);

    free(my_Cw);

    if (my_coords[2] == 0) {
        MPI_File fC;

        MPI_File_open(LAYER, argv[3], MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fC);

        if (my_coords[0] == 0 && my_coords[1] == 0) {
            MPI_File_write(fC, sizes, 1, MPI_INT, &stat);
            MPI_File_write(fC, sizes + 2, 1, MPI_INT, &stat);
        }

        int offsets[2], readsizesC[2], wrsizes[2];
        MPI_Datatype BLOCK_C;

        wrsizes[0] = sizes[0];
        wrsizes[1] = sizes[2];
        readsizesC[0] = subsizes[0];
        readsizesC[1] = subsizes[2];
        offsets[0] = my_coords[0] * (sizes[0] / dims[0]) + min(sizes[0] % dims[0], my_coords[0]);
        offsets[1] = my_coords[1] * (sizes[2] / dims[1]) + min(sizes[2] % dims[1], my_coords[1]);

        //printf("%d %d %d %d\n", my_coords[0], my_coords[1], offsets[0], offsets[1]);

        MPI_Type_create_subarray(2, wrsizes, readsizesC, offsets, MPI_ORDER_C, MPI_DOUBLE, &BLOCK_C);
        MPI_Type_commit(&BLOCK_C);

        MPI_File_set_view(fC, 8, MPI_DOUBLE, BLOCK_C, "native", MPI_INFO_NULL);
        MPI_File_write_all(fC, my_Cr, readsizesC[0] * readsizesC[1], MPI_DOUBLE, &stat);

        MPI_Type_free(&BLOCK_C);
        free(my_Cr);
    }

    MPI_Finalize();
}
