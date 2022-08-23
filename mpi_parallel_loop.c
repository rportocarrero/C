#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, n_ranks, numbers_per_rank;
    int my_first, my_last;
    int numbers = 9;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    numbers_per_rank = floor( numbers/n_ranks);
    if(numbers%n_ranks > 0){
        numbers_per_rank += 1;
    }

    my_first = rank * numbers_per_rank;
    my_last = my_first + numbers_per_rank;

    for(int i = my_first;i<my_last;i++){
        if(i < numbers){
            printf("I'm rank %d and I'm printing the number %d.\n", rank, i);
        }
    }

    return MPI_Finalize();
}