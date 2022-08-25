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
    
    float u[GRIDSIZE+2], unew[GRIDSIZE+2], rho[GRIDSIZE+2];
    int i;
    float h, hsq;
    double unorm, residual;

    h = 0.1;
    hsq = h * h;
    residual = 1e-5;

    for(i = 0; i<=GRIDSIZE;i++){
        u[i] = 0.0;
        rho[i] = 0.0;
    }

    u[0] = 10.0;

    for(i=0; i<10000;i++){
        unorm = poisson_step(u, unew, rho, hsq, GRIDSIZE);
        printf("Iteration %d: Residual %g\n", i, unorm);

        if(sqrt(unorm) < sqrt(residual)){
            break;
        }
    }

    printf("Run completed with residual %g\n", unorm);
}