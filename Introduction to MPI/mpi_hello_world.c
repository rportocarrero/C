#include <stdio.h>
#include <mpi.h> 

int main(int argc, char** argv){
    int rank, n_ranks;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    printf("Hello World! I'm rank %d\n", rank);
    printf("Total no. of ranks = %d\n", n_ranks);

    return MPI_Finalize();
}