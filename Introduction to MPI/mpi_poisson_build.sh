#!/bin/bash

mpicc -o mpi_poisson mpi_poisson.c -lm
mpirun -np 4 ./mpi_poisson