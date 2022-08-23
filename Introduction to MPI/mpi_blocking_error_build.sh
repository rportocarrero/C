#!/bin/bash

mpicc -o mpi_blocking_error mpi_blocking_error.c -lm
mpirun -np 2 mpi_blocking_error