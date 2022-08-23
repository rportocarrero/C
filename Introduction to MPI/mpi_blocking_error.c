#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, n_ranks, neighbour;
    int n_numbers = 10000;
    int *send_message;
    int *recv_message;
    MPI_Status status;

    send_message = malloc(n_numbers*sizeof(int));
    recv_message = malloc(n_numbers*sizeof(int));

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    if(n_ranks != 2){
        printf("This example requires exactly two ranks\n");
        MPI_Finalize();
        return(1);
    }

    if (rank == 0){
        neighbour = 1;
    } else {
        neighbour = 0;
    }

    for(int i=0; i<n_numbers; i++){
        send_message[i] = i;
    }

    MPI_Send(send_message, n_numbers, MPI_INT, neighbour, 0, MPI_COMM_WORLD);

    MPI_Recv(recv_message, n_numbers, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &status);
    printf("Message received by rank %d \n", rank);

    free(send_message);
    free(recv_message);

    return MPI_Finalize();
}