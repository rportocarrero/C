#!/bin/bash

mpicc -o mpi_send_recv mpi_send_recv.c -lm
mpirun -np 2 ./mpi_send_recv