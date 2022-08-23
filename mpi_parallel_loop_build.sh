#!/bin/bash

mpicc -o mpi_parallel_loop mpi_parallel_loop.c -lm
mpirun -np 4 ./mpi_parallel_loop