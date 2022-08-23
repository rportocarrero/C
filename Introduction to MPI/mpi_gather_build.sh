#!/bin/bash

mpicc -o mpi_gather mpi_gather.c
mpirun -np 4 ./mpi_gather