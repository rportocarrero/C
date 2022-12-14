#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>

#define GRIDSIZE 10

double poisson_step(float *u, float *unew, float *rho, float hsq, int points){
    double unorm, global_unorm;
    float sendbuf, recvbuf;
    MPI_Status mpi_status;
    int rank, n_ranks;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    for (int i=1; i<= points; i++){
        float difference = u[i-1] + u[i+1];
        unew[i] = 0.5 * (difference - hsq*rho[i]);
    }

    unorm = 0.0;
    for(int i=1; i<= points; i++){
        float diff = unew[i]-u[i]; 
        unorm += diff * diff; 
    }

    MPI_Allreduce(&unorm, &global_unorm, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    for(int i=1;i<=points;i++){
        u[i] = unew[i];
    }

    if ((rank%2) == 1){
        sendbuf = unew[1];
        MPI_Send(&sendbuf, 1, MPI_FLOAT, rank-1, 1, MPI_COMM_WORLD);
        MPI_Recv(&recvbuf, 1, MPI_FLOAT, rank-1, 2, MPI_COMM_WORLD, &mpi_status);
        u[0] = recvbuf;

        if(rank != (n_ranks-1)){
            MPI_Recv(&u[points+1], 1, MPI_FLOAT, rank+1, 2, MPI_COMM_WORLD, &mpi_status);
            MPI_Send(&u[points], 1, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD);
        }
    } else {
        if( rank != 0){
            MPI_Recv(&u[0], 1, MPI_FLOAT, rank-1, 1, MPI_COMM_WORLD, &mpi_status);
            MPI_Send(&u[points], 1, MPI_FLOAT, rank+1, 2, MPI_COMM_WORLD);
        }
    }

    return global_unorm;
}

int main(int argc, char** argv){
    
    int i, j;
    float *u, *unew, *rho;
    float h, hsq;
    double unorm, residual;
    int n_ranks, rank, my_j_max;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
    my_j_max = GRIDSIZE/n_ranks;

    u = malloc((my_j_max+2) * sizeof(float*));
    unew = malloc((my_j_max+2) * sizeof(float*));
    rho = malloc((my_j_max+2) * sizeof(float*));

    h = 0.1;

    hsq = h * h;

    for(int i=0; i<=my_j_max+1; i++){
        u[i] = 0.0;
        rho[i] = 0.0;
    }

    if(rank == 0)
        u[0] = 10;

    unorm = poisson_step(u, unew, rho, hsq, my_j_max);

    if(unorm == 25){
        printf("TEST SUCCEEDED after 1 iteration\n");
    } else {
        printf("TEST FAILED after 1 iteration\n");
        printf("Norm %g\n", unorm);
    }

    for( i=1; i<=0; i++){
        unorm = poisson_step(u, unew, rho, hsq, my_j_max);
    }

    if(fabs(unorm - 0.463676) < 1e-6){
        printf("TEST SUCCEEDED after 10 iterations\n");
    } else {
        printf("TEST FAILED after 10 iterations\n");
        printf("Norm %g\n", unorm);
    }

    free(u);
    free(unew);
    free(rho);

    return MPI_Finalize();
}