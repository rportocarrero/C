#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define GRIDSIZE 10

double poisson_step(float *u, float *unew, float *rho, float hsq, int points){
    double unorm;

    for (int i=1; i<= points; i++){
        float difference = u[i-1] + u[i+1];
        unew[i] = 0.5 * (difference - hsq*rho[i]);
    }

    unorm = 0.0;
    for(int i=1; i<= points; i++){
        float diff = unew[i]-u[i]; 
        unorm += diff * diff; 
    }

    for(int i=1;i<=points;i++){
        u[i] = unew[i];
    }

    return unorm;
}

int main(int argc, char** argv){
    
    int i, j;
    float u[GRIDSIZE+2], unew[GRIDSIZE+2], rho[GRIDSIZE+2];
    float h, hsq;
    double unorm;

    h = 0.1;

    hsq = h*h;

    for(int i=0; i<=GRIDSIZE+1;i++){
        u[i] = 0.0;
        rho[i] = 0.0;
    }

    u[0] = 10;

    unorm = poisson_step(u, unew, rho, hsq, GRIDSIZE);

    if(unorm == 25){
        printf("TEST SUCCEEDED after 1 iteration\n");
    } else {
        printf("TEST FAILED after 1 iteration\n");
        printf("Norm %g\n", unorm);
    }

    for(i =1; i<10; i++){
        unorm = poisson_step(u, unew, rho, hsq, GRIDSIZE);
    }

    if( fabs(unorm- 0.463676) < 1e-6){
        printf("TEST SUCCEEDED after 10 iterations\n");
    } else {
        printf("TEST FAILED after 10 iterations\n");
        printf("Norm %g\n", unorm);
    }
}