#!/bin/bash

mpicc -o mpi_blocking_fixed mpi_blocking_fixed.c
mpirun -np 2 ./mpi_blocking_fixed