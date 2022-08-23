#!/bin/bash

mpicc -o mpi_hello_world mpi_hello_world.c
mpirun -np 4 ./mpi_hello_world