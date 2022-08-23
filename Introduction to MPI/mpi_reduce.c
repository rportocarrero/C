#include <stdio.h>
#include <mpi.h>

double find_sum(double * vector, int N){
    double sum = 0;
    double global_sum;

    for(int i=0; i<N; i++){
        sum += vector[i];
    }

    MPI_Allreduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    return global_sum;
}

double find_maximum(double * vector, int N){
    double max = 0;
    double global_max;

    for(int i=0; i<N; i++){
        if(vector[i] > max){
            max = vector[i];
        }
    }

    MPI_Allreduce(&max, &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    return global_max;
}

int main(int argc, char** argv){
    int n_numbers = 1024;
    int rank;
    double vector[n_numbers];
    double sum, max;
    double my_first_number;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    my_first_number = n_numbers * rank;

    for(int i=0; i<n_numbers; i++){
        vector[i] = my_first_number + i;
    }

    sum = find_sum(vector, n_numbers);
    printf("The sum of the numbers is %f\n", sum);

    max = find_maximum(vector, n_numbers);
    printf("The largest number is %f\n", max);

    return MPI_Finalize();
}