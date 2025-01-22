// 1. Write a MPI program to read N values in the root process. Root process sends one
// value to each process. Every process receives it and finds the factorial of that number and returns
// it to the root process. Root process gathers the factorial and finds sum of it. Use N number of processes.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int rank, size, N, A[10], B[10], c, i, f;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0) {
		N = size;
		fprintf(stdout, "Enter %d values: ", N);
		fflush(stdout);
		for(i = 0; i < N; i++)
			scanf("%d", &A[i]);
	}

	MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
	fprintf(stdout, "Received %d in process %d\n", c, rank);
	fflush(stdout);
	f = 1;
    for(i = 2; i <= c; i++)
        f *= i;
	MPI_Gather(&f, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
        int s = 0;
		for(i = 0; i < N; i++) 
            s += B[i];
			// fprintf(stdout, "%d\n", B[i]);
        fprintf(stdout, "Sum of factorials is: %d\n", s);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}

// Sample I/O:

// Enter 5 values: 1 2 3 4 5
// Received 1 in process 0
// Received 2 in process 1
// Received 5 in process 4
// Received 4 in process 3
// Received 3 in process 2
// Sum of factorials is: 153
