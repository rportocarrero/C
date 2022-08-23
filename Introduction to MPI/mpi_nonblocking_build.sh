#!/bin/bash

mpicc -o mpi_nonblocking mpi_nonblocking.c
mpirun -np 2 ./mpi_nonblocking