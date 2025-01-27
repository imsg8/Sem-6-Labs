// Write a MPI program to read a 3 X 3 matrix. Enter an element to be
// searched in the root process. Find the number of occurrences of this
// element in the matrix using three processes.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void ErrorHandler(int err_code) {
    if (err_code != MPI_SUCCESS) {
        char error_string[BUFSIZ];
        int length_err_string, err_class;
        MPI_Error_class(err_code, &err_class);
        MPI_Error_string(err_code, error_string, &length_err_string);
        printf("Error: %d %s\n", err_class, error_string);
    }
}

int main(int argc, char* argv[]) {
    int rank, size, err_code, ele, result;
    int mat[3][3];

    err_code = MPI_Init(&argc, &argv);
    if (err_code != MPI_SUCCESS) {
        ErrorHandler(err_code);
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    err_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    err_code = MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        printf("Size of processes is not 3.\n");
        printf("Exiting...\n");
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    if (rank == 0) {
        ErrorHandler(err_code);
    }

    if (rank == 0) {
        printf("Enter the elements in 3x3 matrix:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &mat[i][j]);
            }
        }
        printf("Enter element to be searched: ");
        scanf("%d", &ele);
    }
    int sMat[3];
    err_code = MPI_Bcast(&ele, 1, MPI_INT, 0, MPI_COMM_WORLD);
    err_code = MPI_Scatter(mat, 3, MPI_INT, sMat, 3, MPI_INT, 0, MPI_COMM_WORLD);
    int res = 0;
    for (int i = 0; i < 3; i++) {
        if (sMat[i] == ele)
            res++;
    }
    err_code = MPI_Reduce(&res, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        ErrorHandler(err_code);
        printf("Total number of occurrences is: %d\n", result);
    }

    MPI_Finalize();
    return 0;
}


// Sample I/O:

// Enter the elements in 3x3 matrix:
// 1 2 3
// 1 2 3
// 1 2 3
// Enter element to be searched: 2
// Total number of occurences is: 3
