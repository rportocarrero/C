#!/bin/bash

mpicc -o mpi_hello_world_send mpi_hello_world_send.c -lm
mpirun -np 4 mpi_hello_world_send