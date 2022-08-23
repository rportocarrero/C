#!/bin/bash

mpicc -o mpi_reduce mpi_reduce.c
mpirun -np 4 ./mpi_reduce