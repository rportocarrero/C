#include <stdio.h>
#include <mpi.h>

int main(int argc, char ** argv){
    int rank, n_ranks, numbers_per_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    if(rank !=0){
        char message[30];
        sprintf(message, "Hello World, I'm Rank %d\n", rank);
        MPI_Send(message, 30, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        for(int sender = 1; sender < n_ranks; sender ++){
            char message[30];
            MPI_Status status;
            MPI_Recv(message, 30, MPI_CHAR, sender, 0, MPI_COMM_WORLD, &status);
            printf("%s", message);
        }
    }

    return MPI_Finalize();

}