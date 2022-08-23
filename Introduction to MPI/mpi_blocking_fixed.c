#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, n_ranks, neighbour;
    int n_numbers = 524288;
    int send_message[n_numbers];
    int recv_message[n_numbers];
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    for(int i=0; i<n_numbers; i++){
        send_message[i] = i;
    }

    if(rank == 0){
        MPI_Send(send_message, n_numbers, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    if(rank == 1){
        MPI_Recv(recv_message, n_numbers, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Message received by rank %d\n", rank);
    }

    if(rank == 1){
        MPI_Send(send_message, n_numbers, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if(rank == 0){
        MPI_Recv(recv_message, n_numbers, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("Messaged received by rank %d\n", rank);

        return MPI_Finalize();
    }
}