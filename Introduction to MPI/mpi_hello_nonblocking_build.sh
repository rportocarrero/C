#!/bin/bash

mpicc -o mpi_hello_nonblocking mpi_hello_nonblocking.c -lm
mpirun -np 2 ./mpi_hello_nonblocking