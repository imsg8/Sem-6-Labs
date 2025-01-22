// 2. Write a MPI program to read an integer value M and NXM elements into an ID array in the root
// process, where N is the number of processes. Root process sends M elements to each process. Each process
// finds average of M elements it received and sends these average values to root. Root collects all
// the values and finds the total average. Use collective communication routines.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int rank, size, *n, *arr, res, m;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0){
        printf("Enter M: ");
        scanf("%d", &m);
        n = (int *)calloc(size * m, sizeof(int));
        printf("Enter %d numbers: ", size * m);
        for (int i = 0; i < size * m; i++)
            scanf("%d", &n[i]);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    arr = (int *)calloc(m, sizeof(int));
    MPI_Scatter(n, m, MPI_INT, arr, m, MPI_INT, 0, MPI_COMM_WORLD);
    
    int s = 0;
    for (int i = 0; i < m; i++)
        s += arr[i];

    s /= m;
    MPI_Reduce(&s, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0){
        printf("The average is %d\n", res / size);
        free(n);
    }
    free(arr);
    MPI_Finalize();
    return 0;
}

// Sample I/O: (Running 5 processes)

// Enter M: 2
// Enter 10 numbers: 1 2 3 4 5 6 7 8 9 10
// The average is 5